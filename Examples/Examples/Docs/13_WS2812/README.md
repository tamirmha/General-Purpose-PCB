# 13. External Addressable LED Strip (WS2812B / NeoPixel)

### 1) What to connect
* Connect WS2812B LED strip to the `WS2812B` header on the PCB.

### 2) What the code does
Translates standard RGB values into GRB bit patterns and uses DMA on TIM3 to feed perfect 800kHz timing pulses to the strip.