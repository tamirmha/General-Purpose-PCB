# The Ultimate STM32 USB Setup Guide: DFU Flashing & Virtual COM Port

This guide covers the complete end-to-end process of configuring an STM32 (specifically the STM32G0 series) to support **firmware flashing over a USB Type-C cable** (using the built-in ROM DFU Bootloader) and acting as a **Virtual COM Port (USB CDC)** for serial debugging.

---

## Phase 1: Prerequisites & Drivers

To use the STM32's built-in USB bootloader, Windows needs the official STMicroelectronics DFU driver.

1. **Download STM32CubeProgrammer:** Go to the STMicroelectronics website and download the standalone **STM32CubeProgrammer** software for Windows.
2. **Install It:** Run the installer. During installation, it will prompt you to install the **STMicroelectronics USB Drivers**. You *must* click **Yes/Install** here to ensure Windows can recognize the DFU Bootloader.

---

## Phase 2: The One-Time Hardware Unlock (Option Bytes)

By factory default, the STM32G0 ignores the physical `BOOT0` pin. We need to use your ST-LINK *one last time* to flip a hidden hardware switch inside the chip so it listens to the pin.

1. Plug your **ST-LINK** into your custom board and connect it to your PC.
2. Open **STM32CubeIDE**.
3. Go to **Run** -> **External Tools** -> **External Tools Configurations...**
4. Double-click **Program** to create a new tool.
5. **Name:** `Unlock DFU Hardware`
6. **Location:** Browse to your IDE's installation folder and find the hidden CLI tool. Example path:
   `C:\\ST\\STM32CubeIDE_1.19.0\\STM32CubeIDE\\plugins\\com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.win32_...\\tools\\bin\\STM32_Programmer_CLI.exe`
7. **Arguments:** Paste this exact command:
   `-c port=swd -ob nBOOT_SEL=0`
8. Click **Apply** and then **Run**. 
9. Look at your IDE console. If it says **"Option Bytes successfully programmed"**, you have unlocked the chip. **You can now unplug the ST-LINK forever.**

---

## Phase 3: STM32CubeMX Configuration

We need to configure your C code to act as a Virtual COM Port while the main program is running.

1. Open your **`.ioc`** file in STM32CubeIDE.
2. **Disable CubeMX DFU:** If you previously enabled "Download Firmware Update Class (DFU)" under USB_DEVICE, change it back to **Disable**. We are using the hardware ROM bootloader, not a software bootloader!
3. **Enable USB:** Go to **Connectivity** -> **USB** and check the box for **Device (FS)**.
4. **Enable Virtual COM Port:** Go to **Middleware and Software Packs** -> **USB_DEVICE** and set the Class to **Communication Device Class (Virtual Port Com)**.
5. **Fix the Clocks:** Go to the **Clock Configuration** tab. Find the **To USB (MHz)** multiplexer. It *must* be exactly **48 MHz**. Ensure it is routed from the **HSI48** oscillator.
6. **Enable Interrupts (Crucial):** Go back to **Connectivity** -> **USB** -> **NVIC Settings**. Check the box for **`USB, UCPD1 and UCPD2 global interrupt`**. *(Without this, Windows will not recognize the device when it boots).*
7. **Increase Memory (Crucial):** Go to the **Project Manager** tab -> **Project** -> **Linker Settings**. Change **Minimum Heap Size** to `0x1000` and **Minimum Stack Size** to `0x1000`. *(Without this, the USB driver will crash instantly due to lack of RAM).*
8. Save and **Generate Code**.

---

## Phase 4: Create the "Flash via USB" Button

Now we create the button that will actually shoot your code across the USB cable.

1. Go to **Run** -> **External Tools** -> **External Tools Configurations...**
2. Double-click **Program** to create a new tool.
3. **Name:** `Flash via USB DFU`
4. **Location:** Paste the exact same `STM32_Programmer_CLI.exe` path you used in Phase 2.
5. **Working Directory:** Paste this exact variable:
   `${workspace_loc:/${project_name}}`
6. **Arguments:** Paste this exact command:
   `-c port=usb -w "${project_loc}\\${config_name}\\${project_name}.elf" -v -s`
   *(Note: `-s` tells the board to automatically start running your code after flashing).*
7. Click **Apply** and **Close**.

---

## Phase 5: How to Flash Over USB (The Workflow)

Whenever you write new code and want to upload it, follow this exact physical sequence:

1. Make sure your USB Type-C cable is connected from the PC to your board.
2. **Bridge the Pins:** Use a jumper wire to connect the **`3V3`** pin to the **`SWCLK`** pin on your PROG header. *(This pulls BOOT0 HIGH).*
3. **Reset:** While holding the wire in place, press and release the physical **RESET** button on your board.
4. **Release:** Remove the jumper wire. 
   *(You should hear the Windows "Device Connected" chime. In Device Manager, it will appear as `STM32 BOOTLOADER`).*
5. **Flash:** Click your project folder in the left sidebar of the IDE, then click the **Flash via USB DFU** external tool button.
6. The code will download, verify, and automatically start running.

---

## Phase 6: Printing over USB (C Code)

To print data to your PC via the USB Type-C cable, use the generated CDC library.

1. In your `main.c` (or custom example file), add the include: 
``` c
#include "usbd_cdc_if.h"
char buffer[100];
sprintf(buffer, "Hello World over USB Type-C!\\r\\n");

// Send data over USB
CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));
```

Open a Serial Terminal (like PuTTY or the Arduino IDE Serial Monitor), select the new COM port Windows assigned to your board, set the baud rate (e.g., 115200), and watch your data stream in!
