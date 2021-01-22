// include header file
#include "Inst0.h"

// constructor for the Inst0 class
Inst0::Inst0() : _myKNN(3) {
  _labels[0], _labels[1], _labels[2] = "";
  _buzzerFrequencies[0], _buzzerFrequencies[1], _buzzerFrequencies[2] = -1;
  _midiNotes[0], _midiNotes[1], _midiNotes[2] = -1;
}

// true: instrument outputs debugging messages over USB serial
// false: standalone instrument, no debugging message
void Inst0::setupInstrument(bool serialDebugging) {
  setupLEDs();
  setupSensorAPDS9960();

  _serialDebugging = serialDebugging;

  if (_serialDebugging) {
    Serial.begin(9600);
    while (!Serial);
  }
}

// trains the KNN algorithm with examples provided by the user
// algorithm will use the 'k' nearest neighbors for classification
// 'examplesPerClass' examples that pass 'colorThreshold' are collected per class
// sets the labels of the objects for identification by the KNN algorithm
void Inst0::trainKNN(int k, int examplesPerClass, float colorThreshold, String objects[3]) {

  _k = k;
  _colorThreshold = colorThreshold;

  _labels[0] = objects[0];
  _labels[1] = objects[1];
  _labels[2] = objects[2];
  debugPrint("Labels for Inst0:");
  debugPrint(_labels[0]);
  debugPrint(_labels[1]);
  debugPrint(_labels[2]);

  for (int currentClass = 0; currentClass < 3; currentClass++) {

    turnOnLEDRGB(Colors(currentClass));

    // ask the user to show examples of each object
    for (int currentExample = 0; currentExample < examplesPerClass; currentExample++) {

      debugPrint("Show me an example of: " + _labels[currentClass]);

      // wait for an object then read its color
      readColor(_colorReading);

      // add example color to the k-NN model
      _myKNN.addExample(_colorReading, currentClass);
    }

    // TODO - maybe move to after LED change, since Serial doesn't always work 
    // and won't always be used
    debugPrint("Prepare next object");
    delay(1000);  // so the object readings don't overlap

    // wait for the object to move away again
    while (!APDS.proximityAvailable() || APDS.readProximity() == 0) {}
  }
  debugPrint("Finished training");

  // blink twice
  blinkLEDBuiltIn(2);

  // turn off the LED built in
  turnOffLEDBuiltIn();

  // turn off the LED RGB
  turnOffLEDRGB();

}

// uses the trained KNN algorithm to identify objects the user shows
void Inst0::identify() {
  if (!_checkedSetup) {
    checkInst0Setup();
  }

  // wait for the object to move away again
  while (!APDS.proximityAvailable() || APDS.readProximity() == 0) {}

  debugPrint("Let me guess your object");

  // wait for an object then read its color
  readColor(_colorReading);

  // classify the object
  int classification = _myKNN.classify(_colorReading, _k);

  debugPrint("You showed me: " + _labels[classification]);

  // turn on the corresponding light
  turnOnLEDRGB(Colors(classification));

  // TODO: add the corresponding calls to functions
  switch (_outputMode) {
    case outputBuzzer:
      tone(_outputPinBuzzer, _buzzerFrequencies[classification], _buzzerDuration);
      break;
    case outputLCD:
      break;
    case outputLED:
      break;
    case outputMIDI:
      sendSerialMIDINote(_midiChannel, _midiNotes[classification], _midiVelocity);
      break;
    case outputPrinter:
      break;
    case outputSerialUSB:
      Serial.println(classification);
      break;
    case outputServo:
      // setServoAngle(_servoAngles[classification]);
      break;
  }

  // update previous classification
  _previousClassification = classification;
}

// reads the color from the color sensor
// stores the rgb values in 'colorReading[]'
void Inst0::readColor(float colorReading[]) {

  // declare and initialize local variables for color
  int red, green, blue, colorTotal = 0;

  // wait for the object to move close enough
  while (!APDS.proximityAvailable() || APDS.readProximity() > 0) {}

  // wait until the color is bright enough
  while (colorTotal < _colorThreshold) {

    // sample if the color is available and the object is close
    if (APDS.colorAvailable()) {

      // read color and proximity
      APDS.readColor(red, green, blue);
      colorTotal = (red + green + blue);

      // update readings
      _colorReading[0] = red;
      _colorReading[1] = green;
      _colorReading[2] = blue;
    }
  }
}

// TODO: docstring, call this at the beginning of identify() once
// red is general missing setup
//    1 blink - setupInstrument() not called
//    2 blinks - setLabels() not called
//    3 blinks - trainKNN() not called
// green is usb output missing setup
//    none
// blue is midi output missing setup
//    1 blink - setSerialMIDIChannel() or setSerialMIDIVelocity not called
//    2 blinks - setFrequencies() not called
// yellow is buzzer output missing setup
//    1 blink - setupPin() not called
//    2 blinks - setFrequencies() not called
void Inst0::checkInst0Setup(){
  // checking setupInstrument()
  if (_outputMode == outputUndefined) {
    errorBlink(red, 1);
  }

  // checking setLabels()
  if (_labels[0] == "" || _labels[1] == "" || _labels[2] == "") {
    errorBlink(red, 2);
  }

  // checking trainKNN()
  if (_k == -1) {
    errorBlink(red, 3);
  }

  // checking output-specific setup
  switch (_outputMode) {
    case outputMIDI:
      if (_midiChannel > 15 || _midiVelocity == 0) {
        errorBlink(blue, 1);
      }
      if (_midiNotes[0] == -1 || _midiNotes[1] == -1 || _midiNotes[2] == -1) {
        errorBlink(blue, 2);
      }
      break;
    case outputBuzzer:
      if (_outputPinBuzzer == -1 || _buzzerDuration == 0) {
        errorBlink(yellow, 1);
      }
      if (_buzzerFrequencies[0] == -1 || _buzzerFrequencies[1] == -1 || _buzzerFrequencies[2] == -1) {
        errorBlink(yellow, 2);
      }
      break;
  }
}
