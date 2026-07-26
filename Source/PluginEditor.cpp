/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "UI/MyColours.h"

//==============================================================================
SynthMultimediaAudioProcessorEditor::SynthMultimediaAudioProcessorEditor (SynthMultimediaAudioProcessor& p)
    : AudioProcessorEditor (&p), 
    audioProcessor (p), 
    osc(audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH"),
    filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRES"),
    adsr("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    modAdsr("Mod Envelope", audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE"),
    volpan(audioProcessor.apvts, "OSC1VOLUME", "OSC1PANNER"),
    reverb(audioProcessor.apvts, "ROOMSIZE", "DAMP", "WIDTH", "MIX", "FREEZE"),
    keyboard(p.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{

    juce::LookAndFeel_V4::setDefaultLookAndFeel(&myCustomLNF);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 700);

    keyboard.setColour(keyboard.mouseOverKeyOverlayColourId, MyColours::violet);
    keyboard.setColour(keyboard.keyDownOverlayColourId, MyColours::violet);
    addAndMakeVisible(keyboard);

    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
    addAndMakeVisible(adsr);
    addAndMakeVisible(modAdsr);
    addAndMakeVisible(volpan);
    addAndMakeVisible(reverb);

    audioProcessor.waveVisualiser.setColours(MyColours::black, MyColours::violet);
    addAndMakeVisible(audioProcessor.waveVisualiser);

}

SynthMultimediaAudioProcessorEditor::~SynthMultimediaAudioProcessorEditor()
{
    juce::LookAndFeel_V4::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void SynthMultimediaAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(50.0f);

    g.fillAll(MyColours::black);
    g.setColour(MyColours::mintcream);
    g.setFont(25.0f);
    g.drawText("Sintetizador", labelSpace.withX(35), juce::Justification::left);

} 

void SynthMultimediaAudioProcessorEditor::resized()
{
    const auto paddingX = 35;
    const auto paddingX2 = 750;
    const auto paddingY = 15;
    const auto paddingY2 = 235;
    auto area = getLocalBounds();

    audioProcessor.waveVisualiser.setBounds(paddingX + 60, paddingY + 50, 600, 125);

    osc.setBounds(paddingX, audioProcessor.waveVisualiser.getBottom(), 205, 210);
    volpan.setBounds(osc.getRight(), osc.getY(), 80, 210);
    filter.setBounds(volpan.getRight(), osc.getY(), 205, 210);
    adsr.setBounds(filter.getRight(), osc.getY(), 240, 210);
    
    reverb.setBounds(paddingX, osc.getBottom(), 490, 210);
    modAdsr.setBounds(reverb.getRight(), osc.getBottom(), 240, 210);

    

    keyboard.setBounds(0, 625, 1000, 75);
    keyboard.setKeyWidth(area.getWidth() / 50.0f);
    keyboard.setLowestVisibleKey(48);

}

