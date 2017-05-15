/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
GenTremoloAudioProcessor::GenTremoloAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Set default values:
    trem_beat_indicator = k4th;
    trem_frequency = 2.0;
    trem_depth = 1.0;
    trem_waveform_indicator = kWaveformSquareSlopedEdges; //kWaveformSine;
    trem_lfo_phase = 0.0;
    sample_frequency = 1.0/44100.0; // TODO update this to pull sample rate from host
    isRandom = false;
    blockCounter = 1;
    
    sampleCounter = 0;
    
    addParameter(beatParam = new AudioParameterInt ("beatParam", // parameter ID
                                                 "Beat", // parameter name
                                                 1,   // mininum value
                                                 5,   // maximum value
                                                 1)); // default value)
}

GenTremoloAudioProcessor::~GenTremoloAudioProcessor()
{
}

//==============================================================================
const String GenTremoloAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GenTremoloAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GenTremoloAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double GenTremoloAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GenTremoloAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GenTremoloAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GenTremoloAudioProcessor::setCurrentProgram (int index)
{
}

const String GenTremoloAudioProcessor::getProgramName (int index)
{
    return {};
}

void GenTremoloAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GenTremoloAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GenTremoloAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GenTremoloAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

// Function for calculating LFO waveforms. Phase runs from 0-1, output is scaled
// from 0 to 1 (note: not -1 to 1 as would be typical of sine).
float GenTremoloAudioProcessor::lfo(float phase, int waveform)
{
    switch(waveform)
    {
    case kWaveformTriangle:
        if(phase < 0.25f)
            return 0.5f + 2.0f*phase;
        else if(phase < 0.75f)
            return 1.0f - 2.0f*(phase - 0.25f);
        else
            return 2.0f*(phase-0.75f);
    case kWaveformSquare:
        if(phase < 0.5f)
            return 1.0f;
        else
            return 0.0f;
    case kWaveformSquareSlopedEdges:
        if(phase < 0.48f)
            return 1.0f;
        else if(phase < 0.5f)
            return 1.0f - 50.0f*(phase - 0.48f);
        else if(phase < 0.98f)
            return 0.0f;
        else
            return 50.0f*(phase - 0.98f);
    case kWaveformSine:
    default:
        return 0.5f + 0.5f*sinf(2.0 * M_PI * phase);
    }
}

// TODO may need to return a double instead of an int
int GenTremoloAudioProcessor::getSamplesPerBeat(int beatIndicator, double bpm) {
    double sampleRate = GenTremoloAudioProcessor::getSampleRate();
    if (bpm <= 0)
        return 60.0*sampleRate/120.0;
    double quarterNoteSampleLength = 60.0*sampleRate/bpm;
    switch (beatIndicator) {
        case k4th:
            return quarterNoteSampleLength;
        case k8th:
            return quarterNoteSampleLength/2;
        case k16th:
            return quarterNoteSampleLength/4;
        case k32nd:
            return quarterNoteSampleLength/8;
        case k64th:
            return quarterNoteSampleLength/16;
        default:
            return quarterNoteSampleLength;
    }
}

// TODO implement
float GenTremoloAudioProcessor::getNewTremFrequencyFromBpmGrid() {
    return 0.0;
}

void GenTremoloAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    
    const int totalNumInputChannels  = GenTremoloAudioProcessor::getTotalNumInputChannels();
    const int totalNumOutputChannels = GenTremoloAudioProcessor::getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();
    AudioPlayHead* const playHead = getPlayHead();
    AudioPlayHead::CurrentPositionInfo result = {};
    double bpm = 120.0;
    if (playHead != nullptr) {
        if (GenTremoloAudioProcessor::getPlayHead()->getCurrentPosition(result))
            bpm = result.bpm;
    }
    
    int samplesPerBeat = getSamplesPerBeat(trem_beat_indicator, bpm);
    // TODO create anchor sample and check if hit a multiple of the samples perbeat after anchor sample
    // TODO randomly update the new tremolo frequency / trem beat indicator
    
    float temp_trem_lfo_phase_copy;
    float* channelDataLeft = buffer.getWritePointer(0);
    float* channelDataRight = buffer.getWritePointer(1);
    temp_trem_lfo_phase_copy = trem_lfo_phase;
    for (int i = 0; i < numSamples; i++) {
        const float inLeft = channelDataLeft[i];
        const float inRight = channelDataRight[i];
        if (isRandom && (sampleCounter % samplesPerBeat) == 0) {
            trem_frequency = next_trem_frequency;
            trem_beat_indicator = BeatIndicators(rand() % 5);
            next_trem_frequency = getUpdatedTremFrequency(bpm);
            sampleCounter = 0;
        }
        channelDataLeft[i] = inLeft * (1.0f - trem_depth*lfo(temp_trem_lfo_phase_copy, trem_waveform_indicator));
        channelDataRight[i] = inRight * (1.0f - trem_depth*lfo(temp_trem_lfo_phase_copy, trem_waveform_indicator));
        // Update the carrier and LFO phases, keeping them in the range 0-1
        temp_trem_lfo_phase_copy += trem_frequency*sample_frequency;
        if(temp_trem_lfo_phase_copy >= 1.0)
            temp_trem_lfo_phase_copy -= 1.0;
        sampleCounter++;
    }
    
    // Having made a local copy of the state variables for each channel, now transfer the result
    // back to the main state variable so they will be preserved for the next call of processBlock()
    
    trem_lfo_phase = temp_trem_lfo_phase_copy;
    
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

float GenTremoloAudioProcessor::getUpdatedTremFrequency(double bpm) {
    switch (trem_beat_indicator) {
        case k4th:
            return bpm / 60.0;
        case k8th:
            return bpm / 30.0;
        case k16th:
            return bpm / 15.0;
        case k32nd:
            return bpm / 7.5;
        case k64th:
            return bpm / 3.75;
        default:
            return bpm / 60.0;
    }
}

//==============================================================================
bool GenTremoloAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GenTremoloAudioProcessor::createEditor()
{
    return new GenTremoloAudioProcessorEditor (*this);
}

//==============================================================================
void GenTremoloAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    MemoryOutputStream (destData, true).writeInt (*beatParam);
}

void GenTremoloAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    *beatParam =  MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readInt();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GenTremoloAudioProcessor();
}
