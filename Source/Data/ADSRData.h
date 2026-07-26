/*
  ==============================================================================

    ADSRData.h
    Created: 22 Apr 2023 11:36:20pm
    Author:  albac

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ADSRData : public juce::ADSR {
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;

};