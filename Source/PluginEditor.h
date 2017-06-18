/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "EuclidGrid.h"
#include <string>


//==============================================================================
/**
*/
class GenTremoloAudioProcessorEditor  : public AudioProcessorEditor, private ComboBox::Listener, private Slider::Listener, private Button::Listener, private Timer
{
public:
    GenTremoloAudioProcessorEditor (GenTremoloAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~GenTremoloAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox* comboBox) override;
    void sliderValueChanged(Slider* slider) override;
    void buttonClicked(Button* button) override;
    void timerCallback() override;
    
    String getMinBeatString();
    String getGridBeatString();
    
    /* public attributes */
    const int windowWidth = 500;
    const int windowHeight = 400;
    
    const float cornerSize = 4.0f;
    const int edgeMarginSize = 4;
    
    const int numMinBeatTabs = 5;
    
    Colour backgroundColour = Colour(18, 44, 52);
    Colour stringColour = Colour(166, 207, 213);
    Colour standardSectionColour = Colour(214,255,183);
    Colour tabColorRGBA = Colours::aqua;
    Colour euclidComponentsBackgroundColor = Colours::aqua;
    
    /* component locations */
    const int toggleHeight = 20;
    
    const int chaosSliderX = 333;
    const int chaosSliderY = 45;
    const int chaosSliderDiameter = 95;
    const int mixSliderX = 83;
    
    const int euclidToggleX = 20;
    const int euclidToggleY = 200;
    
    const int standardToggleY = 333;
    
    const int minBeatSliderWidth = 125;
    const int minBeatSliderHeight = 25;
    
    const int togglesTop = 0;
    const int togglesBottom = 0;
    const int togglesLeft = 0;
    const int togglesRight = 0;
    
    const int euclidKnobDiameter = 70;
    const int knobXOffset = 75;
    
    const int waveformX = 340;
    
    /* title box coords */
    const int titleBoxBottom = 20;
    const int titleBoxY = 10;
    
    /* top box coords */
    const int topBoxTop = 20;
    const int topBoxBottom = 133;
    const int topBoxY = 76;
    
    /* euclid box coords */
    const int euclidBoxTop = 166;
    const int euclidBoxBottom = 268;
    const int euclidBoxY = 180;
    
    const float boxLineWidth = 1.0f;
    const int euclidRowLeft = 130;
    const int euclidRowRight = 493;
    const int euclidRowTop = 160;
    const int euclidRowBottom = 240;
    
    /* lfo box coords */
    const int lfoBoxTop = 306;
    const int lfoBoxBottom = 399;
    const int lfoBoxY = 333;
    
    

private:
    
    /* Methods */
    
    
    /* Parameter-related objects */
    AudioProcessorValueTreeState& valueTreeState;
    const int modeRadioGroupID = 1;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> randomAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> euclidAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> standardAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> stereoAttachment;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> chaosAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> minBeatAttachment;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> kickDensityAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> snareDensityAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> hhDensityAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mapXAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mapYAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> euclidBeatAttachment; // TODO remove this

    /* Components */
    ToggleButton randomToggleButton;
    ToggleButton euclidToggleButton;
    ToggleButton standardToggleButton;
    
    ToggleButton stereoToggleButton;
    
    Label mixLabel;
    Slider mixSlider;
    
    Label chaosLabel;
    Slider chaosSlider;
    
    Label kickDensityLabel;
    Slider kickDensitySlider;
    Label snareDensityLabel;
    Slider snareDensitySlider;
    Label hhDensityLabel;
    Slider hhDensitySlider;
    
    Label mapXLabel;
    Slider mapXSlider;
    Label mapYLabel;
    Slider mapYSlider;
    
    Label minBeatLabel;
    Slider minBeatSlider;
    
    Label euclidLabel;
    
    ComboBox waveformComboBox;
    
    /* Misc attributes */

    /* This reference is provided as a quick way for your editor to
     * access the processor object that created it. */
    GenTremoloAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenTremoloAudioProcessorEditor)
};
