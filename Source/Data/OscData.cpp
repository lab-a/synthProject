/*
  ==============================================================================

    OscData.cpp
    Created: 23 Apr 2023 2:46:09pm
    Author:  albac

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
	fmOsc.prepare(spec);
	prepare(spec);
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
	for (int ch = 0; ch < block.getNumChannels(); ch++) {
		for (int s = 0; s < block.getNumSamples(); s++) {
			fmMod = fmOsc.processSample(block.getSample(ch, s)) * fmDepth;
		}
	}

	process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::setWaveFrecuency(const int midiNoteNumber)
{
	setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
	lastMidiNote = midiNoteNumber;
}

void OscData::setFMParams(const float depth, const float freq)
{
	fmOsc.setFrequency(freq);
	fmDepth = depth;
	auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod;
	setFrequency(currentFreq >= 0 ? currentFreq : currentFreq * (-1.0f));
}

void OscData::setWaveType(const int choice)
{
	switch (choice)
	{
	case 0:
		initialise([](float x) {return std::sin(x); }); //sine wave  onda sinusoidal
		break;

	case 1:
		initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; }); //square wave  onda cuadrada
		break;

	case 2:
		initialise([](float x) { return x / juce::MathConstants<float>::pi; }); //saw wave  onda dentada o onda superficial acústica
		break;

	default:
		jassertfalse; //esto solo pasa si las otras opciones fallan, por lo que hay un error que no haya ninguna opción elegida
		break;
	}
}
