# 3c. DC Motor: Serial (UART) Control

### 1) What to connect
* **Communication:** Connect your ST-LINK V3 to the `PROG` connector (`J11`) using the USB cable. The ST-LINK has a built-in Virtual COM Port (VCP) that automatically connects to the STM32's UART1 pins (PB6/PB7).
* **Motor:** Connect the small 12V Mitsumi motor to the motor output terminals. *(Note: Do not use the large Pololu motor, as its 5.5A stall current will trigger the board's 1.47A hardware limit).*

### 2) What the code does
Waits in the background for serial commands using the `ReceiveToIdle_IT` interrupt. When a complete message arrives, it parses the string for a direction prefix (`CW:` or `CC:`) and extracts the speed using `atoi()`. Because it uses interrupts, you can send variable-length commands (e.g., `CW:5\n` or `CC:65535\n`) without blocking the main processor loop.

### 3) CubeMX Configuration (What to configure)
To make the hardware and interrupts work properly, apply these settings in your `.ioc` file:
* **Connectivity -> USART1:**
  * **Mode:** Asynchronous
  * **Baud Rate:** 115200 Bits/s
* **Advanced Features Tab (Crucial Hardware Fix):**
  * **TX/RX pins swap:** `Enable` *(This digitally fixes the crossed RX/TX wires on the physical PCB schematic).*
* **NVIC Settings Tab:**
  * **USART1 global interrupt:** Checked/Enabled *(Allows the background listening to function).*
* **Timers -> TIM16:**
  * **Channel 1:** PWM Generation CH1 (Mapped to Pin PB8).
  * **Prescaler:** 0
  * **Counter Period (ARR):** 65535

### 4) How to run the program
1. **Flash the Code:** Click the Debug/Run button in STM32CubeIDE to load the firmware onto the board.
2. **Open a Serial Monitor:** Open your preferred serial terminal (VS Code Serial Monitor, TeraTerm, or PuTTY).
3. **Connect to the Board:**
   * **Port:** Select the `STMicroelectronics STLink Virtual COM Port` (Check Device Manager if you don't know the COM number).
   * **Baud Rate:** 115200
   * **Line Ending:** Set to `Newline (\n)`.
4. **Send Commands:** Type a command into the terminal and press Enter.
   * **`CW:65535`** (Spins Clockwise at 100% max speed)
   * **`CC:32000`** (Spins Counter-Clockwise at ~50% speed)
   * **`CW:0`** (Stops the motor completely)