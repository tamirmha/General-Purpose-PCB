# 10. DIP Switch Configuration & Reading

### 1) What to connect
* Use the 3 built-in DIP switches (DIP1, DIP2, DIP3) on the board.

### 2) What the code does
Reads the state of the 3 DIP switches. It combines them into a 3-bit binary number (0 to 7) and uses this number to change how fast the PCB_LED blinks.