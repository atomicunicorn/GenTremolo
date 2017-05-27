/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "EuclidGrid.h"


//==============================================================================
/**
*/
class GenTremoloAudioProcessorEditor  : public AudioProcessorEditor, private ComboBox::Listener, private Slider::Listener, private HighResolutionTimer
//, private Timer
{
public:
    GenTremoloAudioProcessorEditor (GenTremoloAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~GenTremoloAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox* comboBox) override;
    void sliderValueChanged(Slider* slider) override;
    
    void hiResTimerCallback() override;
    
    /* public attributes */
    const int numMinBeatTabs = 5;
    Colour tabColorRGBA = Colours::aqua;

private:
    
    /* Methods */
    
    
    /* Parameter-related objects */
    AudioProcessorValueTreeState& valueTreeState;
    const int modeRadioGroupID = 1;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> randomAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> euclidAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> standardAttachment;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> chaosAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mapXAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mapYAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> minBeatAttachment;

    /* Components */
    ToggleButton randomToggleButton;  // TODO enable radio toggle buttons (see button.h) between normal, random, and euclid modes
    ToggleButton euclidToggleButton;
    ToggleButton standardToggleButton;
    
    Label chaosLabel;
    Slider chaosSlider;
    
    Label mapXLabel;
    Slider mapXSlider;
    Label mapYLabel;
    Slider mapYSlider;
    
    Label minBeatLabel;
    Slider minBeatSlider;
    
    Label euclidIsPlayingLabel;
    
//    Label minBeatLabel;
//    TabbedButtonBar minBeatTabButtonBar;
    
    ComboBox waveformComboBox;
    
    /* Misc attributes */

    /* This reference is provided as a quick way for your editor to
     * access the processor object that created it. */
    GenTremoloAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenTremoloAudioProcessorEditor)
};
