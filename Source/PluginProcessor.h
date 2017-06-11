/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "EuclidGrid.h"
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
    int getSamplesPerQuarterNote(double bpm, const double sampleRate);
    int getSamplesPerBeat(int beatIndicator, int samplesPerQuarterNote);
    int getEuclidNoteSampleLength(int samplesPerQuarterNote);
    float getUpdatedTremFrequency(double bpm);
    int scaleChaosParameterToInt();
    void updateEuclid();
    bool onEuclidStep(int samplesPerEuclidPatternStep);
    
    EuclidGrid::EuclidNote noteStruct;
    
    
    
    enum BeatIndicators
    {
        k2 = 0,
        k4th = 1,
        k8th = 2,
        k16th = 3,
        k32nd = 4,
        k64th = 5
    };
    
    enum Waveforms
    {
        kWaveformSine = 1,
        kWaveformTriangle = 2,
        kWaveformSquare = 3,
        kWaveformSquareSlopedEdges = 4,
        kNumWaveforms
    };
    
    AudioParameterInt* beatParam;
    bool isRandom;
    bool isEuclid;
    bool isStandard;
    
    int euclidX;
    int euclidY;
    int euclidDensity;
    int euclidRandomness;
    
    int trem_waveform_indicator;
    int trem_beat_indicator;
    int minBeat;
    int maxBeat;
    bool isPlayingEuclidNote;
    int euclidStep;
    int prevEuclidStep;
    int samplesLeftInCurrentEuclidNote;
    
    int gridsCallCountValid;
    int gridSampLen;
    int euclidSampleCounter;
    int euclidNoteSampleLen;
    int64 randSampleCounter;

private:
    /* Audio Parameters */
    AudioProcessorValueTreeState parameters;
    AudioParameterBool* randomParam;
    
    /* Constants */
    const double volumeRampLengthInMs = 4.0; // this is the default fade length in ableton to remove clicks
    const double defaultSampleRate = 44100.0;
    const double defaultSampleFrequency = 1.0 / defaultSampleRate;
    const int euclidStepNoteDivisor = 32; // every 32nd note
    
    /* Other attributes */
    ScopedPointer<EuclidGrid> euclidGrid;
    float volumeRampMultiplier;
    float euclidNoteAmplitude;
    int euclidBeatDivisor;
    
    
    
    // TODO allow this to be perterbed to different lengths
    
    LinearSmoothedValue<float> euclidLinearSmoothedValue;
    
    
    long globalNumSamplesPassed;
    float min_frequency = 0.5;
    float max_frequency = 8.0;
    int blockCounter;
    float trem_frequency = 2.0;
    float next_trem_frequency;
    float trem_depth = 1.0;
    float trem_lfo_phase = 0.0;
    double currentSampleRate;
    float tremoloBufferPosition;
    float tremoloBufferIncriment;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenTremoloAudioProcessor)
};
