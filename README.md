# TinyTrainable

## About

TinyTrainable is an Arduino library, part of the project Tiny Trainable Instruments [https://github.com/montoyamoraga/tiny-trainable-instruments](https://github.com/montoyamoraga/tiny-trainable-instruments), created by Aarón Montoya-Moraga.

This library is being written between December 2020 and August 2021, with help from undergrad researchers Peter Tone and Maxwell Wang.

## Distribution

This Arduino library is available on this repository [https://github.com/montoyamoraga/TinyTrainable](https://github.com/montoyamoraga/TinyTrainable), and can also be installed on the Arduino IDE.

## Branches

* main: the source code and examples
* gh-pages: documentation generated with Doxygen, also available at [https://montoyamoraga.github.io/TinyTrainable](https://montoyamoraga.github.io/TinyTrainable)

## Dependencies

The dependencies of this library are specified on the [library.properties](library.properties) file and, and also included as Git submodules on [libraries/](libraries/)

* [Adafruit_Thermal](https://github.com/adafruit/Adafruit-Thermal-Printer-Library): for outputs with Adafruit Thermal Printer.
* [Arduino_APDS9960](https://github.com/arduino-libraries/Arduino_APDS9960): APDS9960 sensor, to read gestures, color, proximity.
* [Arduino_KNN](https://github.com/arduino-libraries/Arduino_KNN): for machine learning with K-Nearest Neighbors algorithm.
* [Arduino_LSM9DS1](https://github.com/arduino-libraries/Arduino_LSM9DS1): LSM9DS1 IMU sensor, to read accelerometer, magnetometer, gyroscope.
* [Arduino_TensorFlowLite](https://www.arduino.cc/reference/en/libraries/arduino_tensorflowlite/): for machine learning with TensorFlow.
* [Servo](https://github.com/arduino-libraries/Servo): output with servo motors.
* [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306): for output with screen.
* [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library): for output with screen.

## Hardware

This library runs on the Arduino Nano 33 BLE Sense.

## License

MIT
