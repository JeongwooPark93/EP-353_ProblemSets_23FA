/*
  ==============================================================================

    SynthSound.h
    Created: 10 Dec 2023 9:31:26am
    Author:  Jeongwoo Park

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
    
};
