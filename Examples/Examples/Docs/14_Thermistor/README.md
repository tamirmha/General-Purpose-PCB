# 14. Thermistor Temperature Reading

### 1) What to connect
* Connect a 10k NTC Thermistor to the `THERM` header.

### 2) What the code does
Reads the raw ADC value from the THERMISTOR pin and uses the Steinhart-Hart equation to calculate temperature in Celsius.