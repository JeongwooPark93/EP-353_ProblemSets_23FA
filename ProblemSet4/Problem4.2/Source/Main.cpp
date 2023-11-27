/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

/*
 1. Overview:
 
 This program generates a triangle wave audio file with specified parameters and saves it as a WAV file.
 The triangle wave is created using additive synthesis by summing odd harmonics of the fundamental frequency, with alternating signs for each harmonic. The resulting waveform is written to a WAV file with a duration of 1 second.

 2. Purpose:
 
 The purpose of this program is to demonstrate the synthesis of a triangle wave using additive synthesis techniques.
 It serves as an educational example for understanding the composition of complex waveforms and how they can be
 generated programmatically.

 3. How to run:
 
    1) Copy and paste the code into a C++ environment or an IDE that supports JUCE.
    2) Ensure that the JUCE library is properly set up in the project.
    3) Compile and run the program.
    4) The generated triangle wave will be saved as "triangle.wav" in the specified directory.
*/

#include <JuceHeader.h>

// Define global constant values
const float kSampleRate = 44100.0f;
const float kFrequency = 440.0f;
const int kNumHarmonics = 60;
const float kAmplitude = 0.5f;
const float kSec = 1.0f;

//==============================================================================
int main(int argc, char* argv[])
{
    // Check the output file path
    std::string destFilePath;
    destFilePath = "/Users/jeongwoop/Documents/GitHub/Berklee/EP-353_ProblemSets_23FA/ProblemSet4/SoundFiles/triangle.wav";

    // Create a File object from the path
    juce::File destFile(destFilePath);

    // Create an audio format manager and register the wav format
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Calculate the number of samples needed for the specified duration
    int numSamples = static_cast<int>(kSampleRate * kSec);

    // Create a buffer to hold the samples
    juce::AudioBuffer<float> buffer(1, numSamples);  // Single channel for simplicity

    // Compute triangle wave using odd harmonics and alternating signs
    float fundamentalFrequency = kFrequency;
    for (int harmonic = 1; harmonic <= kNumHarmonics; harmonic += 2)
    {
        float harmonicAmplitude = kAmplitude / (harmonic * harmonic);  // Adjust amplitude for odd harmonics
        float sign = (harmonic % 4 == 1) ? 1.0f : -1.0f;  // Alternate signs
        for (int sample = 0; sample < numSamples; ++sample)
        {
            float t = static_cast<float>(sample) / kSampleRate;
            float y = sign * harmonicAmplitude * std::sin(2.0 * M_PI * fundamentalFrequency * harmonic * t);
            buffer.getWritePointer(0)[sample] += y;
        }
    }

    // Create a unique_ptr for the writer with adjusted bit depth
    std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("wav")
        ->createWriterFor(new juce::FileOutputStream(destFile),
            kSampleRate,
            1,   // Single channel
            16,  // Adjust bit depth as needed
            {},
            0));

    if (writer)
    {
        // Write the triangle wave samples to the output file
        writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
    }
    else
    {
        std::cout << "Failed to create a writer for the triangle wave file." << std::endl;
    }
}
