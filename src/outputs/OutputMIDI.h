#ifndef OUTPUT_MIDI_H
#define OUTPUT_MIDI_H

// include Arduino library
#include <Arduino.h>

// include Output library
#include "Output.h"

// include TinyTrainable library
#include "TinyTrainable.h"

// TODO: include MIDIPatterns.h
// #include "MIDIPatterns.h"

class OutputMIDI : public Output {

public:
  // constructor
  OutputMIDI();

  // TinyTrainable methods
  virtual void playOutput(int classification) override;

  int _outputPinMIDI = -1;
  int _midiNotes[3];
  byte _midiChannel = 16;
  byte _midiVelocity = 127;

  virtual void setupOutputMIDI(byte midiChannel) override;
  virtual void setMIDINote(int object, int note) override;
  virtual void sendMIDINoteOn(byte channel, byte note,
                                  byte velocity) override;
  virtual void sendMIDINoteOff(byte channel, byte note) override;
  virtual void sendMIDIAllNotesOff(byte channel) override;
  void setupSerialMIDI();

  // TODO: in progress

  // notes for volca beats
  byte noteBassDrum = 36;
  byte noteSnare = 38;
  byte noteClosedHiHat = 42;
  byte noteHiTom = 50;

  int currentStep = 0;
  int totalSteps = 16;

  // 0 - bossanova, 1 - chacha, 2 - samba
  int currentGenre = 2;

  int tempoDelay = 100;
};

#endif
