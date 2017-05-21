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
class GenTremoloAudioProcessorEditor  : public AudioProcessorEditor, private ComboBox::Listener
//, private Timer
{
public:
    GenTremoloAudioProcessorEditor (GenTremoloAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~GenTremoloAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox* comboBox) override;
    

private:
    AudioProcessorValueTreeState& valueTreeState;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> chaosAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> randomAttachment;

    /* Components */
    ToggleButton randomToggleButton;
    Label chaosLabel;
    Slider chaosSlider;
//    Label* beatLabel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GenTremoloAudioProcessor& processor;
    ComboBox waveformComboBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenTremoloAudioProcessorEditor)
};
