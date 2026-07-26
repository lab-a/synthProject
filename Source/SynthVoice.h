/*
  ==============================================================================

    SynthVoice.h
    Created: 21 Apr 2023 7:36:39pm
    Author:  albac

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/ADSRData.h"
#include "Data/OscData.h"
#include "Data/FilterData.h"
#include "Data/VolPanData.h"
#include "Data/ReverbData.h"

class SynthVoice : public juce::SynthesiserVoice {
public: 
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    
    OscData& getOscillator() { return osc; }
    void updateFilterOsc(const int filterType, const float cutoff, const float resonance);
    void updateAdsrOsc(const float attack, const float decay, const float sustain, const float release);
    void updateModADSROsc(const float attack, const float decay, const float sustain, const float release);
    void updateVolPanOsc(const float volume, const float panning);
    void updateReverb(const float roomSize, const float damp, const float width, const float mix, const float freeze);
    

private:
    
    juce::AudioBuffer<float> synthBuffer;
    OscData osc;
    VolPanData volpan;
    FilterData filter;
    ADSRData adsr;
    ADSRData modAdsr;
    ReverbData reverb;
  

    bool isPrepared{ false };

};