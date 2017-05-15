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
class GenTremoloAudioProcessorEditor  : public AudioProcessorEditor,
private Button::Listener, private ComboBox::Listener //, public Timer
{
public:
    GenTremoloAudioProcessorEditor (GenTremoloAudioProcessor&);
    ~GenTremoloAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
//    void timerCallback() override;
    void buttonClicked (Button* button) override;
    void comboBoxChanged(ComboBox* comboBox) override;

private:
//    Label* beatLabel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GenTremoloAudioProcessor& processor;
    TextButton randomButton;
    ComboBox waveformComboBox;
//    const String* waveFormStrings = {"sine", "sloped-square", "square", "triangle"};
//    const StringArray* waveformStringList = new StringArray(waveFormStrings, 4);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenTremoloAudioProcessorEditor)
};
