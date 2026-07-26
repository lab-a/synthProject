/*
  ==============================================================================

    VolPanComponent.h
    Created: 1 May 2023 12:57:21pm
    Author:  albac

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class VolPanComponent  : public juce::Component
{
public:
    VolPanComponent(juce::AudioProcessorValueTreeState& apvts, juce::String volumeId, juce::String pannerId);
    ~VolPanComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider volumeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;
    juce::Label volumeLabel{ "Volume", "Volume" };


    juce::Slider pannerSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pannerAttachment;
    juce::Label pannerLabel{ "Panner", "Panner" };

    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolPanComponent)
};
