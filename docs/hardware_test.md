# Hardware Test

This test checks that each module works and is wired correctly, before we write the real program.

The code is in `hardware/Project/Core/Src/hw_test.c`. `main.c` calls it with one line: `hw_test_run();`.

## What is tested

| Module | What the test does |
|--------|--------------------|
| KY-016 3-color LED | Lights red, then green, then blue, half a second each |
| KY-006 passive buzzer | Beeps for half a second after the LED |
| KY-039 heartbeat sensor | Reads the analog signal (`HB`) 10 times a second |
| KY-036 touch sensor | Reads the analog signal (`AO`) and the digital signal (`DO`) 10 times a second |

## What you need

- The NUCLEO-F411RE and its USB cable.
- The four modules and jumper wires.
- STM32CubeIDE.
- A serial monitor (a tool that shows the text the board sends). CubeIDE has one built in, or use PuTTY.

## What to check

The serial monitor shows one line 10 times a second, for example:

```
HB=2051 AO=1730 DO=0
```

`HB` and `AO` go from 0 (0V) to 4095 (3.3V). `DO` is 0 or 1.

| Module | How to check | Pass if | Result |
|--------|--------------|---------|--------|
| KY-016 | Watch the LED after reset | Red, green, blue, in that order | |
| KY-006 | Listen after the LED | One short low beep (500 Hz) | |
| KY-039 | Put your finger between the LED and the sensor | `HB` changes, and moves a little with your pulse | |
| KY-036 | Touch the metal tip | `AO` changes and `DO` flips between 0 and 1 | |

Write "pass" or "fail" in the Result column.

## If something fails

| Problem | Likely cause |
|---------|--------------|
| A color is missing | That wire is loose or on the wrong pin |
| Colors are in the wrong order | R, G and B wires are swapped |
| No beep | Buzzer S wire is loose or on the wrong pin |
| A number stays at 0 or 4095 | Signal wire is loose, or + and - are swapped |
| `DO` never flips | Turn the small screw (potentiometer) on the KY-036 slowly until it does |
| `HB` changes very little | Normal at 3.3V. Block room light with your hand and try again |
| No text in the serial monitor | Wrong COM port or wrong baud rate |

