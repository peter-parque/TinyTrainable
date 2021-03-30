#ifndef INPUT_SPEECH_H
#define INPUT_SPEECH_H

// include Arduino library
#include <Arduino.h>

// include Input library
#include "Input.h"

// include TinyTrainable library
// #include "TinyTrainable.h"

// include libraries for speech recognition
#ifdef INPUT_SPEECH
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>
#endif

class InputSpeech : public Input {
public:
};

#endif