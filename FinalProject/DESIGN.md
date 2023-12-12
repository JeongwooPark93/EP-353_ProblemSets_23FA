# Vsynth2 Design Document

## Overview

Vsynth2 is a virtual synthesizer plugin developed using the JUCE framework. The project aims to provide users with a versatile and customizable synthesizer capable of generating a wide range of sounds through the manipulation of oscillators, envelopes, and filters. The long-term goal includes exploring possibilities for emulating iconic analog synthesizers like Nord and Prophet, serving as a foundation for future replication projects.

## Architecture

### 1. Plugin Processor (`PluginProcessor.h` and `PluginProcessor.cpp`)

- **Vsynth2AudioProcessor Class:**
  - Derives from `juce::AudioProcessor`.
  - Manages the core audio processing logic.
  - Handles voice management, MIDI event reception, and parameter control.
  - Utilizes `AudioProcessorValueTreeState` for parameter management.

### 2. Plugin Editor (`PluginEditor.h` and `PluginEditor.cpp`)

- **Vsynth2AudioProcessorEditor Class:**
  - Derives from `juce::AudioProcessorEditor`.
  - Creates the graphical user interface (GUI) for the plugin.
  - Includes components for oscillator controls, ADSR envelopes, and filter settings.
  - Organizes the layout of GUI components.

### 3. Synthesizer Logic (`SynthVoice.h` and `SynthVoice.cpp`)

- **SynthVoice Class:**
  - Derives from `juce::SynthesiserVoice`.
  - Manages the logic for generating sound.
  - Includes oscillators, ADSR envelopes, and filter updates.

- **SynthSound Class:**
  - Derives from `juce::SynthesiserSound`.
  - Represents a specific sound for the synthesizer.
  - Defines which MIDI notes the synthesizer responds to.

### 4. GUI Components (`OscComponent`, `AdsrComponent`, `FilterComponent`)

- **OscComponent Class:**
  - Manages the oscillator controls in the GUI.

- **AdsrComponent Class:**
  - Manages the ADSR envelope controls in the GUI.

- **FilterComponent Class:**
  - Manages the filter controls in the GUI.

## MIDI Input

The Vsynth2 plugin is designed to accept MIDI input for controlling various parameters. MIDI input is enabled through the `acceptsMidi()` function in the `Vsynth2AudioProcessor` class. Additionally, the Projucer or similar project configuration tools should be used to ensure that MIDI input is allowed.

## Parameterization

Vsynth2 allows users to customize the synthesis parameters through the GUI. The parameters include oscillator wave type, FM (Frequency Modulation) settings, ADSR envelope parameters, filter settings, and more. These parameters are managed using the `AudioProcessorValueTreeState` class.

## Building and Integration

To build and integrate Vsynth2 into a host application, follow these steps:

1. Set the desired MIDI input configuration in the Projucer or project configuration.
2. Build the plugin using the appropriate build tools for your platform.
3. Integrate the generated plugin into your preferred digital audio workstation (DAW) or host application.

## Future Goals

The design of Vsynth2 incorporates the intention to explore and replicate the sound characteristics of iconic analog synthesizers such as Nord and Prophet. Future iterations of this project may involve refining the emulation algorithms and introducing specific features to emulate the unique qualities of these synthesizers.

## Conclusion

Vsynth2 provides a flexible and customizable virtual synthesizer experience for users, allowing them to explore various sonic possibilities through parameter adjustments and MIDI input control. The modular architecture ensures ease of maintenance and further development. The project's future goals involve expanding its capabilities to emulate renowned analog synthesizers.
