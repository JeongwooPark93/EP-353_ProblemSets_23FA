/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

/*
  1. Overview:
  This program reads an input WAV file, reverses its audio samples, and writes the reversed samples to an output WAV file.
  It utilizes the JUCE library for audio file manipulation, and the reversal process is performed channel-wise.

  2. Purpose:
  The purpose of this program is to demonstrate simple audio file manipulation, specifically reversing the samples of a WAV file.
  It serves as an example of using JUCE for reading and writing audio files and implementing a basic audio processing operation.

  3. How to run:
      1) Set the 'sourceFilePath' variable to the path of the input WAV file.
      2) Set the 'destFilePath' variable to the desired path for the output reversed WAV file.
      3) Copy and paste the code into a C++ environment or an IDE that supports JUCE.
      4) Ensure that the JUCE library is properly set up in the project.
      5) Compile and run the program.
      6) The reversed audio will be saved as "ReverseSN.wav" in the specified directory.
 */

#include <JuceHeader.h>

//==============================================================================
int main (int argc, char* argv[])
{
    // Check the input file path
    std::string sourceFilePath;
    sourceFilePath="/Users/jeongwoop/Documents/GitHub/Berklee/EP-353_ProblemSets_23FA/ProblemSet4/SoundFiles/SN.wav";
    
    // Check the output file path
    std::string destFilePath;
    destFilePath="/Users/jeongwoop/Documents/GitHub/Berklee/EP-353_ProblemSets_23FA/ProblemSet4/SoundFiles/ReverseSN.wav";
    
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
        
        // Reverse the samples in the buffer
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel){
            float* channelData = buffer.getWritePointer(channel);
            std::reverse(channelData, channelData + buffer.getNumSamples());
        }
        
        // Create a unique_ptr for the writer
        std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("wav")->createWriterFor(new juce::FileOutputStream(destFile), reader->sampleRate, reader->numChannels, 16, {}, 0));
        
        if(writer)
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
