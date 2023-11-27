/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

/*
1. Program Overview:
 This program reads a sine wave from a WAV file, applies a linear Attack-Decay (AD)
 envelope to the samples, and saves the resulting sound to a new WAV file. The purpose
 is to demonstrate the application of an AD envelope to modify the amplitude over time.

2. Purpose of the Program:
 - Read a sine wave from a WAV file.
 - Apply a linear Attack-Decay (AD) envelope to the samples.
 - Save the enveloped sound to a new WAV file.

3. How to Run:
     1) Replace the 'sourceFilePath' and 'destFilePath' variables with the paths to
        your input sine wave file and the desired output file, respectively.
     2) Compile and run the program.
     3) The program will read the sine wave, apply an AD envelope, and save the
        enveloped sound to the specified output file.

4. Note: The envelope starts from 0, reaches its peak at 10% of the total duration
       (attack time), and then decays to 0 towards the end of the samples.
 */

#include <JuceHeader.h>

//==============================================================================
int main(int argc, char* argv[])
{
    // Check the input file path
    std::string sourceFilePath;
    sourceFilePath = "/Users/jeongwoop/Documents/GitHub/Berklee/EP-353_ProblemSets_23FA/ProblemSet4/SoundFiles/sine.wav";

    // Check the output file path
    std::string destFilePath;
    destFilePath = "/Users/jeongwoop/Documents/GitHub/Berklee/EP-353_ProblemSets_23FA/ProblemSet4/SoundFiles/enveloped.wav";

    // Create a File object from the path
    juce::File sourceFile(sourceFilePath);
    juce::File destFile(destFilePath);

    // Create an audio format manager and register the wav format
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a unique_ptr for the reader
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(sourceFile));

    if (reader)
    {
        // Create a buffer to hold the samples
        juce::AudioBuffer<float> buffer(reader->numChannels, static_cast<int>(reader->lengthInSamples));

        // Read the samples into the buffer
        reader->read(&buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);

        // Generate linear AD envelope
        const int attackSamples = static_cast<int>(0.1 * reader->sampleRate);  // 10% of the total duration for attack
        const int decaySamples = buffer.getNumSamples() - attackSamples;       // Remaining samples for decay

        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            float* channelData = buffer.getWritePointer(channel);

            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                // Linear interpolation for attack and decay
                float envelopeValue;
                if (sample < attackSamples)
                {
                    envelopeValue = (1.0f / attackSamples) * sample;
                }
                else
                {
                    envelopeValue = 1.0f - ((1.0f / decaySamples) * (sample - attackSamples));
                }

                // Apply envelope to the sample
                channelData[sample] *= envelopeValue;
            }
        }

        // Create a unique_ptr for the writer
        std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("wav")->createWriterFor(
            new juce::FileOutputStream(destFile), reader->sampleRate, reader->numChannels, 16, {}, 0));

        if (writer)
        {
            // Write the samples from the buffer to the destination file
            writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
        }
        else
        {
            std::cout << "Failed to create a writer for the destination file." << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to read the source wave file." << std::endl;
    }
}
