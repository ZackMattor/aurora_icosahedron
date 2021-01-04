# Aurora Icosahedron

The Aurora Icosahedron is an LED light which is part of the Aurora lighting project. 

See the [Documentation](/docs/) for some more nerdy details.


**This is part of the Aurora Lighting System**

[Aurora Firmware](https://github.com/ZackMattor/aurora-firmware)

[Aurora Home Hub](https://github.com/ZackMattor/aurora-home-hub)

[Aurora App](https://github.com/ZackMattor/aurora-app-v2)

## Bill of Materials (BOM)
 - Strip of 20 neopixel lights
 - Some sort of DIY Icosahedron structure (Hopefully will write up instructions someday)
 - ESP32 or Arduino Metro Mini (or really any Arduino compatibale system)

## Dependencies
 - [Platform IO](https://docs.platformio.org/en/latest/installation.html)
 - Any drivers needed to communicate with your Arduino
 - Only tested on MacOS and Linux
 
 ## Hardware Requirements
  - Plug neopixel lights into digital pin 2 on the Arduino
  - Power the neopixels off the +5 and GND pins on the Arduino
 
## Compiling and running
```
git clone https://github.com/ZackMattor/aurora_icosahedron.git
cd aurora_icosahedron
pio run -t upload
```
