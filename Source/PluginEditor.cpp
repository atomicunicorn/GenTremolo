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
//    depthLabel_.attachToComponent(&depthSlider_, false);
//    depthLabel_.setFont(Font (11.0f));
//    beatLabel = new Label("Beat", "Beat");
//    beatLabel->attachToComponent(beatLabel, false);
//    beatLabel->setFont(Font(11.0f));
//    addAndMakeVisible(beatLabel);
//    startTimer(50);
    addAndMakeVisible (&randomButton);
    randomButton.setButtonText ("Randomize off");
    randomButton.addListener(this);
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
//        timeLabel.setText (currentTimeString, dontSendNotification);
    }
}

void GenTremoloAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    randomButton.setBounds (40, 30, getWidth() - 100, getHeight()/4);
}
