/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "EuclidGrid.h"
#include "DadBodLookAndFeel.h"


//==============================================================================
GenTremoloAudioProcessorEditor::GenTremoloAudioProcessorEditor (GenTremoloAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState(vts), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (windowWidth, windowHeight);
    setLookAndFeel(&dadBodLookAndFeel);
    
    vFontPtr = Typeface::createSystemTypefaceFor(BinaryData::VT323Regular_ttf, BinaryData::VT323Regular_ttfSize);
    
    testLabel.setText("init", dontSendNotification);
    addAndMakeVisible(&testLabel);
    
    /* ------ Automation params and components added here ------ */
    
    euclidTextButton.setButtonText("Euclid");
    euclidTextButton.setRadioGroupId(modeRadioGroupID);
    euclidTextButton.setClickingTogglesState(true);
    addAndMakeVisible(&euclidTextButton);
    euclidAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "euclidParamID", euclidTextButton);
    euclidTextButton.addListener(this);
    
    lfoTextButton.setButtonText("LFO");
    lfoTextButton.setRadioGroupId(modeRadioGroupID);
    lfoTextButton.setClickingTogglesState(true);
    addAndMakeVisible(&lfoTextButton);
//    standardAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "standardParamID", lfoTextButton);
    lfoTextButton.addListener(this);
    
    
    randomToggleButton.setButtonText ("Random");
    randomToggleButton.setColour(ToggleButton::ColourIds::textColourId, dadBodLookAndFeel.getSecondarySectionColour());
    addAndMakeVisible (&randomToggleButton);
    randomAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "randomParamID", randomToggleButton);
    randomToggleButton.addListener(this);
    
    stereoToggleButton.setButtonText("Stereo");
    stereoToggleButton.setColour(ToggleButton::ColourIds::textColourId, dadBodLookAndFeel.getHighlightColour());
    addAndMakeVisible(&stereoToggleButton);
    stereoAttachment = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "stereoParamID", stereoToggleButton);
    
    /*** Mix Slider Param ***/
    mixSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mixSlider.setChangeNotificationOnlyOnRelease(true);
    mixSlider.setPopupDisplayEnabled (true, this);
    mixSlider.setChangeNotificationOnlyOnRelease(false);
    mixSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&mixSlider);
    mixLabel.setText("Mix", dontSendNotification);
    mixLabel.setJustificationType(Justification::centredBottom);
    mixLabel.setBounds(mixLabel.getX(), 18, mixLabel.getWidth(), mixLabel.getHeight());
    mixLabel.attachToComponent(&mixSlider, false);
    addAndMakeVisible(&mixLabel);
    mixAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mixParamID", mixSlider);
    
    /*** Chaos Slider Param ***/
    // TODO look at docs for NormalisableRange.snapToLegalValue. might work for discrete chaos value fix...
    chaosSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    chaosSlider.setChangeNotificationOnlyOnRelease(true);
    chaosSlider.setPopupDisplayEnabled (true, this);
    chaosSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&chaosSlider);
    chaosLabel.setText("Chaos Amount", dontSendNotification);
    chaosLabel.setJustificationType(Justification::centredBottom);
    chaosLabel.attachToComponent(&chaosSlider, false);
    addAndMakeVisible(&chaosLabel);
    chaosAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "chaosParamID", chaosSlider);
    
    /*** Map X Slider Param ***/
    mapXSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mapXSlider.setChangeNotificationOnlyOnRelease(true);
    mapXSlider.setPopupDisplayEnabled (true, this);
    mapXSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&mapXSlider);
    mapXLabel.setText("X", dontSendNotification);
    mapXLabel.setSize(30, 20);
    mapXLabel.attachToComponent(&mapXSlider, false);
    mapXLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&mapXLabel);
    mapXAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mapXParamID", mapXSlider);
    
    /*** Map Y Slider Param ***/
    mapYSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mapYSlider.setChangeNotificationOnlyOnRelease(true);
    mapYSlider.setPopupDisplayEnabled (true, this);
    mapYSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&mapYSlider);
    mapYLabel.setText("Y", dontSendNotification);
    mapYLabel.setSize(30, 20);
    mapYLabel.attachToComponent(&mapYSlider, false);
    mapYLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&mapYLabel);
    mapYAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mapYParamID", mapYSlider);
    
    /*** Kick Density Slider Param ***/
    kickDensitySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    kickDensitySlider.setPopupDisplayEnabled(true, this);
    kickDensitySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    kickDensitySlider.setColour(Slider::ColourIds::rotarySliderFillColourId, dadBodLookAndFeel.getHighlightColour());
    addAndMakeVisible(&kickDensitySlider);
    kickDensityLabel.setText("density 1", dontSendNotification);
    kickDensityLabel.setSize(30, 20);
    kickDensityLabel.attachToComponent(&kickDensitySlider, false);
    kickDensityLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&kickDensityLabel);
    kickDensityAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "kickDensityParamID", kickDensitySlider);
    
    /*** Snare Density Slider Param ***/
    snareDensitySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    snareDensitySlider.setPopupDisplayEnabled(true, this);
    snareDensitySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    snareDensitySlider.setColour(Slider::ColourIds::rotarySliderFillColourId, dadBodLookAndFeel.getHighlightColour());
    addAndMakeVisible(&snareDensitySlider);
    snareDensityLabel.setText("density 2", dontSendNotification);
    snareDensityLabel.setSize(30, 20);
    snareDensityLabel.attachToComponent(&snareDensitySlider, false);
    snareDensityLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&snareDensityLabel);
    snareDensityAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "snareDensityParamID", snareDensitySlider);
    
    /*** HH Density Slider Param ***/
    hhDensitySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    hhDensitySlider.setPopupDisplayEnabled(true, this);
    hhDensitySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    hhDensitySlider.setColour(Slider::ColourIds::rotarySliderFillColourId, dadBodLookAndFeel.getHighlightColour());
    addAndMakeVisible(&hhDensitySlider);
    hhDensityLabel.setText("density 3", dontSendNotification);
    hhDensityLabel.setSize(30, 20);
    hhDensityLabel.attachToComponent(&hhDensitySlider, false);
    hhDensityLabel.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&hhDensityLabel);
    hhDensityAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "hhDensityParamID",hhDensitySlider);
    
    minBeatSlider.setSliderStyle(Slider::IncDecButtons);
    minBeatSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&minBeatSlider);
    minBeatSlider.addListener(this);
    minBeatLabel.setJustificationType(Justification::centredBottom);
    minBeatLabel.attachToComponent(&minBeatSlider, false);
    addAndMakeVisible(&minBeatLabel);
    minBeatAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "minBeatParamID", minBeatSlider);
    
    euclidBeatSlider.setSliderStyle(Slider::IncDecButtons);
    euclidBeatSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&euclidBeatSlider);
    euclidBeatSlider.addListener(this);
    euclidBeatLabel.setJustificationType(Justification::centredBottom);
    euclidBeatLabel.attachToComponent(&euclidBeatSlider, false);
    addAndMakeVisible(&euclidBeatLabel);
    minBeatAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "euclidBeatParamID", euclidBeatSlider);
    
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
    
    if (euclidTextButton.getToggleState()) {
        minBeatSlider.setAlpha(0.2f);
        minBeatLabel.setAlpha(0.2f);
        euclidBeatLabel.setAlpha(1.0f);
        euclidBeatSlider.setAlpha(1.0f);
        randomToggleButton.setAlpha(0.2f);
        waveformComboBox.setAlpha(0.2f);
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
    } else {
        minBeatSlider.setAlpha(1.0f);
        minBeatLabel.setAlpha(1.0f);
        euclidBeatLabel.setAlpha(0.2f);
        randomToggleButton.setAlpha(1.0f);
        waveformComboBox.setAlpha(1.0f);
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
        euclidBeatSlider.setAlpha(0.2f);
    }
    
    minBeatLabel.setText("LFO min beat: " + getMinBeatString(), dontSendNotification);
    euclidBeatLabel.setText("Euclid min beat: " + getGridBeatString(), dontSendNotification);
    
}

GenTremoloAudioProcessorEditor::~GenTremoloAudioProcessorEditor()
{
}

//==============================================================================
void GenTremoloAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour(getLookAndFeel().findColour(Label::ColourIds::textColourId));
    g.setFont(dadBodLookAndFeel.getTitleTypefacePtr());
    g.setFont(dadBodLookAndFeel.getTitleFontSize());
    Rectangle<int> topBoxArea = Rectangle<int>(6, 6, getWidth() - 12, 133);
    Rectangle<int> titleShadowArea = Rectangle<int>(4, 7, getWidth() - 12, 133);
    g.setColour(dadBodLookAndFeel.getHighlightColour());
    g.drawFittedText("Gen Tremolo 0.0.1", titleShadowArea, Justification::centredTop, 1);
    g.setColour(getLookAndFeel().findColour(Label::ColourIds::textColourId));
    g.drawFittedText("Gen Tremolo 0.0.1", topBoxArea, Justification::centredTop, 1);
    
    /* draw top box */
    g.setColour(getLookAndFeel().findColour(Label::ColourIds::textColourId));
    g.drawRoundedRectangle(6.0f, 6.0f, (float)getWidth()-12.0f, 127.0f, cornerSize, dadBodLookAndFeel.mediumLineWidth);
    /* draw euclid box */
    g.setColour(dadBodLookAndFeel.getHighlightColour());
    g.drawRoundedRectangle(4.0f, 4.0f, (float)getWidth() - 8.0f, 263.0f, cornerSize, dadBodLookAndFeel.mediumLineWidth);
    /* draw LFO box */
    g.setColour(dadBodLookAndFeel.getSecondarySectionColour());
    g.drawRoundedRectangle(2.0f, 2.0f, (float)getWidth() - 4.0f, 396.0f, cornerSize, dadBodLookAndFeel.mediumLineWidth);
    float lineWidth = (float)getWidth() - 1.0f;

    g.setColour(dadBodLookAndFeel.getOpaqueStringColour());
    g.drawRect(1.0f, (float)topBoxBottom, lineWidth, 1.0f);   // top box divider line
    g.drawRect(1.0f, (float)euclidBoxBottom, lineWidth, 1.0f); // euclid box divider line
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
        minBeatLabel.setText("LFO min beat: " + getMinBeatString(), dontSendNotification);
    }
    if (slider == &euclidBeatSlider) {
        euclidBeatLabel.setText("Euclid min beat: " + getGridBeatString(), dontSendNotification);
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
    switch ((int)euclidBeatSlider.getValue()) {
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
    if (button == &lfoTextButton) {
        minBeatSlider.setAlpha(1.0f);
        minBeatLabel.setAlpha(1.0f);
        euclidBeatLabel.setAlpha(0.2f);
        euclidBeatSlider.setAlpha(0.2f);
        randomToggleButton.setAlpha(1.0f);
        waveformComboBox.setAlpha(1.0f);
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
    if (button == &euclidTextButton) {
        euclidBeatSlider.setAlpha(1.0f);
        minBeatSlider.setAlpha(0.2f);
        minBeatLabel.setAlpha(0.2f);
        euclidBeatLabel.setAlpha(1.0f);
        randomToggleButton.setAlpha(0.2f);
        waveformComboBox.setAlpha(0.2f);
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
        minBeatSlider.setAlpha(0.2f);
    }
}

/* For testing purposes - remove timer for production releases */
void GenTremoloAudioProcessorEditor::timerCallback() {
    testLabel.setText("t: " + String(euclidTextButton.getToggleState()), dontSendNotification);
}

void GenTremoloAudioProcessorEditor::resized() {
    /* This is generally where you'll want to lay out the positions of any
     * subcomponents in your editor.. */
    
    /*** Top Box ***/
    euclidTextButton.setBounds(getWidth()/4, getHeight()/6 - getHeight()/16 + 4, getWidth()/6, getHeight()/9);
    lfoTextButton.setBounds(getWidth()/12*7 + 3, euclidTextButton.getY(), getWidth()/6, getHeight()/9);
    randomToggleButton.setBounds(lfoTextButton.getX(), lfoTextButton.getY() + lfoTextButton.getHeight() + 6, getWidth()/6, toggleHeight);
    stereoToggleButton.setBounds(euclidTextButton.getX(), euclidTextButton.getY()+euclidTextButton.getHeight() + 6, getWidth()/6, toggleHeight);
    chaosSlider.setBounds(getWidth()/6*5 - euclidKnobDiameter/2, chaosSliderY - chaosSliderDiameter/6 + 4, euclidKnobDiameter, euclidKnobDiameter);
    mixSlider.setBounds(getWidth()/6 - euclidKnobDiameter/2, chaosSliderY - chaosSliderDiameter/6 + 4, euclidKnobDiameter, euclidKnobDiameter);
    
    /*** Euclid Box ***/
    kickDensitySlider.setBounds(firstEuclidKnobX, euclidKnobY, euclidKnobDiameter, euclidKnobDiameter);
    snareDensitySlider.setBounds(kickDensitySlider.getX() + knobXOffset, euclidKnobY, euclidKnobDiameter, euclidKnobDiameter);
    hhDensitySlider.setBounds(snareDensitySlider.getX() + knobXOffset, euclidKnobY, euclidKnobDiameter, euclidKnobDiameter);
    mapXSlider.setBounds(hhDensitySlider.getX() + knobXOffset, euclidKnobY, euclidKnobDiameter, euclidKnobDiameter);
    mapYSlider.setBounds(mapXSlider.getX() + knobXOffset, euclidKnobY, euclidKnobDiameter, euclidKnobDiameter);
    
    /*** LFO Box ***/
    waveformComboBox.setBounds(waveformX, lfoBoxY - getHeight()/14, getWidth()/4, getHeight()/7);
    testLabel.setBounds(waveformComboBox.getX(), waveformComboBox.getY() - waveformComboBox.getHeight()/2 - 7, waveformComboBox.getWidth(), waveformComboBox.getHeight());
    
    euclidBeatLabel.setBounds(getWidth()/2 - 70, 3*getHeight()/4 - 10, 140, 20);
    euclidBeatSlider.setBounds(getWidth()/2 - minBeatSliderWidth/2, 3*getHeight()/4 - minBeatSliderHeight/2, minBeatSliderWidth, minBeatSliderHeight);
    minBeatLabel.setBounds(getWidth()/2 - 70, 11*getHeight()/12 - 10, 140, 20);
    minBeatSlider.setBounds(getWidth()/2 - minBeatSliderWidth/2, 11*getHeight()/12 - minBeatSliderHeight/2, minBeatSliderWidth, minBeatSliderHeight);

    
    // TODO smarter or automatic resizing. Like example from Juce audio parameter tutorial
    
}
