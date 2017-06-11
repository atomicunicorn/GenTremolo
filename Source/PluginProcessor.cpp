/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "EuclidGrid.h"


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
                       ),
#endif
parameters(*this, nullptr) // TODO point to and set up an undomanager
{
    /* Set default values: */
    trem_beat_indicator = k4th;
    trem_frequency = 2.0;
    trem_depth = 1.0;
    trem_waveform_indicator = kWaveformSquareSlopedEdges; //kWaveformSine;
    trem_lfo_phase = 0.0;
    isRandom = false;
    isStandard = true;
    minBeat = k64th;
    maxBeat = k2;
    blockCounter = 1;
    sampleCounter = 0;
    
    /* Initialize and add the parameters */
    
    // TODO use the value to text function to set the label to either on or off for automation
    parameters.createAndAddParameter("randomParamID", "Random", String(),
                                     NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("euclidParamID", "Euclid", String(),
                                     NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("standardParamID", "Standard", String(),
                                     NormalisableRange<float> (0.0f, 1.0f, 1.0f), 1.0f, nullptr, nullptr);
    
    parameters.createAndAddParameter("chaosParamID", "Chaos", String(), NormalisableRange<float> (0.0f, 1.0f), 0.5f, nullptr, nullptr);
    parameters.createAndAddParameter("mapXParamID", "MapX", String(), NormalisableRange<float> (0.0f, 1.0f), 0.5f, nullptr, nullptr);
    parameters.createAndAddParameter("mapYParamID", "MapY", String(), NormalisableRange<float> (0.0f, 1.0f), 0.5f, nullptr, nullptr);
    // TODO use the value to text function to set the min beat label
    parameters.createAndAddParameter("minBeatParamID", "Min beat", String(), NormalisableRange<float> (0.0f, 4.0f, 1.0f), 0.0f, nullptr, nullptr);
    
    
    parameters.state = ValueTree (Identifier ("APVTSGenTremolo"));
    
    
    /* EuclidGrid setup */  // TODO integrate user parameters here!
    euclidGrid = new EuclidGrid();
    isEuclid = false;
    isPlayingEuclidNote = false;
    samplesLeftInCurrentEuclidNote = 0;
    euclidBeatDivisor = 16; // default to 32nd note length
    euclidNoteAmplitude = 0.0f;
    euclidStep = 0;
    gridsCallCountValid = 0; // for testing
    noteStruct = {};
//    euclidLinearSmoothedValue.reset(defaultSampleRate, ((double)volumeRampLengthInMs)/1000.0);
}

GenTremoloAudioProcessor::~GenTremoloAudioProcessor()
{
    // TODO make sure that we don't need to delete the EuclidGrid object explicitly.
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
    
    // TODO move lots of initialization here
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

int GenTremoloAudioProcessor::getSamplesPerQuarterNote(double bpm, const double sampleRate) {
    if (bpm <= 0) {
        return (int)round(60.0*sampleRate/120.0);
    }
    return (int)round(60.0*sampleRate/bpm);
}

int GenTremoloAudioProcessor::getSamplesPerBeat(int beatIndicator, int samplesPerQuarterNote) {
    switch (beatIndicator) {
        case k4th:
            return samplesPerQuarterNote;
        case k8th:
            return samplesPerQuarterNote/2;
        case k16th:
            return samplesPerQuarterNote/4;
        case k32nd:
            return samplesPerQuarterNote/8;
        case k64th:
            return samplesPerQuarterNote/16;
        default:
            return samplesPerQuarterNote;
    }
}

/* returns the scale of our interval size that we pass before randomly assigning a new trem frequency*/
int GenTremoloAudioProcessor::scaleChaosParameterToInt() {
    const int chaosLevel = (const int)round(*parameters.getRawParameterValue("chaosParamID") * 10.0f);
    if (chaosLevel == 10) {
        return 1;
    }
    if (chaosLevel == 0) {
        return 10;
    }
    return 10 - chaosLevel;
}

int GenTremoloAudioProcessor::getEuclidNoteSampleLength(int samplesPerQuarterNote) {
    if (euclidBeatDivisor <= 0)
        return samplesPerQuarterNote;
    float multipleOfQuarterNote = 4.0f/((float)euclidBeatDivisor);
    return (int)round(multipleOfQuarterNote*((float)samplesPerQuarterNote));
}

void GenTremoloAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    /* Read user-controlled parameters */
    isRandom = *parameters.getRawParameterValue("randomParamID") < 0.5f ? false : true;
    isStandard = *parameters.getRawParameterValue("standardParamID") < 0.5f ? false : true;
    isEuclid = *parameters.getRawParameterValue("euclidParamID") < 0.5f ? false : true;
    euclidGrid->setMapX((const int)round(*parameters.getRawParameterValue("mapXParamID")*126.0f));
    euclidGrid->setMapY((const int)round(*parameters.getRawParameterValue("mapYParamID")*126.0f));
    euclidGrid->setRandomness((const int)round(*parameters.getRawParameterValue("chaosParamID")*126.0f));
    
    /* Get sample and channel information */
    const double sampleRate = getSampleRate(); //GenTremoloAudioProcessor::getSampleRate();
    const double sampleFrequency = 1.0 / sampleRate;
    const int numSamples = buffer.getNumSamples();
    const int totalNumInputChannels  = GenTremoloAudioProcessor::getTotalNumInputChannels();
    const int totalNumOutputChannels = GenTremoloAudioProcessor::getTotalNumOutputChannels();
    float* channelDataLeft = buffer.getWritePointer(0);
    float* channelDataRight = buffer.getWritePointer(1);
    
    /* Initialize internal parameters */
    int randVal = 1;  // TODO make randVal remember its state
    const int chaosIntervalSize = scaleChaosParameterToInt();
    int euclidNoteSampleLength = 22050;
    euclidNoteSampleLen = 22050;
    
    /* Make a temporary copy of any state variables declared in PluginProcessor.h which need to be
     * maintained between calls to processBlock(). Each channel needs to be processed identically
     * which means that the activity of processing one channel can't affect the state variable for
     * the next channel.                                                                           */
    float temp_trem_lfo_phase_copy;
    temp_trem_lfo_phase_copy = trem_lfo_phase;
        
    /* Get playhead information - if successful, begin processing samples */
    AudioPlayHead* const playHead = getPlayHead();
    AudioPlayHead::CurrentPositionInfo result = {};
    if (playHead != nullptr) {
        if (GenTremoloAudioProcessor::getPlayHead()->getCurrentPosition(result) && result.isPlaying) {
            const double bpm = result.bpm;
            const double ppqCount = result.ppqPosition;
            
            /* TODO need smarter way to sync the euclidStep to the grid since this relies on sampleCounter which can have arbitrary start values. the result.timeInSamples validity may be questionable at the moment. */
//            prevEuclidStep = (int)(8*floor(ppqCount));
//            euclidStep = prevEuclidStep;
//            const int globalSamplesPassedSinceBlock = (int)result.timeInSamples;
            
            /* Get rhythmic sample information */
            const int samplesPerQuarterNote = getSamplesPerQuarterNote(bpm, sampleRate);
            int samplesPerBeatIndicator = getSamplesPerBeat(trem_beat_indicator, samplesPerQuarterNote);
            int samplesPer32ndNote = (int)roundf((((float)samplesPerQuarterNote)/8.0f));
            euclidNoteSampleLen = getEuclidNoteSampleLength(samplesPerQuarterNote);
            euclidStep = (int)round((double)result.timeInSamples / (double)euclidNoteSampleLen);
            
            /* Get euclid information if in euclidean mode .... TODO is this if needed?? */
            if (isEuclid) {
                gridSampLen = euclidNoteSampleLength;
            }
            /* Get random information if in random mode */
            if (isRandom) {
                
            }
            
            /***** iterate through and process samples in block *****/
            for (int i = 0; i < numSamples; i++) {
                
                const float inLeft = channelDataLeft[i];
                const float inRight = channelDataRight[i];
                
                /*** Random Tremolo Preparation ***/
                if (isRandom && (sampleCounter % samplesPerBeatIndicator*chaosIntervalSize) == 0) {
                    trem_frequency = next_trem_frequency;
                    randVal = rand() + 1;
                    trem_beat_indicator = BeatIndicators(randVal % 5);
                    next_trem_frequency = getUpdatedTremFrequency(bpm);       //XXX create temporary variables for these
                    sampleCounter = 0;
                }
                
                /*** Euclidean Tremolo Logic ***/
                if (isEuclid) {
                    /* call runGrid on every euclid step (32nd note) regardless of whether a note is playing or not, */
                    if (onEuclidStep(samplesPer32ndNote)) {
                        updateEuclid();
                    }
                    /* Keep track of progress on current euclid note and update if it is finished playing. */
                    if (samplesLeftInCurrentEuclidNote > 0) {
                        samplesLeftInCurrentEuclidNote--;
                    } else {
                        isPlayingEuclidNote = false;
                        euclidNoteAmplitude = 0.0f;
                    }
                    channelDataLeft[i] = inLeft * euclidNoteAmplitude;
                    channelDataRight[i] = inRight * euclidNoteAmplitude;
                }
                
                /*** Non Euclidean Tremolo ***/
                if (!isEuclid) { // non euclidean logic
                    channelDataLeft[i] = inLeft * (1.0f - trem_depth*lfo(temp_trem_lfo_phase_copy, trem_waveform_indicator));
                    channelDataRight[i] = inRight * (1.0f - trem_depth*lfo(temp_trem_lfo_phase_copy, trem_waveform_indicator));
                }
                
                /* Update the carrier and LFO phases, keeping them in the range 0-1 */
                temp_trem_lfo_phase_copy += trem_frequency*sampleFrequency;
                if(temp_trem_lfo_phase_copy >= 1.0)
                    temp_trem_lfo_phase_copy -= 1.0;
                
                /* Increment sample counters and handle other sample bookkeeping*/
                sampleCounter++;
            }
            /*** done iterating through and processing samples in block ***/
            
            /* Having made a local copy of the state variables for each channel, now transfer the result
             * back to the main state variable so they will be preserved for the next call of processBlock() */
            trem_lfo_phase = temp_trem_lfo_phase_copy;
            
            /* In case we have more outputs than inputs, we'll clear any output
             * channels that didn't contain input data, (because these aren't
             * guaranteed to be empty - they may contain garbage). */
            for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            {
                buffer.clear (i, 0, buffer.getNumSamples());
            }
            
        }
    }
}

void GenTremoloAudioProcessor::updateEuclid() {
    noteStruct = {}; // reset struct before call
    euclidGrid->runGrid(euclidStep, euclidNoteSampleLen, noteStruct);
    if (noteStruct.success && noteStruct.noteOn)
        gridsCallCountValid++;
    
    /* check that no euclid note is currently playing and grid did not fail */
    if (!isPlayingEuclidNote) {
        /* check if grid generated a new valid note */
        if (noteStruct.success && noteStruct.noteOn && noteStruct.lengthInSamples > 0) {
            isPlayingEuclidNote = true;
            samplesLeftInCurrentEuclidNote = noteStruct.lengthInSamples;
            euclidNoteAmplitude = 1.0f;   // TODO add volume ramp to this
        } else {
            isPlayingEuclidNote = false;
            samplesLeftInCurrentEuclidNote = 0;
            euclidNoteAmplitude = 0.0f;
        }
    }
}

bool GenTremoloAudioProcessor::onEuclidStep(int samplesPerEuclidPatternStep) {
    if ((sampleCounter % samplesPerEuclidPatternStep) == 0) {
//        prevEuclidStep = euclidStep;
        euclidStep++;
        return true;
    } else {
        return false;
    }
}

float GenTremoloAudioProcessor::getUpdatedTremFrequency(double bpm) {
    switch (trem_beat_indicator) {
        case k2:
            return bpm / 120.0;
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
    return true;
}

AudioProcessorEditor* GenTremoloAudioProcessor::createEditor()
{
    return new GenTremoloAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void GenTremoloAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    /* You should use this method to store your parameters in the memory block.
     * You could do that either as raw data, or use the XML or ValueTree classes
     * as intermediaries to make it easy to save and load complex data. */
    
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

void GenTremoloAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* You should use this method to restore your parameters from this memory block,
     * whose contents will have been created by the getStateInformation() call. */
    
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr) {
        if (xmlState->hasTagName (parameters.state.getType())) {
            parameters.state = ValueTree::fromXml (*xmlState);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GenTremoloAudioProcessor();
}
