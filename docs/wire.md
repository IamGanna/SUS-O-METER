# Wiring Plan

> **Not decided yet.** Board pins will be chosen later. Fill in the "Board pin" column after you set the pins in `Project.ioc`.

## Module wiring

"Pin type needed" is the kind of board pin each module pin must connect to:

- ADC: reads an analog signal (a voltage that changes smoothly).
- GPIO in / out: reads or sets a simple on/off signal.
- PWM: switches a pin on and off very fast. The buzzer needs this to make sound.

| Module | Module pin       | Pin type needed | Board pin |
|--------|------------------|-----------------|-----------|
| KY-039 | S (signal)       | ADC             | TBD       |
| KY-039 | +                | Power           | 3.3V      |
| KY-039 | -                | Ground          | GND       |
| KY-036 | AO (analog out)  | ADC             | TBD       |
| KY-036 | DO (digital out) | GPIO in         | TBD       |
| KY-036 | +                | Power           | 3.3V      |
| KY-036 | G                | Ground          | GND       |
| KY-006 | S (signal)       | PWM             | TBD       |
| KY-006 | -                | Ground          | GND       |
| KY-016 | R                | GPIO out        | TBD       |
| KY-016 | G                | GPIO out        | TBD       |
| KY-016 | B                | GPIO out        | TBD       |
| KY-016 | -                | Ground          | GND       |

## Board to website link

> **Not decided yet.** One option is a NodeMCU ESP32-S3 (a small board with Wi-Fi) connected to the STM32 by UART (a 2-wire serial connection: TX sends, RX receives).

| STM32 pin | ESP32-S3 pin | Board pin |
|-----------|--------------|-----------|
| UART TX   | RX           | TBD       |
| UART RX   | TX           | TBD       |
| GND       | GND          | GND       |

TX on one board connects to RX on the other. Both boards must share GND.

## Pins already in use

These pins are already used by the NUCLEO-F411RE. Do not connect modules to them.

| Pin       | Used for                                      |
|-----------|-----------------------------------------------|
| PA2, PA3  | USART2, sends text to the PC over the USB cable |
| PA5       | Green LED on the board (LD2)                  |
| PA13, PA14 | Debugger connection (SWD)                    |
| PB3       | Debugger output (SWO)                         |
| PC13      | Blue user button on the board                 |
| PC14, PC15 | 32 kHz clock crystal                         |
| PH0, PH1  | Main clock input                              |

Because USART2 is already used for the PC, the ESP32-S3 link needs a different UART, for example USART1 or USART6.
