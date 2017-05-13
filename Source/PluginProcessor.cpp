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
    trem_frequency = 2.0;
    trem_depth = 1.0;
    trem_waveform_indicator = kWaveformSine;
    trem_lfo_phase = 0.0;
    sample_frequency = 1.0/44100.0;
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

float GenTremoloAudioProcessor::getNewTremFrequencyFromBpmGrid() {
    
}

void GenTremoloAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = GenTremoloAudioProcessor::getTotalNumInputChannels();
    const int totalNumOutputChannels = GenTremoloAudioProcessor::getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();
    
    // 1) SINE WAVE CARRIER:
    // v(t) = (Ec + em) * sin(2*PI*Freq*t) ==> [ Ec + Em * sin(2*PI*Freq*t) ] sin(2*PI*Freq*t)
    // Ec = carrier wave
    // em = Em*sin(2*PI*Freq*t) instantaneous amplitude of the modulating signal
    // panL = panR = 1;
    
    int channel;
    float temp_trem_lfo_phase_copy;
    for (channel = 0; channel < totalNumInputChannels; channel++) {
        float* channelData = buffer.getWritePointer(channel);
        temp_trem_lfo_phase_copy = trem_lfo_phase;
        for (int i = 0; i < numSamples; i++) {
            const float in = channelData[i];
            // multiply the waveform by the periodic carrier signal
            channelData[i] = in * (1.0f - trem_depth*lfo(temp_trem_lfo_phase_copy, trem_waveform_indicator));
            // Update the carrier and LFO phases, keeping them in the range 0-1
            temp_trem_lfo_phase_copy += trem_frequency*sample_frequency;
            if(temp_trem_lfo_phase_copy >= 1.0)
                temp_trem_lfo_phase_copy -= 1.0;
        }
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
}

void GenTremoloAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GenTremoloAudioProcessor();
}
