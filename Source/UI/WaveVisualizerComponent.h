/*
  ==============================================================================

    WaveVisualizerComponent.h
    Created: 26 Apr 2023 11:22:27am
    Author:  albac

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveVisualizerComponent  : public juce::AudioVisualiserComponent
{
public:
    WaveVisualizerComponent();
    ~WaveVisualizerComponent();

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveVisualizerComponent)
};
