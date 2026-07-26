/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"
#include "UI/VolPanComponent.h"
#include "UI/ReverbComponent.h"
#include "UI/StyleSheet.h"

//==============================================================================
/**
*/
class SynthMultimediaAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthMultimediaAudioProcessorEditor (SynthMultimediaAudioProcessor&);
    ~SynthMultimediaAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthMultimediaAudioProcessor& audioProcessor;

    OscComponent osc;
    VolPanComponent volpan;
    ADSRComponent adsr;
    ADSRComponent modAdsr;
    FilterComponent filter;
    ReverbComponent reverb;

    juce::MidiKeyboardComponent keyboard;

    CustomLNF myCustomLNF;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthMultimediaAudioProcessorEditor)
};
