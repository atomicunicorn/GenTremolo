/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class GenTremoloAudioProcessorEditor  : public AudioProcessorEditor, private Button::Listener //, public Timer
{
public:
    GenTremoloAudioProcessorEditor (GenTremoloAudioProcessor&);
    ~GenTremoloAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
//    void timerCallback() override;
    String getBeatLabelTextFromBeatParameterValue(const AudioParameterInt* beatParam);
    void buttonClicked (Button* button) override;

private:
//    Label* beatLabel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GenTremoloAudioProcessor& processor;
    TextButton randomButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenTremoloAudioProcessorEditor)
};
