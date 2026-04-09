# 2. Analog Interfaces (ADC & DAC)

### 1) What to connect
* 0-10V sensor or Potentiometer to the Analog Input block.
* Multimeter to the DAC1_OUT1 pin.

### 2) What the code does
Polls the ADC to read the incoming analog value, then outputs a fixed 12-bit value to the DAC.