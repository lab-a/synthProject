/*
  ==============================================================================

    ReverbData.cpp
    Created: 3 May 2023 11:19:43am
    Author:  albac

  ==============================================================================
*/

#include "ReverbData.h"


void ReverbData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    reverb.reset();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    reverb.prepare(spec);
    isPrepared = true;
}

void ReverbData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> block{ buffer };
    reverb.process(juce::dsp::ProcessContextReplacing<float> { block });
}

void ReverbData::updateReverb(float roomSize, float damp, float width, float mix, float freeze)
{
    params.roomSize = roomSize;
    params.damping = damp;
    params.width = width;
    params.wetLevel = mix;
    params.dryLevel = 1.0f - mix;
    params.freezeMode = freeze;

    reverb.setParameters(params);
}