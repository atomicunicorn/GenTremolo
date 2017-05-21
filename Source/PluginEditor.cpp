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
    : AudioProcessorEditor (&p), valueTreeState(vts),  minBeatTabButtonBar(TabbedButtonBar::Orientation::TabsAtBottom), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 400);
    
    /* ------ Automation params and components added here ------ */
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
    
    
    // TODO look into making the minBeat controlled by a slider with an "IncDecButtons" SliderStyle!!!
    minBeatLabel.setText("Min beat", dontSendNotification);
    addAndMakeVisible(&minBeatLabel);
    // first tab added farthest left, last added farthest right...
    minBeatTabButtonBar.addTab("1/64th", tabColorRGBA, 0);
    minBeatTabButtonBar.addTab("1/32nd", tabColorRGBA, 1);
    minBeatTabButtonBar.addTab("1/16th", tabColorRGBA, 2);
    minBeatTabButtonBar.addTab("1/8th", tabColorRGBA, 3);
    minBeatTabButtonBar.addTab("1/4th", tabColorRGBA, 4);
    minBeatTabButtonBar.setName("Min beat");
    addAndMakeVisible(&minBeatTabButtonBar);
    
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
    g.drawFittedText ("Gen Tremolo e", getLocalBounds(), Justification::centredTop, 1);
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
    randomToggleButton.setBounds(getWidth()/2, 30, getWidth()/5, getHeight()/6);
    chaosSlider.setBounds(40, 30, 20, getHeight() - 120);
    Rectangle<int> chaosSliderBounds = chaosSlider.getBounds();
    chaosLabel.setBounds(chaosSliderBounds.getRight() - chaosSliderBounds.getWidth(), chaosSliderBounds.getBottom() + 10, 85, 35);
    Rectangle<int> chaosLabelBounds = chaosLabel.getBounds();
    minBeatTabButtonBar.setBounds(chaosLabelBounds.getRight(), chaosLabelBounds.getBottom() + 15, getWidth()/2, 30);
    Rectangle<int> minBarBounds = minBeatTabButtonBar.getBounds();
    minBeatLabel.setBounds(minBarBounds.getCentreX(), minBarBounds.getBottom()-minBarBounds.getHeight() - 11, minBarBounds.getWidth()/3, 10);
    
    // TODO smarter or automatic resizing. Like example from Juce audio parameter tutorial
    
}
