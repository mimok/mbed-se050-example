# Example for MBED SE050 Driver

## Introduction

This repo is an example of a simple MBED program using its companion SE050 driver to attest (authenticate)
temperature measurements performed using an I2C temperature sensor.
 
## Requirements

To execute this example, you need either a TSensor board or these pieces of hardware:

- a B-L072Z-LRWAN1 Board from ST.
- an OM-SE050ARD Arduino shield from NXP.
- a Pmod TMP3 sensor from digilent.

You also need to install [mbed-cli](https://os.mbed.com/docs/mbed-os/v5.15/tools/developing-mbed-cli.html) from ARM
and [ARM GCC 9](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm).
Once ARM GCC 9 is installed, you will have to follow instructions provided on this [web page](https://os.mbed.com/docs/mbed-os/v5.15/tools/manual-installation.html)
to properly configure mbed-cli.

## Importing and building the project

Once toolchain is installed, you will have to import and build the repo:
```bash
mbed import https://github.com/mimok/mbed-se050-example
cd mbed-se050-example
mbed compile -t GCC_ARM -m TSENSOR
```
If your are using the B-L072Z-LRWAN1 board and the SE050 Arduino shield, use the following command:
```bash
mbed import https://github.com/mimok/mbed-se050-example
cd mbed-se050-example
mbed compile -t GCC_ARM -m TSENSOR_DEV
```
## Preparing the hardware

If you are using the TSensor board, use female-male wire jumpers to connect SCL, SDA, GND and Vcc pins
from the Pmod module to the SCL, SDA, GND and 3v3 pin of the MIKROBUS connector.

:warning: **DO NOT connect Pmod Vcc pin to TSensor 5v pin**: Pmod must be supplied through 3v3 pin!

If you are using the B-L072Z-LRWAN1 board and the SE050 Arduino shield, plug the shield into the ST Microeletronics board
and use female-female wire jumpers to connect SCL, SDA, GND and Vcc pin from Pmod TMP3 module the corresponding pins 
of connector J11:
- SCL -> IO2
- SDA -> IO1
- Vcc -> VOUT
- GND -> Pin 7 of J11

## Loading the firmware

If you are using the TSensor board, use [STM32 Cube Programmer](https://www.st.com/en/development-tools/stm32cubeprog.html) to program the board thanks to the on-chip flash loader.
You will have to power up (or resetting) the board while pressing the BOOT0 button to allow the board to be detected by STM32 Cube Prog.

If you are using the B-L072Z-LRWAN1 board, copy/paste the generated `.bin` file into the virtual 
drive which appears when you plug the board to your computer using the on-board ST-LINK probe.

## Connecting to the console

If you are using the TSensor board, plug a USB/Serial adapter to the connector J1. If you are using the B-L072Z-LRWAN1 board you will use the ST-LINK virtual COM port.
Identify the right virtual COM port and connect to this port at 115200 baud.

If everything goes right, you should see something on the console which looks like the following log:
```
Read SE050 attested PmodTMP3 temperature
------------------------------------------
Temperature: 1b80

ChipId (len=18)
12040050 01dcfd2e 436e19ba 042c0219
5a00

Random (len=16)
10000102 03040506 0708090a 0b0c0d0e

TimeStamp (len=12)
0c000000 83000000 00000e30

Signature (len=72)
48304602 21008666 e5e7ea70 2ed835e0
9f5597b3 2530d40c c0a36494 580f6dc7
305ed680 c81a0221 00fa7032 61087205
c8caeca6 aae16247 f00fb64b f3db3cd9
a6500ea8 6a998573

Data (len=150)
01418200 0c015a03 5a035a04 5a00021b
80438200 0c000000 83000000 00000e30
d0448200 10000102 03040506 0708090a
0b0c0d0e 0f458200 12040050 01dcfd2e
436e19ba 042c0219 5a000046 82004830
46022100 8666e5e7 ea702ed8 35e09f55
97b32530 d40cc0a3 6494580f 6dc7305e
d680c81a 022100fa 70326108 7205c8ca
eca6aae1 6247f00f b64bf3db 3cd9a650
0ea86a99 8573

SW = 9000
```





