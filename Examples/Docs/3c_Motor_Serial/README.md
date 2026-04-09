# 3c. DC Motor: Serial (UART) Control

### 1) What to connect
* PC to UART1 pins (PB6/PB7).

### 2) What the code does
Waits for an 8-character serial string (e.g., 'CW:0750\n'). Parses direction and speed.