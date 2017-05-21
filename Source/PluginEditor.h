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
class GenTremoloAudioProcessorEditor  : public AudioProcessorEditor, private ComboBox::Listener //,
//private Button::Listener, private Timer
{
public:
    GenTremoloAudioProcessorEditor (GenTremoloAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~GenTremoloAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
//    void buttonClicked (Button* button) override;
    void comboBoxChanged(ComboBox* comboBox) override;
    AudioParameterBool* getParameterForButton (Button* button);
    

private:
    AudioProcessorValueTreeState& valueTreeState;
    ToggleButton randomToggleButton;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> randomAttachment;
    
//    void timerCallback() override {
//        const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();
//        for (int i = 0; i < controls.size(); ++i) {
//            if (Slider* slider = dynamic_cast<Slider*> (controls[i])) {
//                AudioParameterFloat* param = static_cast<AudioParameterFloat*> (params[i]);
//                slider->setValue ((double) *param, dontSendNotification);
//            }
//            else if (Button* button = dynamic_cast<Button*> (controls[i])) {
//                AudioParameterBool* param = static_cast<AudioParameterBool*> (params[i]);
//                button->setToggleState (*param, dontSendNotification);
//            }
//        }
//    }

//    Label* beatLabel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GenTremoloAudioProcessor& processor;
    ComboBox waveformComboBox;
//    const String* waveFormStrings = {"sine", "sloped-square", "square", "triangle"};
//    const StringArray* waveformStringList = new StringArray(waveFormStrings, 4);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenTremoloAudioProcessorEditor)
};
