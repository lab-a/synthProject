/*
  ==============================================================================

    VolPanData.cpp
    Created: 1 May 2023 12:56:51pm
    Author:  albac

  ==============================================================================
*/

#include "VolPanData.h"

void VolPanData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    gain.reset();
    pan.reset();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    gain.prepare(spec);
    pan.prepare(spec);

    isPrepared = true;
}

void VolPanData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> block{ buffer };
    gain.process(juce::dsp::ProcessContextReplacing<float> { block });
    pan.process(juce::dsp::ProcessContextReplacing<float> { block });

}

void VolPanData::updateParameters(const float volume, const float panning)
{
    gain.setGainLinear(volume);
    pan.setPan(panning);
}

void VolPanData::reset()
{
    gain.reset();
    pan.reset();
}
