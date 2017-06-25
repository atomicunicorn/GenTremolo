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
    isStandard = false;
    isStereo = false;
    minBeat = k64th;
    maxBeat = k2;
    blockCounter = 1;
    randSampleCounter = 0;
    euclidSampleCounter = 0;
    
    /* Initialize and add the parameters */
    
    // TODO fix automation text representations in host (may be just a problem with Ableton integration)
    parameters.createAndAddParameter("randomParamID", "Random", String(),
                                     NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f,
                                     [](float v) -> String { return v < 0.5f ? "Off" : "On";},
                                     [](const String& s) -> float { if (s == "Off"){return 0.0f;} if(s =="On"){return 1.0f;}return 0.0f;} );
    parameters.createAndAddParameter("euclidParamID", "Euclid", String(),
                                     NormalisableRange<float> (0.0f, 1.0f, 1.0f), 1.0f,
                                     [](float value)
                                     {
                                         if(value == 0.0f) return "Off";
                                         if(value == 1.0f) return "On";
                                         return "";
                                     },
                                     [](const String& text)
                                     {
                                         if(text == "Off") return 0.0f;
                                         if(text == "On") return 1.0f;
                                         return 0.0f;
                                     });
    parameters.createAndAddParameter("standardParamID", "Standard", String(),
                                     NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("stereoParamID", "Stereo", String(), NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("chaosParamID", "Chaos", String(), NormalisableRange<float> (0.0f, 1.0f), 0.5f, nullptr, nullptr);
    parameters.createAndAddParameter("mixParamID", "Mix", String(), NormalisableRange<float> (0.0f, 1.0f), 1.0f, nullptr, nullptr);
    parameters.createAndAddParameter("kickDensityParamID", "Kick Density", String(), NormalisableRange<float> (0.0f, 127.0f), 32.0f, nullptr, nullptr);
    parameters.createAndAddParameter("snareDensityParamID", "Snare Density", String(), NormalisableRange<float> (0.0f, 127.0f), 32.0f, nullptr, nullptr);
    parameters.createAndAddParameter("hhDensityParamID", "HH Density", String(), NormalisableRange<float> (0.0f, 127.0f), 32.0f, nullptr, nullptr);
    parameters.createAndAddParameter("mapXParamID", "MapX", String(), NormalisableRange<float> (0.0f, 1.0f), 0.5f, nullptr, nullptr);
    parameters.createAndAddParameter("mapYParamID", "MapY", String(), NormalisableRange<float> (0.0f, 1.0f), 0.5f, nullptr, nullptr);
    // TODO use the value to text function to set the min beat label and the euclid beat label
    parameters.createAndAddParameter("minBeatParamID", "Min beat", String(), NormalisableRange<float> (0.0f, 4.0f, 1.0f), 0.0f, nullptr, nullptr);
//    parameters.createAndAddParameter("euclidBeatParamID", "Euclid beat", String(), NormalisableRange<float> (0.0f, 4.0f, 1.0f), 0.0f, nullptr, nullptr);
    
    
    parameters.state = ValueTree (Identifier ("APVTSGenTremolo"));
    
    
    /* EuclidGrid setup */  // TODO integrate user parameters here!
    euclidGrid = new EuclidGrid();
    isEuclid = true;
    isPlayingEuclidNote = false;
    samplesLeftInCurrentEuclidNote = 0;
    euclidBeatDivisor = 8; // default to 32nd note length
    euclidNoteAmplitude = 0.0f;
    euclidStep = 0;
    gridsCallCountValid = 0; // for testing
    noteStruct = {};
    euclidLinearSmoothedValue.reset(defaultSampleRate, (double)(volumeRampLengthInMs/1000.0));
}

GenTremoloAudioProcessor::~GenTremoloAudioProcessor()
{
    // TODO make sure that we don't need to delete the EuclidGrid object explicitly.
}

String GenTremoloAudioProcessor::toggleButtonParameterValueToString(float rawValue) {
    return rawValue < 0.5f ? "Off" : "On";
}

float GenTremoloAudioProcessor::toggleButtonStringToParameterRawValue(String toggleButtonString) {
    if (toggleButtonString == "Off")
        return 0.0f;
    if (toggleButtonString == "On");
        return 1.0f;
    return 0.0f;
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
    euclidLinearSmoothedValue.reset(sampleRate, (double)(volumeRampLengthInMs/1000.0));
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

GenTremoloAudioProcessor::BeatIndicators GenTremoloAudioProcessor::getBeatIndicatorFromParam(float rawValue) {
    switch ((int)rawValue) {
        case 0:
            return k64th;
        case 1:
            return k32nd;
        case 2:
            return k16th;
        case 3:
            return k8th;
        case 4:
            return k4th;
        default:
            return k4th;
    }
}

int GenTremoloAudioProcessor::beatIndicatorToEuclidBeatDivisor(float rawValue) {
    switch ((int)rawValue) {
        case 0:
            return 32;
        case 1:
            return 16;
        case 2:
            return 8;
        case 3:
            return 4;
        case 4:
            return 2;
        default:
            return 4;
    }
}

/* returns the scale of our interval size that we pass before randomly assigning a new trem frequency*/
int GenTremoloAudioProcessor::scaleChaosParameterToInt(float rawValue) {
    const int chaosLevel = (const int)round(rawValue * 10.0f);
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
    
    /* Get sample and channel information */
    const double sampleRate = getSampleRate();
    const double sampleFrequency = 1.0 / sampleRate;
    const int numSamples = buffer.getNumSamples();
    const int totalNumInputChannels  = GenTremoloAudioProcessor::getTotalNumInputChannels();
    const int totalNumOutputChannels = GenTremoloAudioProcessor::getTotalNumOutputChannels();
    float* channelDataLeft = buffer.getWritePointer(0);
    float* channelDataRight = buffer.getWritePointer(1);
    float leftConvolvedSample;
    float rightConvolvedSample;
    
    /* Initialize internal parameters */
    int randVal = 1;  // TODO make randVal remember its state
    euclidNoteSampleLen = 22050;
    const int volumeRampSampleLength = (int)round(((double)volumeRampLengthInMs * sampleRate/1000.0));
    
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
            
            /* Get rhythmic sample information */
            const int samplesPerQuarterNote = getSamplesPerQuarterNote(bpm, sampleRate);
            int samplesPerBeatIndicator = getSamplesPerBeat(trem_beat_indicator, samplesPerQuarterNote);
            int samplesPer32ndNote = (int)roundf((((float)samplesPerQuarterNote)/8.0f));
            euclidNoteSampleLen = getEuclidNoteSampleLength(samplesPerQuarterNote);
            euclidStep = (int)round((double)result.timeInSamples / (double)euclidNoteSampleLen);
            
            /***** iterate through and process samples in block *****/
            for (int i = 0; i < numSamples; i++) {
                /* Read user-controlled parameters */
                const float rawChaosParamValue = *parameters.getRawParameterValue("chaosParamID");
                const float rawBeatParamValue = *parameters.getRawParameterValue("minBeatParamID");
                euclidGrid->setMapX((int)roundf(*parameters.getRawParameterValue("mapXParamID")*126.0f));
                euclidGrid->setMapY((int)roundf(*parameters.getRawParameterValue("mapYParamID")*126.0f));
                euclidGrid->setRandomness((int)roundf(rawChaosParamValue * 126.0f));
                euclidGrid->setDensity((int)roundf(*parameters.getRawParameterValue("kickDensityParamID")*126.0f), kickIndex);
                euclidGrid->setDensity((int)roundf(*parameters.getRawParameterValue("snareDensityParamID")*126.0f), snareIndex);
                euclidGrid->setDensity((int)roundf(*parameters.getRawParameterValue("hhDensityParamID")*126.0f), hhIndex);
                minBeat = getBeatIndicatorFromParam(rawBeatParamValue);
                euclidBeatDivisor = beatIndicatorToEuclidBeatDivisor(rawBeatParamValue);
                const int chaosIntervalSize = scaleChaosParameterToInt(rawChaosParamValue);
                
                isRandom = *parameters.getRawParameterValue("randomParamID") < 0.5f ? false : true;
                isStandard = *parameters.getRawParameterValue("standardParamID") < 0.5f ? false : true;
                isEuclid = *parameters.getRawParameterValue("euclidParamID") < 0.5f ? false : true;
                isStereo = *parameters.getRawParameterValue("stereoParamID") < 0.5f ? false : true;
                const float rawMixParamValue = *parameters.getRawParameterValue("mixParamID");
                
                const float inLeft = channelDataLeft[i];
                const float inRight = channelDataRight[i];
                float preMixLeftAmplitude;
                float preMixRightAmplitude;
                
                /*** Random Tremolo Preparation ***/
                if (isRandom && (randSampleCounter % samplesPerBeatIndicator*chaosIntervalSize) == 0) {
                    trem_frequency = next_trem_frequency;
                    randVal = rand() + 1;
                    trem_beat_indicator = BeatIndicators(randVal % 5);
                    next_trem_frequency = getUpdatedTremFrequency(bpm);       //XXX create temporary variables for these?
                    randSampleCounter = 0;
                }
                
                /*** Euclidean Tremolo Logic ***/
                if (isEuclid) {
                    /* call runGrid on every euclid step (32nd note) regardless of whether a note is playing or not, */
                    if (onEuclidStep(samplesPer32ndNote)) {
                        updateEuclidGrid();
                    }
                    /* Keep track of progress on current euclid note and update if it is finished playing. */
                    updateEuclidAmplitudeAndNoteLength(volumeRampSampleLength, samplesPer32ndNote);
                    preMixLeftAmplitude = leftEuclidNoteAmplitude;
                    preMixRightAmplitude = rightEuclidNoteAmplitude;
                }
                
                /*** Non Euclidean Tremolo ***/
                if (!isEuclid) { // non euclidean logic
                    preMixLeftAmplitude = (1.0f - trem_depth*lfo(temp_trem_lfo_phase_copy, trem_waveform_indicator));
                    preMixRightAmplitude = (1.0f - trem_depth*lfo(temp_trem_lfo_phase_copy, trem_waveform_indicator));
                }
                leftConvolvedSample = inLeft * preMixLeftAmplitude;
                rightConvolvedSample = inRight * preMixRightAmplitude;
                channelDataLeft[i] = inLeft * (1.0f - rawMixParamValue) + leftConvolvedSample * rawMixParamValue;
                channelDataRight[i] = inRight * (1.0f - rawMixParamValue) + rightConvolvedSample * rawMixParamValue;
                
                /* Update the carrier and LFO phases, keeping them in the range 0-1 */
                temp_trem_lfo_phase_copy += trem_frequency*sampleFrequency;
                if(temp_trem_lfo_phase_copy >= 1.0)
                    temp_trem_lfo_phase_copy -= 1.0;
                
                /* Increment sample counters and handle other sample bookkeeping*/
                randSampleCounter++;
                euclidSampleCounter++;
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

void GenTremoloAudioProcessor::updateEuclidGrid() {
    noteStruct = {}; // reset structs before calling run grid
    stereoNoteStruct = {};
    euclidGrid->runGrid(euclidStep, euclidNoteSampleLen, isStereo, noteStruct, stereoNoteStruct);
    
    if (!isStereo) { // process mono
        if (noteStruct.success && noteStruct.noteOn)
            gridsCallCountValid++;
        /* check that no euclid note is currently playing and grid did not fail */
        if (!isPlayingEuclidNote) {
            /* check if grid generated a new valid note */
            if (noteStruct.success && noteStruct.noteOn && noteStruct.lengthInSamples > 0) {
                isPlayingEuclidNote = true;
                samplesLeftInCurrentEuclidNote = noteStruct.lengthInSamples;
                euclidNoteAmplitude = 1.0f;  // TODO get amplitude values generated by EuclidGrid object
                euclidLinearSmoothedValue.setValue(euclidNoteAmplitude);
            } else {
                isPlayingEuclidNote = false;
                samplesLeftInCurrentEuclidNote = 0;
                euclidNoteAmplitude = 0.0f;
            }
        }
        leftEuclidNoteAmplitude = euclidNoteAmplitude;
        rightEuclidNoteAmplitude = euclidNoteAmplitude;
    } else {  // process stereo
        if (stereoNoteStruct.success && (stereoNoteStruct.rightNoteOn || stereoNoteStruct.leftNoteOn)) {
            gridsCallCountValid++;
            updateEuclidLeft();
            updateEuclidRight();
        }
    }

}

void GenTremoloAudioProcessor::updateEuclidLeft() {
    if (!leftIsPlayingEuclidNote) {
        if (stereoNoteStruct.leftNoteOn && stereoNoteStruct.leftLengthInSamples > 0) {
            leftIsPlayingEuclidNote = true;
            leftSamplesLeftInCurrentEuclidNote = stereoNoteStruct.leftLengthInSamples;
            leftEuclidNoteAmplitude = 1.0f;
            leftEuclidLinearSmoothedValue.setValue(leftEuclidNoteAmplitude);
        } else {
            leftIsPlayingEuclidNote = false;
            leftSamplesLeftInCurrentEuclidNote = 0;
            leftEuclidNoteAmplitude = 0.0f;
        }
    }
}

void GenTremoloAudioProcessor::updateEuclidRight() {
    if (!rightIsPlayingEuclidNote) {
        if (stereoNoteStruct.rightNoteOn && stereoNoteStruct.rightLengthInSamples > 0) {
            rightIsPlayingEuclidNote = true;
            rightSamplesLeftInCurrentEuclidNote = stereoNoteStruct.rightLengthInSamples;
            rightEuclidNoteAmplitude = 1.0f;
            rightEuclidLinearSmoothedValue.setValue(rightEuclidNoteAmplitude);
        } else {
            rightIsPlayingEuclidNote = false;
            rightSamplesLeftInCurrentEuclidNote = 0;
            rightEuclidNoteAmplitude = 0.0f;
        }
    }
}

void GenTremoloAudioProcessor::updateEuclidAmplitudeAndNoteLength(int volumeRampSampleLength, int samplesPer32ndNote) {
    if (!isStereo) { /* MONO */
        if (samplesLeftInCurrentEuclidNote > 0) {
            samplesLeftInCurrentEuclidNote--;
            if (samplesLeftInCurrentEuclidNote == volumeRampSampleLength + 1)
                euclidLinearSmoothedValue.setValue(0.0f);
        } else {
            isPlayingEuclidNote = false;
            euclidNoteAmplitude = 0.0f;
        }
        if (euclidLinearSmoothedValue.isSmoothing())
            euclidNoteAmplitude = euclidLinearSmoothedValue.getNextValue();
        leftEuclidNoteAmplitude = euclidNoteAmplitude;
        rightEuclidNoteAmplitude = euclidNoteAmplitude;
    } else { /* STEREO */
        // process left
        if (leftSamplesLeftInCurrentEuclidNote > 0) {
            leftSamplesLeftInCurrentEuclidNote--;
            if (leftSamplesLeftInCurrentEuclidNote == volumeRampSampleLength + 1)
                leftEuclidLinearSmoothedValue.setValue(0.0f);
        } else {
            leftIsPlayingEuclidNote = false;
            leftEuclidNoteAmplitude = 0.0f;
        }
        if (leftEuclidLinearSmoothedValue.isSmoothing())
            leftEuclidNoteAmplitude = leftEuclidLinearSmoothedValue.getNextValue();
        // process right
        if (rightSamplesLeftInCurrentEuclidNote > 0) {
            rightSamplesLeftInCurrentEuclidNote--;
            if (rightSamplesLeftInCurrentEuclidNote == volumeRampSampleLength + 1)
                rightEuclidLinearSmoothedValue.setValue(0.0f);
        } else {
            rightIsPlayingEuclidNote = false;
            rightEuclidNoteAmplitude = 0.0f;
        }
        if (rightEuclidLinearSmoothedValue.isSmoothing())
            rightEuclidNoteAmplitude = rightEuclidLinearSmoothedValue.getNextValue();
    }
}



bool GenTremoloAudioProcessor::onEuclidStep(int samplesPerEuclidPatternStep) {
    if ((euclidSampleCounter % samplesPerEuclidPatternStep) == 0) {
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
