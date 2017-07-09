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
    int scaleChaosParameterToInt(float rawValue);
    void updateEuclidGrid();
    void updateEuclidLeft();
    void updateEuclidRight();
    bool onEuclidStep(int samplesPerEuclidPatternStep);
    void updateEuclidAmplitudeAndNoteLength(int volumeRampSampleLength, int samplesPer32ndNote);
    
    EuclidGrid::EuclidNote noteStruct;
    EuclidGrid::StereoEuclidNote stereoNoteStruct;
    
    
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
    bool isStereo;
    
    int euclidX;
    int euclidY;
    int euclidDensity;
    int euclidRandomness;
    
    int trem_waveform_indicator;
    int trem_beat_indicator;
    int minBeat;
    int maxBeat;
    bool isPlayingEuclidNote;
    bool leftIsPlayingEuclidNote;
    bool rightIsPlayingEuclidNote;
    int euclidStep;
    int prevEuclidStep;
    int samplesLeftInCurrentEuclidNote;
    int leftSamplesLeftInCurrentEuclidNote;
    int rightSamplesLeftInCurrentEuclidNote;
    
    int gridsCallCountValid;
    int euclidSampleCounter;
    int euclidNoteSampleLen;
    int euclidBeatDivisor;
    int64 randSampleCounter;
    
    BeatIndicators getBeatIndicatorFromParam(float rawValue);
    int beatIndicatorToEuclidBeatDivisor(float rawValue);
    
    //// XXX THIS MAY CAUSE THE STATIC INITIALIZATION ORDER DISASTER!!!!!
    static const int kickIndex = 0;
    static const int snareIndex = 1;
    static const int hhIndex = 2;
    
    static String toggleButtonParameterValueToString(float rawValue);
    static float toggleButtonStringToParameterRawValue(String toggleButtonString);
    
    static String buttonValueToText (float value) {
        return value < 0.5 ? "Off" : "On";
    }
    
    static float buttonTextToValue (const String& text) {
        if (text == "Off")    return 0.0f;
        if (text == "On")  return 1.0f;
        return 0.0f;
    }
    
//    static String euclidParameterToText (float value) {
//        return String((int)roundf(value*126.0f));
//    }
//    
//    static float euclidTextToValue (const String& text) {
//        return
//    }
    

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
    float outAmplitudeLeft;
    float outAmplitudeRight;
    
    float leftVolumeRampMultiplier;
    float rightVolumeRampMultiplier;
    float leftEuclidNoteAmplitude;
    float rightEuclidNoteAmplitude;
    
    
    
    
    // TODO allow this to be perterbed to different lengths
    
    LinearSmoothedValue<float> euclidLinearSmoothedValue;
    
    LinearSmoothedValue<float> leftEuclidLinearSmoothedValue;
    LinearSmoothedValue<float> rightEuclidLinearSmoothedValue;
    
    
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
