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
    
    euclidIsPlayingLabel.setText("n playing", dontSendNotification);
    addAndMakeVisible(&euclidIsPlayingLabel);
    
    
    /* ------ Automation params and components added here ------ */
    randomToggleButton.setButtonText ("Random");
    randomToggleButton.setRadioGroupId(modeRadioGroupID);
    addAndMakeVisible (&randomToggleButton);
    randomAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "randomParamID", randomToggleButton);
    
    euclidToggleButton.setButtonText("Euclidean");
    euclidToggleButton.setRadioGroupId(modeRadioGroupID);
    addAndMakeVisible(&euclidToggleButton);
    euclidAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "euclidParamID", euclidToggleButton);
    
    standardToggleButton.setButtonText("Standard");
    standardToggleButton.setRadioGroupId(modeRadioGroupID);
    standardToggleButton.setToggleState(true, dontSendNotification);
    addAndMakeVisible(&standardToggleButton);
    standardAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "standardParamID", standardToggleButton);
    
    /*** Chaos Slider Param ***/
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
    
    /*** Map X Slider Param ***/
    mapXSlider.setSliderStyle (Slider::LinearVertical);
    mapXSlider.setRange(0.0, 10.0, 1.0);
    mapXSlider.setChangeNotificationOnlyOnRelease(true);
    mapXSlider.setPopupDisplayEnabled (false, this);
//    mapXSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 10, 20);
    addAndMakeVisible(&mapXSlider);
    mapXLabel.setText("X", dontSendNotification);
    mapXLabel.attachToComponent(&mapXSlider, true);
    addAndMakeVisible(&mapXLabel);
    mapXAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mapXParamID", mapXSlider);
    
    /*** Map Y Slider Param ***/
    mapYSlider.setSliderStyle (Slider::LinearVertical);
    mapYSlider.setRange(0.0, 10.0, 1.0);
    mapYSlider.setChangeNotificationOnlyOnRelease(true);
    mapYSlider.setPopupDisplayEnabled (false, this);
    //    mapXSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 10, 20);
    addAndMakeVisible(&mapYSlider);
    mapYLabel.setText("Y", dontSendNotification);
    mapYLabel.attachToComponent(&mapYSlider, true);
    addAndMakeVisible(&mapYLabel);
    mapYAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mapYParamID", mapYSlider);
    
    
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
    
    startTimer(15);
    
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
    g.drawFittedText ("Gen Tremolo f", getLocalBounds(), Justification::centredTop, 1);
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

void GenTremoloAudioProcessorEditor::hiResTimerCallback() {
    if (processor.isEuclid && processor.isPlayingEuclidNote) {
        String bString = processor.isPlayingEuclidNote ? "playing" : "not playing";
        euclidIsPlayingLabel.setText(bString, dontSendNotification);
    } else {
        if (processor.isEuclid) {
            String bString = processor.isPlayingEuclidNote ? "note on" : "note off";
            euclidIsPlayingLabel.setText(bString, dontSendNotification);
        }
    }
}

void GenTremoloAudioProcessorEditor::resized() {
    /* This is generally where you'll want to lay out the positions of any
     * subcomponents in your editor.. */
    
    waveformComboBox.setBounds(getWidth()/2, 170 + getHeight()/4, getWidth()/3, getHeight()/7);
    euclidIsPlayingLabel.setBounds(waveformComboBox.getX(), waveformComboBox.getY() + waveformComboBox.getHeight()/2 + 3, waveformComboBox.getWidth(), waveformComboBox.getHeight());
    
    randomToggleButton.setBounds(getWidth()/2, 30, getWidth()/5, getHeight()/6);
    euclidToggleButton.setBounds(randomToggleButton.getX(), randomToggleButton.getY() + randomToggleButton.getHeight() + 5, randomToggleButton.getWidth(), randomToggleButton.getHeight());
    standardToggleButton.setBounds(euclidToggleButton.getX(), euclidToggleButton.getY() + euclidToggleButton.getHeight() + 5, euclidToggleButton.getWidth(), euclidToggleButton.getHeight());
    
    chaosSlider.setBounds(65, 33, chaosSlider.getTextBoxWidth(), getHeight() - 150);
    mapXSlider.setBounds(chaosSlider.getRight()+chaosSlider.getWidth()/4, chaosSlider.getY(), chaosSlider.getWidth()/4, chaosSlider.getHeight());
    mapYSlider.setBounds(mapXSlider.getRight()+mapXSlider.getWidth()/2+5, mapXSlider.getY(), mapXSlider.getWidth(), mapXSlider.getHeight());
    minBeatLabel.setBounds(chaosSlider.getX() - getWidth()/3, chaosSlider.getBottom() + 50, 140, 20);
    minBeatSlider.setBounds(chaosSlider.getX() - getWidth()/3 + minBeatLabel.getWidth(), chaosSlider.getBottom() + 50, 125, 25);
    
    // TODO smarter or automatic resizing. Like example from Juce audio parameter tutorial
    
}
