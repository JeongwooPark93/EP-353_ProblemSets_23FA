/*
  ==============================================================================

    The template DAFx file.

  ==============================================================================
*/

/*
 1. Overview:
  This program implements a noise gate effect for audio processing.
  It reads an input WAV file, applies a noise gate to attenuate signals below a specified threshold,
  and saves the processed audio as a new WAV file. The noise gate threshold is set to ±0.02 by default.
  Adjust the 'threshold' variable in the 'main' function to control the sensitivity of the noise gate effect.
 
 2. Purpose:
  The purpose of this program is to demonstrate a simple noise gate effect,
  a common audio processing technique used to reduce low-amplitude noise in audio recordings.
  The noise gate works by attenuating signals below a certain amplitude threshold, effectively reducing
  background noise during silent or low-amplitude sections of the audio.
 
 3. How to Run:
  1) Update the 'sourceFilePath' and 'destFilePath' variables with the paths to your input and output WAV files.
  2) Compile and run the program.
  3) The processed audio with the noise gate effect will be saved to the specified output file.
 
 */

#include <JuceHeader.h>

// Function prototypes
int readSoundFile(juce::AudioBuffer<float>* buffer);
int writeSoundFile(juce::AudioBuffer<float> buffer, float sampleRate);
void process(juce::AudioBuffer<float> inBuffer, juce::AudioBuffer<float>* outBuffer, float threshold);

//==============================================================================
int main()
{
    // Read the source file into a buffer for processing
    juce::AudioBuffer<float> inBuffer;
    float sampleRate = readSoundFile(&inBuffer);
    if (!sampleRate) return 1;

    // Create a buffer for processing audio data
    juce::AudioBuffer<float> outBuffer(inBuffer.getNumChannels(), inBuffer.getNumSamples());

    // Set the noise gate threshold
    float threshold = 0.02f;

    // Process the audio data with the noise gate effect
    process(inBuffer, &outBuffer, threshold);

    // Write the processed audio data to a sound file
    if (writeSoundFile(outBuffer, sampleRate)) return 1;
}

// Noise gate effect: attenuate signals below the threshold
void process(juce::AudioBuffer<float> inBuffer, juce::AudioBuffer<float>* outBuffer, float threshold)
{
    for (int sample = 0; sample < inBuffer.getNumSamples(); ++sample)
    {
        for (int channel = 0; channel < inBuffer.getNumChannels(); ++channel)
        {
            // Apply the noise gate effect
            if (std::abs(inBuffer.getReadPointer(channel)[sample]) > threshold)
            {
                // Copy the sample to the output buffer
                outBuffer->getWritePointer(channel)[sample] = inBuffer.getReadPointer(channel)[sample];
            }
            else
            {
                // If below the threshold, attenuate the signal
                outBuffer->getWritePointer(channel)[sample] = 0.0f;
            }
        }
    }
}

int readSoundFile (juce::AudioBuffer<float> *buffer)
{
    // Check the input file path
    std::string sourceFilePath;
    sourceFilePath = "/Users/jeongwoop/Documents/GitHub/Berklee/EP-353_ProblemSets_23FA/ProblemSet4/SoundFiles/noisy.wav";
    juce::File file(sourceFilePath);
    
    // Create an audio format manager and register basic formats (especially WAV)
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a unique_ptr for the reader
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
    
    // Check if the reader was created
    if (reader)
    {
        // Set the size of buffer
        buffer->setSize(reader->numChannels, static_cast<int>(reader->lengthInSamples));
        
        // Read the samples from the first file into the buffer
        bool success = reader->read(buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);

        // Return the sample rate for this file if reading was successful
        if (success) return reader->sampleRate;
        
        std::cout << "Failed to copy samples into the buffer from the source wave file." << std::endl;
        return 0;
    }
    
    std::cout << "Failed to read the source wave file." << std::endl;
    return 0;
}

int writeSoundFile (juce::AudioBuffer<float> buffer, float sampleRate)
{
    // Check the output file path
        std::string destFilePath;
        destFilePath = "/Users/jeongwoop/Documents/GitHub/Berklee/EP-353_ProblemSets_23FA/ProblemSet4/SoundFiles/noisegate.wav";
    juce::File file(destFilePath);
    
    // Create an audio format manager and register basic formats (especially WAV)
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    // Create a unique_ptr for the writer (WAV format)
    std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("wav")
                                                    ->createWriterFor(new juce::FileOutputStream(file),
                                                                       sampleRate,
                                                                       buffer.getNumChannels(),
                                                                       16,
                                                                       {},
                                                                       0));
    // Check if the writer was created
    if (writer)
    {
        // Write the mixed samples to the output file
        bool success = writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
        if (success) return 0;
        
        std::cout << "Failed to write samples into the buffer to the destination wave file." << std::endl;
        return 1;
    }
    
    std::cout << "Failed to create a writer for the destination file." << std::endl;
    return 1;
}
