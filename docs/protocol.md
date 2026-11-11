# Board-Website Message Format

> **Not decided yet.** Everything in this file is a draft and will be decided in the future:
>
> - How the board connects to the website (for example, a NodeMCU ESP32-S3 over Wi-Fi). See [wire.md](wire.md).
> - The message names and their format.
>
> Agree on it as a team before you start coding.

This file lists the messages the board and the website send each other. Each message is one line of text that ends with a newline (`\n`). Plain text is easy to read in a serial monitor (a tool that shows the text a board sends), so it is easy to debug.

## Board to website

| Message        | Meaning                                   | Example    |
|----------------|-------------------------------------------|------------|
| `BASE:<bpm>`   | Baseline heart rate after calibration     | `BASE:75`  |
| `HR:<bpm>`     | Heart rate during the answer, once a second | `HR:92`  |
| `TOUCH:<0/1>`  | Finger off (0) or on (1) the sensor       | `TOUCH:1`  |

bpm means beats per minute.

## Website to board

| Message         | Meaning                                  |
|-----------------|------------------------------------------|
| `ASK`           | A question has started. Start recording. |
| `RESULT:TRUTH`  | The LLM says truth. Show the truth signal. |
| `RESULT:LIE`    | The LLM says lie. Show the lie signal.   |

## Example session

```
board   -> BASE:75
website -> ASK
board   -> HR:80
board   -> HR:91
board   -> HR:95
website -> RESULT:LIE
```
