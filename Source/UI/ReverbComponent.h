/*
  ==============================================================================

    ReverbComponent.h
    Created: 3 May 2023 11:21:22am
    Author:  albac

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String roomSizeId, juce::String dampId, juce::String widthId, juce::String mixId, juce::String freezeId);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider roomSizeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
    juce::Label roomSizeLabel{ "Room Size", "Room Size" };


    juce::Slider dampSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampAttachment;
    juce::Label dampLabel{ "Damping", "Damping" };

    juce::Slider widthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthAttachment;
    juce::Label widthLabel{ "Width", "Width" };


    juce::Slider mixSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
    juce::Label mixLabel{ "Wet/Dry Mix", "Wet/Dry Mix" };

    juce::Slider freezeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freezeAttachment;
    juce::Label freezeLabel{ "Freeze", "Freeze" };

    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
