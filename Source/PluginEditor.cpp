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
    : AudioProcessorEditor (&p), valueTreeState(vts),  processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 400);
    
    /* Automation params added here */
    randomToggleButton.setButtonText ("Random");
    addAndMakeVisible (&randomToggleButton);
    randomAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "randomParamID", randomToggleButton);
    chaosLabel.setText("Chaos Amount", dontSendNotification);
    addAndMakeVisible(&chaosLabel);
    chaosSlider.setSliderStyle (Slider::LinearBarVertical);
    chaosSlider.setRange(0.0, 10.0, 1.0);
    chaosSlider.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    chaosSlider.setPopupDisplayEnabled (true, this);
    addAndMakeVisible(&chaosSlider);
    chaosAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "chaosParamID", chaosSlider);

    /* non audioparameter combo boxes */
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
    g.drawFittedText ("Gen Tremolo d", getLocalBounds(), Justification::centredTop, 1);
}

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
    /* This is generally where you'll want to lay out the positions of any
     * subcomponents in your editor.. */
    
    waveformComboBox.setBounds(getWidth()/2, 100 + getHeight()/4, getWidth()/3, getHeight()/5);
    randomToggleButton.setBounds(getWidth() - 180, 30, getWidth()/4, getHeight()/6);
    chaosSlider.setBounds(40, 30, 20, getHeight() - 120);
    Rectangle<int> chaosSliderBounds = chaosSlider.getBounds();
    chaosLabel.setBounds(chaosSliderBounds.getX(), chaosSliderBounds.getBottom() + 20, 100, 90);
    /* TODO make the resizing more intelligent and automatic... something like this example below from https://www.juce.com/doc/tutorial_audio_parameter */
}
