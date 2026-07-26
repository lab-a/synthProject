/*
  ==============================================================================

    StyleSheet.h
    Created: 11 May 2023 8:11:23pm
    Author:  albac

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>



class CustomLNF : public juce::LookAndFeel_V4 {
public:

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider);

};


