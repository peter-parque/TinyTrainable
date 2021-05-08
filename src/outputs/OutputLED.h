/// @file OutputLED.h
/// @brief Output LED

#ifndef OUTPUT_LED_H
#define OUTPUT_LED_H

// include Arduino library
#include <Arduino.h>

// include Output library
#include "Output.h"

// include library TinyTrainable
#include "TinyTrainable.h"

/// @class OutputLED
/// @brief OutputLED inherits from Output
class OutputLED : public Output {

public:
  // constructor
  OutputLED();

  // methods for TinyTrainable
  virtual void setupOutputTest() override;
  virtual void playOutput(int classification) override;

  // variables
  int _outputPinsLED[3];

  // methods for LED
  virtual void setupOutputLED(int object, int outputPin) override;
};

#endif
