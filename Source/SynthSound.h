/*
  ==============================================================================

    SynthSound.h
    Created: 21 Apr 2023 7:36:57pm
    Author:  albac

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }

};
