# SimpleMES
 a simple MES system with some hardware and sofware for industry

Dev env : VSCode + platformio

platformio.ini is built to dispatch each cpp file to the good board.


the solution is based on an ESP32 with a small TFT plugged by I2C with an arduino witch operate 3 light sensors.


 ## IHM :

 TFT LED panel with ESP32 or ESP32-S2 attached from makerbots

 or 
 
 M5Stack Core2

 it use LovyanGFX library for display
 and 
FT6236 Library from Makerfabs :
https://github.com/Makerfabs/Makerfabs-ESP32-S2-Parallel-TFT-with-Touch/tree/main/example/simple_test/touch16_3.5

 ## Sensor :

 SignalColumn sensor for detecting state of CNC machine based on seeeduino


