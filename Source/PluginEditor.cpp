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
    
    euclidLabel.setText("init", dontSendNotification);
    addAndMakeVisible(&euclidLabel);
    
    /* ------ Automation params and components added here ------ */
    randomToggleButton.setButtonText ("Random");
    randomToggleButton.setRadioGroupId(modeRadioGroupID);
    addAndMakeVisible (&randomToggleButton);
    randomAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "randomParamID", randomToggleButton);
    randomToggleButton.addListener(this);
    
    euclidToggleButton.setButtonText("Euclidean");
    euclidToggleButton.setRadioGroupId(modeRadioGroupID);
    euclidToggleButton.setColour(ToggleButton::ColourIds::textColourId, Colours::aqua);
    addAndMakeVisible(&euclidToggleButton);
    euclidAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "euclidParamID", euclidToggleButton);
    euclidToggleButton.addListener(this);
    
    standardToggleButton.setButtonText("Standard");
    standardToggleButton.setRadioGroupId(modeRadioGroupID);
    standardToggleButton.setToggleState(true, dontSendNotification);
    addAndMakeVisible(&standardToggleButton);
    standardAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "standardParamID", standardToggleButton);
    standardToggleButton.addListener(this);
    
    stereoToggleButton.setButtonText("Stereo");
    stereoToggleButton.setColour(ToggleButton::ColourIds::textColourId, Colours::aqua);
    addAndMakeVisible(&stereoToggleButton);
    stereoAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "stereoParamID", stereoToggleButton);
    
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
    mapXSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mapXSlider.setRange(0.0, 10.0, 1.0);
    mapXSlider.setChangeNotificationOnlyOnRelease(true);
    mapXSlider.setPopupDisplayEnabled (true, this);
    mapXSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mapXSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::aqua);
    addAndMakeVisible(&mapXSlider);
    mapXLabel.setText("X", dontSendNotification);
    mapXLabel.setSize(30, 20);
    mapXLabel.attachToComponent(&mapXSlider, false);
    mapXLabel.setColour(Label::ColourIds::textColourId, Colours::aqua);
    mapXSlider.setAlpha(0.2f);
    addAndMakeVisible(&mapXLabel);
    mapXAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mapXParamID", mapXSlider);
    
    /*** Map Y Slider Param ***/
    mapYSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mapYSlider.setRange(0.0, 10.0, 1.0);
    mapYSlider.setChangeNotificationOnlyOnRelease(true);
    mapYSlider.setPopupDisplayEnabled (true, this);
    mapYSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mapYSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::aqua);
    addAndMakeVisible(&mapYSlider);
    mapYLabel.setText("Y", dontSendNotification);
    mapYLabel.setSize(30, 20);
    mapYLabel.attachToComponent(&mapYSlider, false);
    mapYLabel.setColour(Label::ColourIds::textColourId, Colours::aqua);
    addAndMakeVisible(&mapYLabel);
    mapYAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mapYParamID", mapYSlider);
    
    /*** Kick Density Slider Param ***/
    kickDensitySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    kickDensitySlider.setRange(0.0, 127.0);
    kickDensitySlider.setPopupDisplayEnabled(true, this);
    kickDensitySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    kickDensitySlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::aqua);
    addAndMakeVisible(&kickDensitySlider);
    kickDensityLabel.setText("kick d", dontSendNotification);
    kickDensityLabel.setSize(30, 20);
    kickDensityLabel.attachToComponent(&kickDensitySlider, false);
    kickDensityLabel.setColour(Label::ColourIds::textColourId, Colours::aqua);
    addAndMakeVisible(&kickDensityLabel);
    kickDensityAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "kickDensityParamID", kickDensitySlider);
    
    /*** Snare Density Slider Param ***/
    snareDensitySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    snareDensitySlider.setRange(0.0, 127.0);
    snareDensitySlider.setPopupDisplayEnabled(true, this);
    snareDensitySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    snareDensitySlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::aqua);
    addAndMakeVisible(&snareDensitySlider);
    snareDensityLabel.setText("snare d", dontSendNotification);
    snareDensityLabel.setSize(30, 20);
    snareDensityLabel.attachToComponent(&snareDensitySlider, false);
    snareDensityLabel.setColour(Label::ColourIds::textColourId, Colours::aqua);
    addAndMakeVisible(&snareDensityLabel);
    snareDensityAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "snareDensityParamID", snareDensitySlider);
    
    /*** HH Density Slider Param ***/
    hhDensitySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    hhDensitySlider.setRange(0.0, 127.0);
    hhDensitySlider.setPopupDisplayEnabled(true, this);
    hhDensitySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    hhDensitySlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::aqua);
    addAndMakeVisible(&hhDensitySlider);
    hhDensityLabel.setText("hh d", dontSendNotification);
    hhDensityLabel.setSize(30, 20);
    hhDensityLabel.attachToComponent(&hhDensitySlider, false);
    hhDensityLabel.setColour(Label::ColourIds::textColourId, Colours::aqua);
    addAndMakeVisible(&hhDensityLabel);
    hhDensityAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "hhDensityParamID",hhDensitySlider);
    
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
    
    startTimer(300);
    mapXSlider.setAlpha(0.2f);
    mapXLabel.setAlpha(0.2f);
    mapYSlider.setAlpha(0.2f);
    mapYLabel.setAlpha(0.2f);
    kickDensitySlider.setAlpha(0.2f);
    kickDensityLabel.setAlpha(0.2f);
    snareDensitySlider.setAlpha(0.2f);
    snareDensityLabel.setAlpha(0.2f);
    hhDensitySlider.setAlpha(0.2f);
    hhDensityLabel.setAlpha(0.2f);
    stereoToggleButton.setAlpha(0.2f);
    
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
        if (randomToggleButton.getToggleState() || standardToggleButton.getToggleState())
            minBeatLabel.setText("Min beat: " + getMinBeatString(), dontSendNotification);
        if (euclidToggleButton.getToggleState())
            minBeatLabel.setText("Euclid beat: " + getGridBeatString(), dontSendNotification);
    }
}

String GenTremoloAudioProcessorEditor::getMinBeatString() {
    switch ((int)minBeatSlider.getValue()) {
        case 0:
            return "1/64th";
        case 1:
            return "1/32nd";
        case 2:
            return "1/16th";
        case 3:
            return "1/8th";
        case 4:
            return "1/4th";
        default:
            return "n/a";
    }
}


// TODO deal with the fact that the min beat slider has two choices for 1/4th... 64th beat doesn't work because its too small for euclidgrid resolution.
String GenTremoloAudioProcessorEditor::getGridBeatString() {
    switch ((int)minBeatSlider.getValue()) {
        case 0:
            return "1/32nd";
        case 1:
            return "1/16th";
        case 2:
            return "1/8th";
        case 3:
            return "1/4th";
        case 4:
            return "1/2";
        default:
            return "n/a";
    }
}

void GenTremoloAudioProcessorEditor::buttonClicked(Button* button) {
    if (button == &randomToggleButton || button == &standardToggleButton) {
        minBeatLabel.setText("Min beat: " + getMinBeatString(), dontSendNotification);
        waveformComboBox.setVisible(true);
        mapXSlider.setAlpha(0.2f);
        mapXLabel.setAlpha(0.2f);
        mapYSlider.setAlpha(0.2f);
        mapYLabel.setAlpha(0.2f);
        kickDensitySlider.setAlpha(0.2f);
        kickDensityLabel.setAlpha(0.2f);
        snareDensitySlider.setAlpha(0.2f);
        snareDensityLabel.setAlpha(0.2f);
        hhDensitySlider.setAlpha(0.2f);
        hhDensityLabel.setAlpha(0.2f);
        stereoToggleButton.setAlpha(0.2f);
    }
    if (button == &euclidToggleButton) {
        minBeatLabel.setText("Euclid beat: " + getGridBeatString(), dontSendNotification);
        waveformComboBox.setVisible(false);
        mapXSlider.setAlpha(1.0f);
        mapXLabel.setAlpha(1.0f);
        mapYSlider.setAlpha(1.0f);
        mapYLabel.setAlpha(1.0f);
        kickDensitySlider.setAlpha(1.0f);
        kickDensityLabel.setAlpha(1.0f);
        snareDensitySlider.setAlpha(1.0f);
        snareDensityLabel.setAlpha(1.0f);
        hhDensitySlider.setAlpha(1.0f);
        hhDensityLabel.setAlpha(1.0f);
        stereoToggleButton.setAlpha(1.0f);
    }
}

/* For testing purposes */
void GenTremoloAudioProcessorEditor::timerCallback() {
    if (processor.isEuclid) {
        String labelText = String("b ") + String(processor.euclidBeatDivisor) + String(" s ") + String(processor.euclidStep);
        euclidLabel.setText(labelText, dontSendNotification);
    } else {
        euclidLabel.setText("off", dontSendNotification);
    }
}

void GenTremoloAudioProcessorEditor::resized() {
    /* This is generally where you'll want to lay out the positions of any
     * subcomponents in your editor.. */
    
//    waveformComboBox.setBounds(getWidth()/2 + 15, 135 + getHeight()/4, getWidth()/3, getHeight()/7);
//    euclidLabel.setBounds(waveformComboBox.getX(), waveformComboBox.getY() + waveformComboBox.getHeight()/2 + 7, waveformComboBox.getWidth(), waveformComboBox.getHeight());
    
    waveformComboBox.setBounds(getWidth()/2 + 10, getWidth()/5 - getWidth()/7, getWidth()/3, getHeight()/7);
    euclidLabel.setBounds(waveformComboBox.getX(), waveformComboBox.getY() + waveformComboBox.getHeight()/2 + 7, waveformComboBox.getWidth(), waveformComboBox.getHeight());
    randomToggleButton.setBounds(getWidth()/2, waveformComboBox.getY() + waveformComboBox.getHeight()/2 + 60, getWidth()/5, getHeight()/6);
//    euclidToggleButton.setBounds(randomToggleButton.getX(), randomToggleButton.getY() + randomToggleButton.getHeight() + 5, randomToggleButton.getWidth(), randomToggleButton.getHeight());
//    stereoToggleButton.setBounds(euclidToggleButton.getX() + euclidToggleButton.getWidth(), euclidToggleButton.getY(), euclidToggleButton.getWidth(), euclidToggleButton.getHeight());
    standardToggleButton.setBounds(randomToggleButton.getX(), randomToggleButton.getY() + randomToggleButton.getHeight()/2 + 15, randomToggleButton.getWidth(), randomToggleButton.getHeight());
//    waveformComboBox.setBounds(getWidth()/2 + 10, standardToggleButton.getY()+getHeight()/7, getWidth()/3, getHeight()/7);
    euclidToggleButton.setBounds(standardToggleButton.getX(), standardToggleButton.getY() + standardToggleButton.getHeight()/2 + 15, standardToggleButton.getWidth(), standardToggleButton.getHeight());
    stereoToggleButton.setBounds(euclidToggleButton.getX() + euclidToggleButton.getWidth(), euclidToggleButton.getY(), euclidToggleButton.getWidth(), euclidToggleButton.getHeight());
    
    chaosSlider.setBounds(65, 33, chaosSlider.getTextBoxWidth(), getHeight() - 150);
//    mapXSlider.setBounds(chaosSlider.getRight()+chaosSlider.getWidth()/4, chaosSlider.getY(), chaosSlider.getWidth()/4, chaosSlider.getHeight());
//    mapYSlider.setBounds(mapXSlider.getRight()+mapXSlider.getWidth()/2+5, mapXSlider.getY(), mapXSlider.getWidth(), mapXSlider.getHeight());
    minBeatLabel.setBounds(chaosSlider.getX() - getWidth()/3 - 35, chaosSlider.getBottom() + 50, 140, 20);
    minBeatSlider.setBounds(chaosSlider.getX() - getWidth()/3 + minBeatLabel.getWidth() - 35, chaosSlider.getBottom() + 50, 125, 25);
    
    kickDensitySlider.setBounds(minBeatSlider.getX()+minBeatSlider.getWidth() + 5, minBeatSlider.getY(), 70, 70);
    snareDensitySlider.setBounds(kickDensitySlider.getX() + kickDensitySlider.getWidth() + 5, kickDensitySlider.getY(), kickDensitySlider.getWidth(), kickDensitySlider.getHeight());
    hhDensitySlider.setBounds(snareDensitySlider.getX()+snareDensitySlider.getWidth() + 5, kickDensitySlider.getY(), kickDensitySlider.getWidth(), kickDensitySlider.getHeight());
    mapXSlider.setBounds(hhDensitySlider.getX()+hhDensitySlider.getWidth()+5, kickDensitySlider.getY(), kickDensitySlider.getWidth(), kickDensitySlider.getHeight());
    mapYSlider.setBounds(mapXSlider.getX()+mapXSlider.getWidth()+5, kickDensitySlider.getY(), kickDensitySlider.getWidth(), kickDensitySlider.getHeight());

    
    // TODO smarter or automatic resizing. Like example from Juce audio parameter tutorial
    
}
