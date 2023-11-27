/*
  ==============================================================================

    The template DAFx file.

  ==============================================================================
*/

/*
 1. Overview:
     This C++ program demonstrates a simple digital audio effect that performs
     bit quantization or reduction on an input audio file. The effect keeps a
     specified number of bits from each 16-bit sample, effectively reducing the
     audio resolution and introducing a lo-fi characteristic.

 2. Purpose:
     The purpose of this program is to showcase the implementation of a basic digital
     audio effect using the JUCE C++ library. The specific effect applied here is
     bit quantization, where the program reads an input WAV file, processes the
     audio data by reducing the bit depth of each sample, and then writes the
     processed audio to a new AIFF file. This program serves as an educational
     resource for understanding audio signal processing and simple effects.

 3. How to Run:
     1) Ensure you have the JUCE library installed.
     2) Replace the sourceFilePath and destFilePath variables with the paths to
        your input audio file (WAV) and the desired output file (AIFF).
     3) Compile and run the program.

 4. Program Structure:
     - The main function reads an input audio file into an AudioBuffer for processing.
     - The process function applies the bit quantization effect to each sample.
     - The keep_bits_from_16 function keeps a specified number of bits from a 16-bit sample.
     - The readSoundFile function reads the input audio file and returns the sample rate.
     - The writeSoundFile function writes the processed audio data to an output file.
 */

#include <iostream>
#include <JuceHeader.h>

// Function prototypes
int readSoundFile(juce::AudioBuffer<float>* buffer);
int writeSoundFile(juce::AudioBuffer<float> buffer, float sampleRate);
void process(juce::AudioBuffer<float> inBuffer, juce::AudioBuffer<float>* outBuffer);
short keep_bits_from_16(short input, int keepBits);

//==============================================================================
int main()
{
    // Read the source file into a buffer for processing
    juce::AudioBuffer<float> inBuffer;
    float sampleRate = readSoundFile(&inBuffer);
    if (!sampleRate) return 1;

    // Create a buffer for processing audio data
    juce::AudioBuffer<float> outBuffer(inBuffer.getNumChannels(), inBuffer.getNumSamples());

    // Process the audio data
    process(inBuffer, &outBuffer);

    // Write the processed audio data to a sound file
    if (writeSoundFile(outBuffer, sampleRate)) return 1;
}

// TODO: Modify this function for your digital audio effect
void process(juce::AudioBuffer<float> inBuffer, juce::AudioBuffer<float>* outBuffer)
{
    for (int sample = 0; sample < inBuffer.getNumSamples(); ++sample)
    {
        for (int channel = 0; channel < inBuffer.getNumChannels(); ++channel)
        {
            // Apply bit quantization/reduction effect
            short inputSample = static_cast<short>(inBuffer.getSample(channel, sample));
            short outputSample = keep_bits_from_16(inputSample, 8); // Keep 8 bits

            // Copy the result to outBuffer
            outBuffer->setSample(channel, sample, static_cast<float>(outputSample));
        }
    }
}

// Keep only specified number of bits from a 16-bit sample
short keep_bits_from_16(short input, int keepBits)
{
    int shift = 16 - keepBits;
    return static_cast<short>((input >> shift) << shift);
}

int readSoundFile(juce::AudioBuffer<float>* buffer)
{
    // Check the input file path
    std::string sourceFilePath;
    sourceFilePath = "/Users/jeongwoop/Documents/GitHub/Berklee/EP-353_ProblemSets_23FA/ProblemSet4/SoundFiles/sine.wav";
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

int writeSoundFile(juce::AudioBuffer<float> buffer, float sampleRate)
{
    // Check the output file path
    std::string destFilePath;
    destFilePath = "/Users/jeongwoop/Documents/GitHub/Berklee/EP-353_ProblemSets_23FA/ProblemSet4/SoundFiles/reduct.aiff";
    juce::File file(destFilePath);

    // Create an audio format manager and register basic formats (especially WAV)
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a unique_ptr for the writer (AIFF format with 24-bit)
    std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("aiff")
        ->createWriterFor(new juce::FileOutputStream(file),
            sampleRate,
            buffer.getNumChannels(),
            24, // Set to 24-bit
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
