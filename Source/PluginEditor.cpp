/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "EuclidGrid.h"


//==============================================================================
GenTremoloAudioProcessorEditor::GenTremoloAudioProcessorEditor (GenTremoloAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState(vts), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 400);
    
    /* ------ Automation params and components added here ------ */
    randomToggleButton.setButtonText ("Random");
    addAndMakeVisible (&randomToggleButton);
    randomAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "randomParamID", randomToggleButton);
    
    
    // TODO look at docs for NormalisableRange.snapToLegalValue. might work for discrete chaos value fix...
    chaosSlider.setSliderStyle (Slider::LinearVertical);
    chaosSlider.setRange(0.0, 10.0, 1.0);
    chaosSlider.setChangeNotificationOnlyOnRelease(true);
    chaosSlider.setPopupDisplayEnabled (false, this);
    chaosSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 65, 20);
    addAndMakeVisible(&chaosSlider);
    chaosLabel.setText("Chaos Amount", dontSendNotification);
    chaosLabel.attachToComponent(&chaosSlider, true);
    addAndMakeVisible(&chaosLabel);
    chaosAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "chaosParamID", chaosSlider);
    
    minBeatSlider.setSliderStyle(Slider::IncDecButtons);
    minBeatSlider.setRange(0, 4, 1);
    minBeatSlider.setValue(0);
    minBeatSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&minBeatSlider);
    minBeatSlider.addListener(this);
    minBeatLabel.setText("Min beat: 1/4", dontSendNotification);
    minBeatLabel.attachToComponent(&minBeatSlider, false);
    addAndMakeVisible(&minBeatLabel);
    minBeatAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "minBeatParamID", minBeatSlider);
    
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
    delete randomAttachment;
    delete chaosAttachment;
    delete minBeatAttachment;
}

//==============================================================================
void GenTremoloAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Gen Tremolo e", getLocalBounds(), Justification::centredTop, 1);
}

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

void GenTremoloAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &minBeatSlider) {
        switch ((int)slider->getValue()) {
            case 0:
                minBeatLabel.setText("min beat: 1/64th", dontSendNotification);
                break;
            case 1:
                minBeatLabel.setText("min beat: 1/32nd", dontSendNotification);
                break;
            case 2:
                minBeatLabel.setText("min beat: 1/16th", dontSendNotification);
                break;
            case 3:
                minBeatLabel.setText("min beat: 1/8th", dontSendNotification);
                break;
            case 4:
                minBeatLabel.setText("min beat: 1/4th", dontSendNotification);
                break;
            default:
                minBeatLabel.setText("min beat: n/a", dontSendNotification);
                break;
        }
    }
}

void GenTremoloAudioProcessorEditor::resized() {
    /* This is generally where you'll want to lay out the positions of any
     * subcomponents in your editor.. */
    
    waveformComboBox.setBounds(getWidth()/2, 100 + getHeight()/4, getWidth()/3, getHeight()/5);
    randomToggleButton.setBounds(getWidth()/2, 30, getWidth()/5, getHeight()/6);
    chaosSlider.setBounds(65, 33, chaosSlider.getTextBoxWidth(), getHeight() - 150);
    minBeatLabel.setBounds(chaosSlider.getX() - getWidth()/3, chaosSlider.getBottom() + 50, 140, 20);
    minBeatSlider.setBounds(chaosSlider.getX() - getWidth()/3 + minBeatLabel.getWidth(), chaosSlider.getBottom() + 50, 125, 25);
    
    // TODO smarter or automatic resizing. Like example from Juce audio parameter tutorial
    
}
