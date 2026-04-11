# 2. Analog Interfaces (ADC & DAC)

### 1) What to connect
* **Input:** Connect the middle wiper pin of a Potentiometer to your board's Analog Input (ADC) terminal. Connect the other two outer pins of the potentiometer to 3.3V and GND.
* **Output:** Connect a Multimeter (set to measure DC Voltage) or an LED with a resistor to the Analog Output (DAC) terminal.

### 2) What the code does
This code acts as a real-time analog mirror. 
1. **The ADC (Analog-to-Digital Converter)** reads the physical voltage from the potentiometer and translates it into a 12-bit digital number ranging from `0` (0 Volts) to `4095` (3.3 Volts). 
2. **The DAC (Digital-to-Analog Converter)** takes that exact digital number and physically generates the corresponding voltage on the output pin. 

As you twist the potentiometer, the STM32 actively tracks your movement and outputs an identical sweeping voltage.

### 3) CubeMX Configuration
* **Analog -> ADC1:**
  * Configure your specific input pin (e.g., IN0, IN1) as an `INx Single-ended` channel.
  * *Parameter Settings:* Ensure "Resolution" is set to `ADC 12-bit resolution`.
* **Analog -> DAC1:**
  * Configure `OUT1` mode to `Connected to external pin only`.

### 4) How to run and test
1. Flash the code to your STM32.
2. Hook up a multimeter to the DAC output pin and turn on the board.
3. Slowly twist the potentiometer. 
4. You will see the voltage on your multimeter smoothly sweep up and down (from ~0V up to ~3.3V) in perfect sync with your hand movements! 
5. **Bonus:** If you use the STM32CubeIDE debugger, add `adc_value` to your **Live Expressions** tab to watch the raw 12-bit numbers (`0` to `4095`) change in real-time as you turn the knob.