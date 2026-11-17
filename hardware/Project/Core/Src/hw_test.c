/* Hardware test for the lie detector modules. Wiring: see docs/wire.md.
 * 1. LED shows red, green, blue. Then the buzzer beeps.
 * 2. Prints sensor readings to the PC serial monitor (115200 baud), 10 times a second.
 */
#include "main.h"
#include <stdio.h>

extern UART_HandleTypeDef huart2;

#define HB_CHANNEL      0               /* KY-039 S  -> PA0 (A0) */
#define TOUCH_CHANNEL   1               /* KY-036 AO -> PA1 (A1) */
#define TOUCH_DO_PORT   GPIOB           /* KY-036 DO -> PB5 (D4) */
#define TOUCH_DO_PIN    GPIO_PIN_5
#define BUZZER_PORT     GPIOB           /* KY-006 S  -> PB4 (D5) */
#define BUZZER_PIN      GPIO_PIN_4
#define LED_R_PORT      GPIOA           /* KY-016 R  -> PA8 (D7) */
#define LED_R_PIN       GPIO_PIN_8
#define LED_G_PORT      GPIOB           /* KY-016 G  -> PB10 (D6) */
#define LED_G_PIN       GPIO_PIN_10
#define LED_B_PORT      GPIOA           /* KY-016 B  -> PA6 (D12) */
#define LED_B_PIN       GPIO_PIN_6

static void pins_init(void)
{
  GPIO_InitTypeDef g = {0};

  g.Mode = GPIO_MODE_ANALOG;
  g.Pull = GPIO_NOPULL;
  g.Pin = GPIO_PIN_0 | GPIO_PIN_1;
  HAL_GPIO_Init(GPIOA, &g);

  g.Mode = GPIO_MODE_INPUT;
  g.Pin = TOUCH_DO_PIN;
  HAL_GPIO_Init(TOUCH_DO_PORT, &g);

  g.Mode = GPIO_MODE_OUTPUT_PP;
  g.Speed = GPIO_SPEED_FREQ_LOW;
  g.Pin = LED_R_PIN | LED_B_PIN;
  HAL_GPIO_Init(GPIOA, &g);
  g.Pin = LED_G_PIN | BUZZER_PIN;
  HAL_GPIO_Init(GPIOB, &g);
}

/* The project has no HAL ADC driver yet, so set up ADC1 through its registers. */
static void adc_init(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  ADC->CCR = ADC_CCR_ADCPRE_0;          /* 84 MHz / 4 = 21 MHz, under the 36 MHz limit */
  ADC1->SMPR2 = (7U << 0) | (7U << 3);  /* longest sample time on channels 0 and 1, for weak sensor signals */
  ADC1->CR2 = ADC_CR2_ADON;
  HAL_Delay(1);                         /* ADC needs a few microseconds to wake up */
}

/* Returns 0..4095. 0 = 0 V, 4095 = 3.3 V. */
static uint32_t adc_read(uint32_t channel)
{
  ADC1->SQR3 = channel;
  ADC1->CR2 |= ADC_CR2_SWSTART;
  while (!(ADC1->SR & ADC_SR_EOC))
  {
  }
  return ADC1->DR;
}

static void led_show(GPIO_TypeDef *port, uint16_t pin)
{
  HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
  HAL_Delay(500);
  HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}

/* Passive buzzer only sounds when the pin switches on and off.
 * Toggling once per 1 ms tick gives a 500 Hz tone. */
static void buzzer_beep(uint32_t ms)
{
  uint32_t start = HAL_GetTick();
  uint32_t last = start;

  while (HAL_GetTick() - start < ms)
  {
    if (HAL_GetTick() != last)
    {
      last = HAL_GetTick();
      HAL_GPIO_TogglePin(BUZZER_PORT, BUZZER_PIN);
    }
  }
  HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}

void hw_test_run(void)
{
  char line[48];

  pins_init();
  adc_init();

  led_show(LED_R_PORT, LED_R_PIN);
  led_show(LED_G_PORT, LED_G_PIN);
  led_show(LED_B_PORT, LED_B_PIN);
  buzzer_beep(500);

  while (1)
  {
    int n = snprintf(line, sizeof line, "HB=%lu AO=%lu DO=%d\r\n",
                     adc_read(HB_CHANNEL), adc_read(TOUCH_CHANNEL),
                     (int)HAL_GPIO_ReadPin(TOUCH_DO_PORT, TOUCH_DO_PIN));
    HAL_UART_Transmit(&huart2, (uint8_t *)line, n, HAL_MAX_DELAY);
    HAL_Delay(100);
  }
}
