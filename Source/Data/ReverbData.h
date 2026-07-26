/*
  ==============================================================================

    ReverbData.h
    Created: 3 May 2023 11:19:43am
    Author:  albac

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ReverbData {
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateReverb(float roomSize, float damp, float width, float mix, float freeze);

private:
    juce::dsp::Reverb::Parameters params;
    juce::dsp::Reverb reverb;
    bool isPrepared{ false };
};