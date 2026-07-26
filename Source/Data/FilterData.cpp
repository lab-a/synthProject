/*
  ==============================================================================

    FilterData.cpp
    Created: 25 Apr 2023 12:41:57pm
    Author:  albac

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    filter.reset();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    filter.prepare(spec);

    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> block{ buffer };
    filter.process(juce::dsp::ProcessContextReplacing<float> { block });

}

void FilterData::updateParameters(const int filterType, const float frequency, const float resonance, const float modulator)
{
    switch (filterType)
    {
    case 0:
        filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;

    case 1:
        filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        break;

    case 2:
        filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
        break;

    }

    float modFreq = frequency * modulator;
    modFreq = std::fmax(modFreq, 20.0f); //va a devolver el mayor valor de estos numeros, evitando asii que sean menos de 20Hz
    modFreq = std::fmin(modFreq, 20000.0f); //lo mismo pero que no sobrepase los 20kHz


    filter.setCutoffFrequency(modFreq);
    filter.setResonance(resonance);

}

void FilterData::reset()
{
    filter.reset();
}
