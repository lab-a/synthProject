/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthMultimediaAudioProcessor::SynthMultimediaAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, &undo, "Parameters", createParams()), waveVisualiser(1)
#endif
{

    waveVisualiser.setSamplesPerBlock(8);
    waveVisualiser.setBufferSize(8192);

    
    keyboardState.reset();

    synth1.clearVoices();

    for (int i = 0; i < 5; i++) {
        synth1.addVoice(new SynthVoice());
    }

    synth1.clearSounds();
    synth1.addSound(new SynthSound());
    

}

SynthMultimediaAudioProcessor::~SynthMultimediaAudioProcessor()
{
    //no hace falta llamar a los constructores de synthsound o synthvoice puesto que segun la documentacion se destruyen solos
}

//==============================================================================
const juce::String SynthMultimediaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthMultimediaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthMultimediaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthMultimediaAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthMultimediaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthMultimediaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthMultimediaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthMultimediaAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthMultimediaAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthMultimediaAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthMultimediaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth1.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth1.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth1.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

    waveVisualiser.clear();
}

void SynthMultimediaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthMultimediaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthMultimediaAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth1.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth1.getVoice(i))) {

            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& fmDepth = *apvts.getRawParameterValue("OSC1FMDEPTH");
            auto& fmFreq = *apvts.getRawParameterValue("OSC1FMFREQ");

            auto& osc1Volume = *apvts.getRawParameterValue("OSC1VOLUME");
            auto& osc1Panner = *apvts.getRawParameterValue("OSC1PANNER");

            auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
            auto& cutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
            auto& resonance = *apvts.getRawParameterValue("FILTERRES");

            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            auto& modAttack = *apvts.getRawParameterValue("MODATTACK");
            auto& modDecay = *apvts.getRawParameterValue("MODDECAY");
            auto& modSustain = *apvts.getRawParameterValue("MODSUSTAIN");
            auto& modRelease = *apvts.getRawParameterValue("MODRELEASE");

            auto& roomSize = *apvts.getRawParameterValue("ROOMSIZE");
            auto& damping = *apvts.getRawParameterValue("DAMP");
            auto& width = *apvts.getRawParameterValue("WIDTH");
            auto& mix = *apvts.getRawParameterValue("MIX");
            auto& freeze = *apvts.getRawParameterValue("FREEZE");

            voice->getOscillator().setWaveType(oscWaveChoice);
            voice->getOscillator().setFMParams(fmDepth, fmFreq);
            voice->updateVolPanOsc(osc1Volume, osc1Panner);
            voice->updateFilterOsc(filterType.load(), cutoff.load(), resonance.load());
            voice->updateAdsrOsc(attack.load(), decay.load(), sustain.load(), release.load()); //se les añade .load() porque son valores atómicos y necesita más "energía" para procesar
            voice->updateModADSROsc(modAttack, modDecay, modSustain, modRelease);
            voice->updateReverb(roomSize, damping, width, mix, freeze);
            
        }
    }


    juce::MidiMessage msg;
    int ignore;

    for (juce::MidiBuffer::Iterator it(midiMessages); it.getNextEvent(msg, ignore);) {
        if (msg.isNoteOn()) {
            keyboardState.noteOn(msg.getChannel(), msg.getNoteNumber(), msg.getVelocity() / 127.0f);
        }
        else if (msg.isNoteOff()) {
            keyboardState.noteOff(msg.getChannel(), msg.getNoteNumber(), msg.getVelocity() / 127.0f);
        }
    }

    synth1.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    waveVisualiser.pushBuffer(buffer);
}

//==============================================================================
bool SynthMultimediaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthMultimediaAudioProcessor::createEditor()
{
    return new SynthMultimediaAudioProcessorEditor (*this);
}

//==============================================================================
void SynthMultimediaAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthMultimediaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthMultimediaAudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout SynthMultimediaAudioProcessor::createParams() {

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //OSC1 select
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray{ "Sine", "Square", "Saw" }, 0));

    //Volume and Panning
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1VOLUME", "Osc1 Volume", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1PANNER", "Osc1 Panner", juce::NormalisableRange<float>{ -1.0f, 1.0f, 0.01}, 0.0f));

    //FM1 Frequency
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ", "FM Frequency", juce::NormalisableRange<float>{ 0.0f, 1000.0f, 0.01, 0.3f}, 0.0f));  //el 0.3, es el skew factor, hace que el slider sea logarítmico y tenga más precisión en el rango de números más bajos
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "FM Depth", juce::NormalisableRange<float>{ 0.0f, 1000.0f, 0.01, 0.3f}, 0.0f));

    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>{ 0.1f, 3.0f, 0.01f }, 0.4f));

    //Filter ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODATTACK", "Modulator Attack", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODDECAY", "Modulator Decay", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODSUSTAIN", "Modulator Sustain", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODRELEASE", "Modulator Release", juce::NormalisableRange<float>{ 0.1f, 3.0f, 0.01f }, 0.4f));

    //Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray{ "Low-Pass", "Band-Pass", "High-Pass" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff", juce::NormalisableRange<float>{ 20.0f, 20000.0f, 0.1f, 0.6f }, 200.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Filter Resonance", juce::NormalisableRange<float>{ 1.0f, 10.0f, 0.1f }, 1.0f));

    //Reverb
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ROOMSIZE", "Room Size", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DAMP", "Damping", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WIDTH", "Width", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MIX", "Wet/Dry Mix", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FREEZE", "Freeze", juce::NormalisableRange<float>{ -1.0f, 1.0f, 0.01f }, 0.0f));



    return { params.begin(), params.end() };

}
