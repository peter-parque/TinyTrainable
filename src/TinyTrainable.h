// TinyTrainable.h - a library for Tiny Trainable Instruments
// a project by Aarón Montoya-Moraga
// with assistance by undergrad researchers Peter Tone, Maxwell Wang
// Master's thesis at MIT Media Lab, Opera of the Future / Future Sketches
// Started in November 2020
// MIT License

#ifndef TINY_TRAINABLE_H
#define TINY_TRAINABLE_H

// include Arduino library
#include <Arduino.h>

// include library for proximity and light sensor
// https://www.arduino.cc/en/Reference/ArduinoAPDS9960
#include <Arduino_APDS9960.h>

// include library for temperature and humidity sensor
// https://www.arduino.cc/en/Reference/ArduinoHTS221
#include <Arduino_HTS221.h>

// include library for pressure sensor
// https://www.arduino.cc/en/Reference/ArduinoLPS22HB/
#include <Arduino_LPS22HB.h>

// include library for IMU sensor
// 3-axis accelerometer, 3-axis gyroscope, 3-axis magnetometer
// https://www.arduino.cc/en/Reference/ArduinoLSM9DS1/
#include <Arduino_LSM9DS1.h>

// COMMENT - was giving me compiler errors even though i had it installed?
// include Servo library
// #include <Servo.h>

// include Adafruit Thermal Printer library
#include <Adafruit_Thermal.h>

// colors for setting the RGB LED
enum Colors {red = 0, green = 1, blue= 2, yellow = 3, magenta = 4, cyan = 5};

// different instrument output modes
enum OutputMode {
  outputBuzzer = 0, 
  outputLCD = 1, 
  outputLED = 2, 
  outputMIDI = 3, 
  outputPrinter = 4, 
  outputSerialUSB = 5, 
  outputServo = 6,
  outputUndefined = 7
};

// COMMENT - i don't think these are in the same order as in the cpp file.
// choose an order you like and then we should get them to match for readibility.

class TinyTrainable {
  public:
    // constructor
    TinyTrainable();
    
    // template datatypes allows any datatype as an argument, like Serial.println().
    // it is defined here in the header file so it compiles at the beginning
    template <typename T> void debugPrint(T message) {
      if (_serialDebugging) {
        Serial.println(message);
      }
    };
    
    // COMMENT - instead of having two methods to turn the led on or off, i think it 
    // would be cleaner to have just one "setLEDBuiltInState(bool on)"
    void turnOnLEDBuiltIn();
    void turnOffLEDBuiltIn();
    void blinkLEDBuiltIn(int blinks);
    // COMMENT - same comment as above, merge on and off?
    void turnOnLEDRGB(Colors color);
    void turnOffLEDRGB();
    void errorBlink(Colors color, int blinkNum);

    // methods for outputs
    void setupOutputBuzzer(int outputPin, int buzzerDuration, int freq0, int freq1, int freq2);
    void setupOutputMIDI(byte midiChannel, byte midiVelocity, int note0, int note1, int note2);
    void setupOutputSerialUSB();
    void setupOutputServo(int outputPin, int angle0, int angle1, int angle2);

    // COMMENT - not sure what this is for, leaving it here for the moment!
    // void setServoAngle(int angle);

    // TODO: methods for outputLCD
    // TODO: methods for outputLED
    // TODO: methods for outputPrinter
    // TODO: methods for outputSerialUSB

  protected:
    void setupLEDs();

    // methods for input sensors
    // COMMENT - i moved all the links from here to docstrings in the cpp file,
    // to keep the files more readable
    // TODO: add all sensors on the Arduino Nano BLE 33 Sense
    void setupSensorAPDS9960();
    void setupSensorHTS221();
    void setupSensorLPS22HB();
    void setupSensorLSM9DS1();

    // methods for outputs
    void setupSerialMIDI();
    void sendSerialMIDINote(byte channel, byte note, byte velocity);

    // COMMENT - i moved all comments from here into the cpp file for readability
    bool _serialDebugging = false;

    // variables for outputs
    OutputMode _outputMode = outputUndefined;
    // COMMENT - since these variables are protected and not exposed to the user, 
    // all these pin variables can be condensed to one variable (that might get set 
    // through different methods)
    int _outputPinBuzzer = -1;
    int _outputPinLCD = -1;
    int _outputPinLED = -1;
    int _outputPinMIDI = -1;
    int _outputPinPrinter = -1;  // TODO: this might need to be several variables
    int _outputPinServo = -1;

    // TODO: variables for outputBuzzer
    int _buzzerFrequencies[3];
    int _buzzerDuration = 0;

    // TODO: variables for outputMIDI
    int _midiNotes[3];
    byte _midiChannel = 16;
    byte _midiVelocity = 0;

    // TODO: variables for outputServo
    // Servo _servo;
    int _servoAngleCurrent = 0;
    // COMMENT - can these min and maxes be constants?
    int _servoAngleMin = 0;
    int _servoAngleMax = 180;
    int _servoAngles[3];

    // TODO: variables for outputLCD
    // TODO: variables for outputLED
    // TODO: variables for outputPrinter
    // TODO: variables for outputSerialUSB
};

#endif
