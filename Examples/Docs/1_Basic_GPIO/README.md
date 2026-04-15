# 1. Basic GPIO Control (Momentary Action)

### 1) What to connect
* **Input:** Press the onboard `BTN1` to activate.
* **Output:** Connect an inductive load (like a Solenoid) to the Solenoid terminal on your board.
* *(Note: The `PCB_LED` is already on the board and requires no wiring).*

### 2) What the code does
This example demonstrates a simple **momentary** switch. When `BTN1` is physically held down, it drives the solenoid at 100% power using a PWM signal and continuously blinks the onboard LED to indicate the active state. The exact moment you let go of the button, the solenoid powers off (0% PWM).

### 3) CubeMX Configuration
* **GPIO:**
  * `BTN1`: Configured as `GPIO_Input`. (If there is no external pull-up resistor on the board, ensure `Pull-up` is enabled in settings since the code looks for a pull to Ground/RESET).
  * `PCB_LED`: Configured as `GPIO_Output`.
* **Timers -> TIM14 (Solenoid Output):**
  * *Mode:* Channel 1 -> `PWM Generation CH1`.
  * *Parameter Settings:* Prescaler `0`, Counter Period `65535`.

### 4) How to run and test
1. Flash the code to your STM32.
2. Press and **hold** `BTN1`. 
3. The solenoid will actuate and the LED will blink.
4. Let go of the button, and the solenoid will instantly release.

---

# 1.1 Basic GPIO Control (Toggle & Hit-and-Hold)

### 1) What to connect
* **Input:** Press the onboard `BTN1` to toggle.
* **Output:** Connect a Solenoid to the Solenoid terminal on your board.

### 2) What the code does
This code introduces two massive upgrades for industrial control: **Latching (Toggle)** and a **Hit-and-Hold power profile**. 
When you press the button, the state toggles ON. To guarantee the heavy solenoid moves, it hits it with a full 100% power burst (65535) while your finger is on the button. The moment you let go, it drops the PWM power down to ~49% (32000). This is enough magnetic force to *hold* the solenoid in place, but drastically reduces the heat generated, preventing the coil from burning out over time. Press the button a second time to safely turn it OFF.

### 3) CubeMX Configuration
* **GPIO:**
  * `BTN1`: Configured as `GPIO_Input` (Pull-up).
  * `PCB_LED`: Configured as `GPIO_Output`.
* **Timers -> TIM14 (Solenoid Output):**
  * *Mode:* Channel 1 -> `PWM Generation CH1`.
  * *Parameter Settings:* Prescaler `0`, Counter Period `65535`.

### 4) How to run and test
1. Flash the code to your STM32.
2. Press and release `BTN1` once. 
3. You will hear a strong click as the solenoid actuates at 100% power, followed by a potential slight hum as it drops to 50% holding power when you release the button. The LED will stay firmly ON.
4. Press and release `BTN1` again to completely turn off the solenoid and the LED.