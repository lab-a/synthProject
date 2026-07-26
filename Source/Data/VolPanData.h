/*
  ==============================================================================

    VolPanData.h
    Created: 1 May 2023 12:56:51pm
    Author:  albac

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class VolPanData {
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const float volume, const float panning);
    void reset();

private:
    juce::dsp::Gain<float> gain;
    juce::dsp::Panner<float> pan;
    bool isPrepared{ false };

};