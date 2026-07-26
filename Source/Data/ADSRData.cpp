/*
  ==============================================================================

    ADSRData.cpp
    Created: 22 Apr 2023 11:36:20pm
    Author:  albac

  ==============================================================================
*/

#include "ADSRData.h"



void ADSRData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams);
}