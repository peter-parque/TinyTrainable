/// @file InputSpeech.h
/// @brief TensorFlow model + input speech

#ifndef INPUT_SPEECH_H
#define INPUT_SPEECH_H

/// @include library Arduino
#include <Arduino.h>

/// @include library TinyTrainable
#include "TinyTrainable.h"

/// @include library Input 
#include "Input.h"

/// @include library for input microphone
// https://www.arduino.cc/en/Reference/PDM/
#include <PDM.h>

/// @include library for machine learning
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/micro_mutable_op_resolver.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

/// @include files from TinyML micro_speech
#include "../tensorflow_speech/recognize_commands.h"

// #include "../tensorflow/main_functions.h"
// #include "../tensorflow/command_responder.h"
// #include "../tensorflow/feature_provider.h"
// #include "../tensorflow/micro_features_micro_model_settings.h"
// #include "../tensorflow/micro_features_model.h"
// #include "../tensorflow/recognize_commands.h"

/// @class InputSpeech
/// @brief InputSpeech inherits from Input
class InputSpeech : public Input {
public:

  /// @brief constructor
  InputSpeech();

  virtual void setupInstrument(bool serialDebugging) override;
  virtual void setupSpeechModel(String sounds[3],
                             const unsigned char *model = nullptr) override;
  virtual void identify() override;

private:
  // TFLite setup
  const int NUM_SOUNDS = 3;
  String _sounds[3];

  // TFLite variables
  //   tflite::MicroErrorReporter tflErrorReporter;
  //   tflite::AllOpsResolver tflOpsResolver;
  const tflite::Model *tflModel = nullptr;
  //   tflite::MicroInterpreter *tflInterpreter = nullptr;
  //   TfLiteTensor *tflInputTensor = nullptr;
  //   TfLiteTensor *tflOutputTensor = nullptr;
};

#endif
