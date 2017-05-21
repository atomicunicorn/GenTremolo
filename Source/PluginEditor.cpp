/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
GenTremoloAudioProcessorEditor::GenTremoloAudioProcessorEditor (GenTremoloAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 400);
    
    /* Automation params added here */
    randomToggleButton.setButtonText ("Random");
    addAndMakeVisible (&randomToggleButton);
    randomAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "randomParamID", randomToggleButton);
    
    /* non audioparameter buttons */
//    addAndMakeVisible (&randomButton);
//    randomButton.setButtonText ("Randomize off");
//    randomButton.addListener(this);
//    
//    /* non audioparameter combo boxes */
    waveformComboBox.addItem("sine", 1);
    waveformComboBox.addItem("sloped-square", 2);
    waveformComboBox.addItem("triangle", 3);
    waveformComboBox.addItem("square", 4);
    waveformComboBox.addSeparator();
    waveformComboBox.setText("sloped-square");
    addAndMakeVisible(&waveformComboBox);
    waveformComboBox.addListener(this);
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
    g.drawFittedText ("Gen Tremolo d", getLocalBounds(), Justification::centred, 1);
}

//void GenTremoloAudioProcessorEditor::buttonClicked (Button* button) {
//    if (AudioParameterBool* param = getParameterForButton (button)) {
//        param->beginChangeGesture();
//        *param = button->getToggleState();
//        param->endChangeGesture();
//    }
//    if (button == &randomButton) {
//        processor.isRandom = !processor.isRandom;
//        if (processor.isRandom)
//            randomButton.setButtonText("Randomize on");
//        if (!processor.isRandom)
//            randomButton.setButtonText("Randomize off");
//    }
//}

// TODO get this to work
void GenTremoloAudioProcessorEditor::comboBoxChanged(ComboBox* comboBox) {
    if (comboBox == &waveformComboBox) {
        switch (comboBox->getSelectedId()) {
            case 1:
                processor.trem_waveform_indicator = GenTremoloAudioProcessor::kWaveformSine;
                break;
            case 2:
                processor.trem_waveform_indicator = GenTremoloAudioProcessor::kWaveformSquareSlopedEdges;
                break;
            case 3:
                processor.trem_waveform_indicator = GenTremoloAudioProcessor::kWaveformTriangle;
                break;
            case 4:
                processor.trem_waveform_indicator = GenTremoloAudioProcessor::kWaveformSquare;
                break;
            default:
                processor.trem_waveform_indicator = GenTremoloAudioProcessor::kWaveformSine;
                break;
        }
    }
}

void GenTremoloAudioProcessorEditor::resized() {
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
//    randomButton.setBounds (40, 30, getWidth() - 100, getHeight()/4);
    // TODO add the waveform combo box to this.
    waveformComboBox.setBounds(getWidth()/2, 100 + getHeight()/4, getWidth()/3, getHeight()/5);
    randomToggleButton.setBounds(40, 30, getWidth() - 100, getHeight()/4);
    
    /* TODO make the resizing more intelligent and automatic... something like this example below from https://www.juce.com/doc/tutorial_audio_parameter */
}
