/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 3 May 2023 11:21:22am
    Author:  albac

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"
#include "MyColours.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String roomSizeId, juce::String dampId, juce::String widthId, juce::String mixId, juce::String freezeId)
{
    setSliderWithLabel(roomSizeSlider, roomSizeLabel, apvts, roomSizeId, roomSizeAttachment);
    setSliderWithLabel(dampSlider, dampLabel, apvts, dampId, dampAttachment);
    setSliderWithLabel(widthSlider, widthLabel, apvts, widthId, widthAttachment);
    setSliderWithLabel(mixSlider, mixLabel, apvts, mixId, mixAttachment);
    setSliderWithLabel(freezeSlider, freezeLabel, apvts, freezeId, freezeAttachment);
}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(MyColours::black);
    g.setColour(MyColours::mintcream);
    g.setFont(20.0f);
    g.drawText("Reverb", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void ReverbComponent::resized()
{
    const auto startY = 90;
    const auto sliderWidth = 95;
    const auto sliderHeight = 95;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;


    roomSizeSlider.setBounds(5, startY, sliderWidth, sliderHeight);
    roomSizeLabel.setBounds(roomSizeSlider.getX(), roomSizeSlider.getY() - labelYOffset, roomSizeSlider.getWidth(), labelHeight);

    dampSlider.setBounds(roomSizeSlider.getRight(), startY, sliderWidth, sliderHeight);
    dampLabel.setBounds(dampSlider.getX(), dampSlider.getY() - labelYOffset, dampSlider.getWidth(), labelHeight);

    widthSlider.setBounds(dampSlider.getRight(), startY, sliderWidth, sliderHeight);
    widthLabel.setBounds(widthSlider.getX(), widthSlider.getY() - labelYOffset, widthSlider.getWidth(), labelHeight);

    mixSlider.setBounds(widthSlider.getRight(), startY, sliderWidth, sliderHeight);
    mixLabel.setBounds(mixSlider.getX(), mixSlider.getY() - labelYOffset, mixSlider.getWidth(), labelHeight);

    freezeSlider.setBounds(mixSlider.getRight(), startY, sliderWidth, sliderHeight);
    freezeLabel.setBounds(freezeSlider.getX(), freezeSlider.getY() - labelYOffset, freezeSlider.getWidth(), labelHeight);
}

void ReverbComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment)
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
