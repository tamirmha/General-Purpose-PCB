# 1. Basic GPIO Control

### 1) What to connect
* Press the onboard BTN1 to activate.
* Inductive load (Solenoid) to the Solenoid terminal output.

### 2) What the code does
Reads BTN1 state. If pressed, it toggles PCB_LED, turns on the solenoid, and applies a debounce delay.

## 1.1
Using Toggle instead of momentary