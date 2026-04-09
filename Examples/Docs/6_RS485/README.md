# 6. Serial Communication (UART & RS485)

### 1) What to connect
* RS485 network wires (A and B) to the RS485 terminal.

### 2) Hardware Note
This board maps the DE pin to PA1 (USART2_DE). The STM32 hardware handles switching from RX to TX automatically when `HAL_UART_Transmit` is called. No manual GPIO toggling needed!