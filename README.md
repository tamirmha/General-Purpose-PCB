# General Purpose STM32G0 Development Board

![General Purpose PCB](./images/20260401_105217.jpg)

Welcome to the General Purpose STM32G0 Development Board project repository! This project features a comprehensive testing and development PCB designed around the STM32G0 microcontroller. The board is engineered to integrate multiple industrial and hobbyist protocols into a single platform, including DC-DC power management, motor drivers, and versatile communication interfaces[cite: 1]. The project includes manufacturing files (Gerber), Bill of Materials (BOM), Pick and Place files, and the STM32 configuration file.
Use [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) to manage and upload the code to the STM32 microcontroller.
## Developer
- **Name**: Lidor Simhi
- **GitHub**: [LidorSimhi](https://github.com/Meluhlah)

![3D Rendering](./images/IsometricView.png)
![Top View](./images/TopView.png) 
![Bottom View](./images/BotView.png)
![PCB](./images/20260401_105204.jpg)
![BOTTOM PCB](./images/20260401_105236.jpg)

## Contents

- [Description](#description)
- [Components](#components)
- [Folder Structure](#folder-structure)
- [Usage](#usage)
- [Credits](#credits)
- [Sponsors](#sponsors)
- [License](#license)

## Description

This project is a general-purpose testing board designed for educational purposes, rapid prototyping, and industrial application testing.
The board is built to handle mixed-voltage systems with onboard DC-DC converters for 12V, 5V, and 3.3V rails. 
It supports a wide range of actuators, including DC motors with encoders, Servos, and inductive loads like solenoids.

The board features extensive connectivity options, supporting industrial standards such as CAN BUS, RS485, and RS232, alongside standard UART, I2C, and SPI interfaces.

### The inputs and outputs are designed for versatility:
- **Analog Inputs**: 0-10V Industrial ADC Input and Thermistor support.
- **Digital I/O**: Selectable NPN/PNP Digital Sensor interfaces and addressable LED support (WS2812B).

## Components

The development board features the following components:

- **Microcontroller**:
    - STM32G0 Series MCU (U5).

- **Power Management**:
    - Input Voltage: VIN Max 32V.
    - DC-DC Converters: 12V, 5V, 3.3V.
    - Dedicated 3.3V LDO for MCU.

- **Communication**:
    - **Industrial**:
        - [CAN BUS](https://www.iso.org/standard/63533.html) .
        - [RS485](https://en.wikipedia.org/wiki/RS-485) .
        - [RS232](https://en.wikipedia.org/wiki/RS-232) .
    - **Standard**:
        - UART (RX/TX).
        - I2C (SDA/SCL).
        - SPI (SCK, MOSI, MISO, NCS).
        - USB 2.0 Interface.

- **Actuators & Drivers**:
    - **Motors**:
        - H-Bridge for DC Motor Control (CW/CCW).
        - Incremental Encoder Interface.
        - Servo Motor Header.
    - **Loads**:
        - Inductive Load Driver (Solenoid).
        - Addressable LED Header (WS2812B).

- **Sensors & IO**:
    - 2 x DAC Outputs.
    - Thermistor Input.
    - Digital Sensor Interface (PNP/NPN Selectable).
    - User Buttons & LEDs.

- **Files Included**:
    - Full BOM and Pick & Place files can be found:
      <br>[Bill of Materials](./Hardware/BOM_JLCPCB_PCB.xlsx)
      <br>[Pick and Place](./Hardware/Pick_Place_JLCPCB_PCB.csv)

## Folder Structure

The repository is organized as follows:

/[Firmware](./Firmware/)
<br>&nbsp;&nbsp;&nbsp;&nbsp;├── [STM32_Config](./Firmware/STM32_Config/) &nbsp;&nbsp;&nbsp;# .ioc configuration files for STM32Cube
<br>&nbsp;&nbsp;&nbsp;&nbsp;├── [src](./Firmware/src/)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; # Source code examples
<br>/[Hardware](./Hardware/)
<br>&nbsp;&nbsp;&nbsp;&nbsp;├── [Gerbers](./Hardware/Gerbers/)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; # Gerber files for PCB Manufacturing
<br>&nbsp;&nbsp;&nbsp;&nbsp;├── [BOM](./Hardware/BOM/) &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;# Bill of Materials
<br>&nbsp;&nbsp;&nbsp;&nbsp;├── [PickAndPlace](./Hardware/PickAndPlace/) &nbsp;# Automated assembly files
<br> [Examples](./Examples/) &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;# Comprehensive C source code examples and HOW_TO_USE
<br>/[Docs](./Docs/) &nbsp;&nbsp;&nbsp;&nbsp; # Datasheets for components and Pinout Diagrams
<br>/[Images](./images/) &nbsp;&nbsp;&nbsp;&nbsp; # Datasheets for components and Pinout Diagrams
<br>/README.md

## Examples

This repository includes a comprehensive suite of C code examples to help you test the board's hardware, learn embedded concepts, and implement industrial protocols. You can find these files in the `\Examples` directory.

> **💡 Need Help Running These?** > Check the `HOW_TO_USE` text document and the detailed markdown documentation located right inside the `\Examples` folder! They contain step-by-step wiring guides, CubeMX parameter settings, and explanations of the code for every single file below.

### How to Use the Examples
The codebase is structured so that all examples live in the same project without conflicting. We use macro definitions to turn specific examples on or off:
1. Open the `example_config.h` file.
2. Uncomment the specific `#define` for the example you want to run (e.g., `#define EX_1_BASIC_GPIO`).
3. Ensure all other example definitions are commented out.
4. Compile and flash!

### Available Examples 

* **1. GPIO & Power Loads**
    * `ex1_basic_gpio.c`: Basic momentary button reading and driving an inductive solenoid load via PWM.
    * `ex1_1_basic_gpio.c`: Advanced "Hit-and-Hold" toggle logic to actuate a solenoid at 100% power and hold it at 50% to save energy.
* **2. Analog Interfaces**
    * `ex2_analog.c`: Reads a potentiometer via the ADC and perfectly mirrors the output voltage in real-time using the DAC.
* **3. DC Motor Control**
    * `ex3a_motor_fixed.c`: Basic H-bridge control using buttons for fixed-speed CW and CCW rotation.
    * `ex3b_motor_analog.c`: Uses a potentiometer to dynamically control the PWM speed of the motor.
    * `ex3c_motor_serial.c`: Non-blocking UART control to command motor speed and direction via serial terminal.
* **4. Servo Motor Control**
    * `ex4a_servo_buttons.c`: Generates strict 50Hz PWM signals to drive a 5V RC servo to fixed angles using buttons.
    * `ex4b_servo_analog.c`: Scales a potentiometer's ADC reading to smoothly sweep a servo arm 180 degrees.
* **5. Motor Feedback**
    * `ex5_encoder.c`: Reads an incremental quadrature encoder to track infinite rotational position and direction.
* **6-8. Communication Protocols**
    * `ex6_rs485.c`: Implementation of the robust RS-485 industrial serial protocol.
    * `ex7_i2c.c`: Two-wire I2C communication for external sensors and displays.
    * `ex8_can.c`: Controller Area Network (CAN Bus) implementation for high-reliability automotive/industrial networks.
* **10-11. Digital Logic & Sensors**
    * `ex10_dip_switch.c`: Reads the onboard DIP switches to form a binary number, dynamically changing the LED blink rate.
    * `ex11_digital_sensor.c`: Polling logic for reading standard digital sensors (proximity, limit switches).
* **12-14. Advanced Modules**
    * `ex12_spi.c`: High-speed SPI communication protocol.
    * `ex13_ws2812.c`: Drives WS2812B addressable RGB LEDs.
    * `ex13_1_ws2813_ADC.c`: Dynamically controls addressable LEDs using analog ADC inputs.
    * `ex14_thermistor.c`: Reads and converts analog data into real-world temperature values.


## Usage

To replicate or use this project, follow these steps:

1. **Manufacturing**:
    - Use the provided Gerber files in `\Hardware\Gerbers` to order the PCB.

2. **Assembly**:
    - Assemble the components using the BOM and Pick & Place files found in `\Hardware`.
    - Ensure the correct selection of NPN/PNP jumpers for your digital sensors.

3. **Electronics**:
   <BR>Connect your peripherals according to the board labels:
    - **Power**: Connect up to 32V DC to the VIN terminal.
    - **Motors**: Connect DC motors to the "MOTOR" terminal and Servos to the "SERVO" header.
    - **Comms**: Use J30/J21 for communication interfaces.

4. **Programming**:
    - Open the `.ioc` file in `\Firmware\STM32_Config` using STM32CubeIDE or STM32CubeMX.
    - Generate the code and flash the STM32G0 MCU using the PROG interface.

5. **Debugging**:
    - Use the onboard TEST POINTS and User LEDs for easy debugging.

## Credits

This project was created to provide a robust general-purpose testing platform. Feel free to contribute by submitting pull requests or reporting issues.

## Sponsors 
A huge thanks to [PCBWay](https://pcbway.com/g/lxAijI) for sponsoring this project! 
Their support didn't stop at manufacturing – their team provided incredible post-shipping customer service and actively helped me navigate customs clearance to ensure the boards arrived safely and without delay. Highly recommended!

[PCBWay](https://pcbway.com/g/lxAijI)  is a one-stop solution for PCB prototyping, manufacturing, and assembly, as well as 3D printing services. Their high-quality products and excellent customer service make them a top choice for electronics enthusiasts and professionals alike.\
Visit [PCBWay](https://pcbway.com/g/lxAijI) for more information on their services and to get started on your own projects!

<a href="https://www.pcbway.com/project/shareproject/Manipulator_PCB_435606e7.html"><img src="https://www.pcbway.com/project/img/images/frompcbway-1220.png" alt="PCB from PCBWay" /></a>
## License

This project is licensed under the [MIT License](LICENSE). Feel free to use, modify, or distribute this code and design for personal or educational purposes.
