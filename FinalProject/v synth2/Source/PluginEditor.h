/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AdsrComponent.h"
#include "OscComponent.h"
#include "FilterComponent.h"

//==============================================================================
/**
*/
class Vsynth2AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Vsynth2AudioProcessorEditor (Vsynth2AudioProcessor&);
    ~Vsynth2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Vsynth2AudioProcessor& audioProcessor;
    
    OscComponent osc;
    AdsrComponent adsr;
    AdsrComponent filterAdsr;
    FilterComponent filter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Vsynth2AudioProcessorEditor)
};
