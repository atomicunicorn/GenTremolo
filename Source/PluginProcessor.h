/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <math.h>


//==============================================================================
/**
*/
class GenTremoloAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    GenTremoloAudioProcessor();
    ~GenTremoloAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float lfo(float phase, int waveform);
    int getSamplesPerBeat(int beatIndicator, double bpm);
    float getNewTremFrequencyFromBpmGrid();
    
    enum BeatIndicators
    {
        k4th = 1,
        k8th = 2,
        k16th = 3,
        k32nd = 4,
        k64th = 5
    };
    
    enum Waveforms
    {
        kWaveformSine = 1,
        kWaveformTriangle,
        kWaveformSquare,
        kWaveformSquareSlopedEdges,
        kNumWaveforms
    };
    AudioParameterInt* beatParam;
    bool isRandom;

private:
    
    int blockCounter;
    float trem_frequency = 2.0;
    float trem_depth = 1.0;
    int trem_beat_indicator;
    int trem_waveform_indicator;
    float trem_lfo_phase = 0.0;
    float sample_frequency = 1.0/44100.0;
    double currentSampleRate;
    float tremoloBufferPosition;
    float tremoloBufferIncriment;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenTremoloAudioProcessor)
};
