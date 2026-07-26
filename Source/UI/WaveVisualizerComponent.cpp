/*
  ==============================================================================

    WaveVisualizerComponent.cpp
    Created: 26 Apr 2023 11:22:27am
    Author:  albac

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveVisualizerComponent.h"

//==============================================================================
WaveVisualizerComponent::WaveVisualizerComponent() : AudioVisualiserComponent(2)
{
    setBufferSize(248);
    setSamplesPerBlock(256);
    setColours(juce::Colours::black, juce::Colours::mediumpurple);

}

WaveVisualizerComponent::~WaveVisualizerComponent()
{
}


