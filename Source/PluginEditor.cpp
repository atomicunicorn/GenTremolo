/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
GenTremoloAudioProcessorEditor::GenTremoloAudioProcessorEditor (GenTremoloAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 400);
    
    /* buttons */
    addAndMakeVisible (&randomButton);
    randomButton.setButtonText ("Randomize off");
    randomButton.addListener(this);
    
    /* combo boxes */
//    waveformComboBox.addItemList(waveformStringList, 0)
    waveformComboBox.addItem("sine", 1);
    waveformComboBox.addItem("sloped-square", 2);
    waveformComboBox.addItem("triangle", 3);
    waveformComboBox.addItem("square", 4);
    waveformComboBox.addSeparator();
    waveformComboBox.setText("sloped-square");
    addAndMakeVisible(&waveformComboBox);
    // TODO finish initializing the waveform combobox
}

GenTremoloAudioProcessorEditor::~GenTremoloAudioProcessorEditor()
{
}

//==============================================================================
void GenTremoloAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Gen Tremolo c", getLocalBounds(), Justification::centred, 1);
}

//void GenTremoloAudioProcessorEditor::timerCallback() {
//    const OwnedArray<AudioProcessorParameter> &params = processor.getParameters();
//    for (int i = 0; i < params.size(); ++i)
//    {
//        if (const AudioParameterInt* param = dynamic_cast<AudioParameterInt*> (params[i])) {
//            const String paramString = param->name;
//            if (paramString.compare("Beat") == 0) {
//                beatLabel->setText(getBeatLabelTextFromBeatParameterValue(param), dontSendNotification);
//            }
//        }
//    }
//}

String GenTremoloAudioProcessorEditor::getBeatLabelTextFromBeatParameterValue(const AudioParameterInt* beatParam) {
    switch(beatParam->get()) {
        case 1:
            return "1/4th";
        case 2:
            return "1/8th";
        case 3:
            return "1/16th";
        case 4:
            return "1/32nd";
        case 5:
            return "1/64th";
        default:
            return "1/4th";
    }
    return "n/a";
}

void GenTremoloAudioProcessorEditor::buttonClicked (Button* button) {
    if (button == &randomButton) {
        processor.isRandom = !processor.isRandom;
        if (processor.isRandom)
            randomButton.setButtonText("Randomize on");
        if (!processor.isRandom)
            randomButton.setButtonText("Randomize off");
    }
}

// TODO get this to work
void GenTremoloAudioProcessorEditor::comboBoxChanged(ComboBox* comboBox) {
    if (comboBox == &waveformComboBox) {
        switch (comboBox->getSelectedId()) {
            case 1:
                processor.trem_waveform_indicator = 1;
                break;
            case 2:
                processor.trem_waveform_indicator = 2;
                break;
            case 3:
                processor.trem_waveform_indicator = 3;
                break;
            case 4:
                processor.trem_waveform_indicator = 4;
                break;
            default:
                processor.trem_waveform_indicator = 1;
                break;
        }
    }
}

void GenTremoloAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    randomButton.setBounds (40, 30, getWidth() - 100, getHeight()/4);
    // TODO add the waveform combo box to this.
    waveformComboBox.setBounds(100, 40 + getHeight()/5, getWidth()/4, getHeight()/5);
}
