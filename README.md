# USB2BTLE

Convert boot-protocol from USB to Bluetooth LE.

# Board support.

The code is divided into a USB controller (in the `samd` directory)
and a Bluetooth LE controller (in `nrf52`).

The USB controller acts as an I²C master sending to the BTLE
controller.

## USB Controller (samd)

  * Adafruit Trinket M0
  * Adafruit Feather M4

## BTLE Controller (nrf52)

  * Adafruit Feather 52832
  * Adafruit Feather 52840

# Wiring

| USB              | BTLE        |
| ---------------- | ----------- |
| USB Voltage      | USB Voltage |
| Ground           | Ground      |
| SDA              | SDA         |
| SCL              | SCL         |
| Reset (optional) | Reset       |

![Trinket M0 and Feather 52840 wired together on a breadboard.][breadboard]

[breadboard]: usb2btle-breadboard.jpg

# Compiling/Flashing

## This is only tested on Linux. You will need to make changes for other platforms.

Edit the `Makefile` in `nrf52` and `samd` to select the appropriate
include for your board. You may also need to edit `Makefile.common` in
the root to specify paths to gcc-arm and various Arduino bits.

You should follow the arduino setup instructions for your
boards. While we're not using the Arduino IDE, we do rely on
board support packages being installed.

You will also need the SimplyAtomic library, available
[here](https://github.com/wizard97/SimplyAtomic.git).

Once everything's set up, you'll need to build and flash the images to
your board. The instructions are the same for both:

### Bluetooth controller:
1. `cd nrf52`
2. `make all flash`

### USB controller:
1. `cd samd`
2. `make all flash`

# TODO

  * `samd`/`nrf` directory names should be changed.

  * Makefile dependencies fixed so `make all` doesn't require a
    `clean` when a non-ino file is changed.

  * `find-serial-port` is Linux-only.

  * `bossac` tool path isn't conditionalized sanely.

  * Consumer key support.

  * Report protocol support.
