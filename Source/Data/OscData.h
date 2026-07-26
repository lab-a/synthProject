/*
  ==============================================================================

    OscData.h
    Created: 23 Apr 2023 2:46:09pm
    Author:  albac

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float> {
public: 
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setWaveFrecuency(const int midiNoteNumber);
    void setFMParams(const float depth, const float freq);
    void setWaveType(const int choice);

private:
    juce::dsp::Oscillator<float> fmOsc{ [](float x) {return std::sin(x); } };
    float fmMod { 0.0f };
    float fmDepth { 0.0f };
    int lastMidiNote{ 0 };

};