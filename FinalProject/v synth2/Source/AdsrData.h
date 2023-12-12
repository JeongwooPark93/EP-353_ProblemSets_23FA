/*
  ==============================================================================

    AdsrData.h
    Created: 10 Dec 2023 9:49:10pm
    Author:  Jeongwoo Park

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void update (const float attack, const float decay, const float sustain, const float release);
    
private:
    juce::ADSR::Parameters adsrParams;
};
