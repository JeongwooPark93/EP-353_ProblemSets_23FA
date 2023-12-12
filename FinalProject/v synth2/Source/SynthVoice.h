/*
  ==============================================================================

    SynthVoice.h
    Created: 10 Dec 2023 9:31:50am
    Author:  Jeongwoo Park

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "OscData.h"
#include "AdsrData.h"
#include "FilterData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void updateFilter (const int filterType, const float frequency, const float resonance);
    
    OscData& getOscillator() { return osc; }
    AdsrData& getAdsr() { return adsr; }
    AdsrData& getFilterAdsr() { return filterAdsr; }
    FilterData& getFilter() { return filter; }
    
private:
    juce::AudioBuffer<float> synthBuffer;
    
    OscData osc;
    AdsrData adsr;
    AdsrData filterAdsr;
    FilterData filter;
    juce::dsp::Gain<float> gain;
    
    bool isPrepared { false };
};
