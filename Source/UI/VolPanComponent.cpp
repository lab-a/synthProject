/*
  ==============================================================================

    VolPanComponent.cpp
    Created: 1 May 2023 12:57:21pm
    Author:  albac

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VolPanComponent.h"
#include "MyColours.h"

//==============================================================================
VolPanComponent::VolPanComponent(juce::AudioProcessorValueTreeState& apvts, juce::String volumeId, juce::String pannerId)
{
    setSliderWithLabel(volumeSlider, volumeLabel, apvts, volumeId, volumeAttachment);
    setSliderWithLabel(pannerSlider, pannerLabel, apvts, pannerId, pannerAttachment);

}

VolPanComponent::~VolPanComponent()
{
}

void VolPanComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(MyColours::black);
    g.setColour(MyColours::mintcream);
    g.setFont(20.0f);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void VolPanComponent::resized()
{
    const auto startY = 50;
    const auto sliderWidth = 70;
    const auto sliderHeight = 65;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

 
    volumeSlider.setBounds(5, startY, sliderWidth, sliderHeight);
    volumeLabel.setBounds(volumeSlider.getX(), volumeSlider.getY() - labelYOffset, volumeSlider.getWidth(), labelHeight);

    pannerSlider.setBounds(5, volumeSlider.getBottom() + 20, sliderWidth, sliderHeight);
    pannerLabel.setBounds(pannerSlider.getX(), pannerSlider.getY() - labelYOffset, pannerSlider.getWidth(), labelHeight);

}

void VolPanComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);


    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
