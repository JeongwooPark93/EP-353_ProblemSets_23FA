/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

/*
  1. Overview:
  This program generates a sine wave with a specified frequency and applies a tremolo effect using a low-frequency oscillator (LFO).
  The resulting audio is written to a WAV file, demonstrating basic audio synthesis with amplitude modulation (tremolo).

  2. Purpose:
  The purpose of this program is to showcase how to generate a simple audio waveform, modulate its amplitude with a tremolo effect,
  and save the resulting audio to a file using the JUCE library. It serves as an example of basic audio synthesis and modulation.

  3. How to run:
      1) Set the 'destFilePath' variable to the desired path for the output WAV file.
      2) Copy and paste the code into a C++ environment or an IDE that supports JUCE.
      3) Ensure that the JUCE library is properly set up in the project.
      4) Compile and run the program.
      5) The generated audio with tremolo effect will be saved as "tremolo.wav" in the specified directory.
*/

#include <JuceHeader.h>

// Define constant values as global variables for ease of access
const float kSampleRate = 44100.0f;
const float kSec = 1.0f;
const float kNumFrames = kSampleRate * kSec;
const int kNumChannels = 2;
const float kFrequency = 250.0f;  // Updated frequency for the sine wave
const float kAmplitude = 0.25f;

// Define tremolo parameters
const float kTremoloFrequency = 2.0f;  // Frequency of the LFO for tremolo

//==============================================================================
int main(int argc, char* argv[])
{
    // Check the output file path
        std::string destFilePath;
        destFilePath = "/Users/jeongwoop/Documents/GitHub/Berklee/EP-353_ProblemSets_23FA/ProblemSet4/SoundFiles/tremolo.wav";

    // Create a File object from the path
    juce::File destFile(destFilePath);

    // Create an audio format manager and register the wav format
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a buffer to hold the samples
    juce::AudioBuffer<float> buffer(kNumChannels, kNumFrames);

    // Compute sine wave with tremolo
    float lfoPhase = 0.0f;

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            // Compute LFO signal (unipolar positive)
            float lfoValue = 0.5f * (1.0f + std::sin(2.0 * juce::MathConstants<float>::pi * kTremoloFrequency / kSampleRate * sample + lfoPhase));

            // Compute A sin(2πft+φ) and apply tremolo
            float y = kAmplitude * std::sin(2.0 * juce::MathConstants<float>::pi * kFrequency / kSampleRate * sample);
            channelData[sample] = y * lfoValue;  // Apply tremolo

            // Update LFO phase
            lfoPhase += 2.0 * juce::MathConstants<float>::pi * kTremoloFrequency / kSampleRate;
            if (lfoPhase >= 2.0 * juce::MathConstants<float>::pi)
                lfoPhase -= 2.0 * juce::MathConstants<float>::pi;
        }
    }

    // Create a unique_ptr for the writer
    std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("wav")
        ->createWriterFor(new juce::FileOutputStream(destFile),
            kSampleRate,
            kNumChannels,
            16,
            {},
            0));

    if (writer)
    {
        // Write the mixed samples to the output file
        writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
    }
    else
    {
        std::cout << "Failed to create a writer for the mixed file." << std::endl;
    }
}
