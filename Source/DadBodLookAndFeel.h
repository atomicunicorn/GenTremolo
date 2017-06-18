/*
  ==============================================================================

    DadBodLookAndFeel.h
    Created: 18 Jun 2017 1:44:40am
    Author:  Zachary Gottesman

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DadBodLookAndFeel : public LookAndFeel_V4
{
public:
    
    /* colors */
    Colour backgroundColour;
    Colour stringColour;
    Colour opaqueStringColour;
    Colour testGridColour;
    Colour secondarySectionColour;
    Colour highlightColour;
    
    /* vaporwave colors */
    Colour vwBackgroundColour;
    Colour vwStringColour;
    Colour vwOpaqueStringColour;
    Colour vwSecondarySectionColour;
    Colour vwHighlightColour;
    Colour vwTertiarySectionColour;
    
    /* Typefaces and fonts */
    Typeface::Ptr bodyTypefacePtr;
    Typeface::Ptr titleTypefacePtr;
    const float titleFontSize = 19.0f;
    const float maxComponentFontSize = 15.0f;
    
    DadBodLookAndFeel()
    {
        /* vaporwave colors */
        vwBackgroundColour = Colour();
        vwStringColour = Colour();
        vwHighlightColour = Colour();
        vwSecondarySectionColour = Colour();
        vwTertiarySectionColour = Colour();
        vwOpaqueStringColour = Colour();
        
        /* assign default colors */
        backgroundColour = Colour(18, 44, 52); // navy-ish
        stringColour = Colour(166, 207, 213); // light blue-ish grey
        opaqueStringColour = Colour::fromFloatRGBA(166.0f, 207.0f, 213.0f, 0.2f); // opaque greyish 
        testGridColour = Colour::fromFloatRGBA(255.0f, 255.0f, 255.0f, 0.2f); // opaque white
        secondarySectionColour = Colour(214,255,183); // light green
        highlightColour = Colours::aqua; // aqua
        
        setColour(ResizableWindow::backgroundColourId, backgroundColour);
        setColour(Slider::ColourIds::rotarySliderFillColourId, stringColour);
        setColour(Label::ColourIds::textColourId, stringColour);
        setColour(Label::ColourIds::textWhenEditingColourId, highlightColour);
        setColour(ToggleButton::ColourIds::tickColourId, stringColour);
        setColour(HyperlinkButton::ColourIds::textColourId, secondarySectionColour);
        setColour(Label::ColourIds::outlineWhenEditingColourId, opaqueStringColour);
        setColour(ComboBox::ColourIds::arrowColourId, stringColour);
        setColour(ComboBox::ColourIds::outlineColourId, secondarySectionColour);
        setColour(ComboBox::ColourIds::textColourId, secondarySectionColour);
        
        /* assign fonts */
        bodyTypefacePtr = Typeface::createSystemTypefaceFor(BinaryData::VT323Regular_ttf, BinaryData::VT323Regular_ttfSize);
        titleTypefacePtr = Typeface::createSystemTypefaceFor(BinaryData::VCR_OSD_MONO_1_001_ttf, BinaryData::VCR_OSD_MONO_1_001_ttfSize);
        
    }
    
    /*** CUSTOM METHODS BELOW ***/
    
    Colour getBackgroundColour() {
        return backgroundColour;
    }
    
    Colour getStringColour() {
        return stringColour;
    }
    
    Colour getOpaqueStringColour() {
        return opaqueStringColour;
    }
    
    Colour getSecondarySectionColour() {
        return secondarySectionColour;
    }
    
    Colour getHighlightColour() {
        return highlightColour;
    }
    
    Colour getTestGridColour() {
        return testGridColour;
    }
    
    float getTitleFontSize() {
        return titleFontSize;
    }
    
    float getMaxComponentFontSize() {
        return maxComponentFontSize;
    }
    
    Typeface::Ptr getBodyTypefacePtr() {
        return bodyTypefacePtr;
    }
    
    Typeface::Ptr getTitleTypefacePtr() {
        return titleTypefacePtr;
    }
    
    /* Need to copy construct the returned value of this function. Look at how getToggleButtonFont is called. */
    Font getScaledTitleFont(int requestedFontHeight) {
        const float fontHeight = jmin(maxComponentFontSize, requestedFontHeight * 0.75f);
        Font f = Font(titleTypefacePtr);
        f.setHeightWithoutChangingWidth(fontHeight);
        return f;
    }
    
    /* Need to copy construct the returned value of this function. Look at how getToggleButtonFont is called. */
    Font getUnscaledTitleFont(int requestedFontHeight) {
        const float fontHeight = requestedFontHeight;
        Font f = Font(titleTypefacePtr);
        f.setHeightWithoutChangingWidth(fontHeight);
        return f;
    }
    
    /* Need to copy construct the returned value of this function. Look at how getToggleButtonFont is called. */
    Font getScaledBodyFont(int requestedFontHeight) {
        const float fontHeight = jmin(maxComponentFontSize, requestedFontHeight * 0.75f);
        Font f = Font(bodyTypefacePtr);
        f.setHeightWithoutChangingWidth(fontHeight);
        return f;
    }
    
    /* Need to copy construct the returned value of this function. Look at how getToggleButtonFont is called. */
    Font getUnscaledBodyFont(int requestedFontHeight) {
        const float fontHeight = jmin(maxComponentFontSize, requestedFontHeight * 0.75f);
        Font f = Font(bodyTypefacePtr);
        f.setHeightWithoutChangingWidth(fontHeight);
        return f;
    }
    
    /* Need to copy construct the returned value of this function. Look at how this is called within drawToggleButton here. */
    Font getToggleButtonFont (ToggleButton &, int buttonHeight) {
        const float fontHeight = jmin(15.0f, buttonHeight * 0.75f);
        Font f = Font(bodyTypefacePtr);
        f.setHeightWithoutChangingWidth(fontHeight);
        return f;
    }
    
    /*** OVERRIDEN METHODS BELOW ***/
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        const float radius = jmin (width / 2, height / 2) - 4.0f;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (stringColour);
        g.fillEllipse (rx, ry, rw, rw);
        
        // outline
        g.setColour (testGridColour);
        g.drawEllipse (rx, ry, rw, rw, 1.0f);
        
        // knob pointer line
        Path p;
        const float pointerLength = radius * 0.33f;
        const float pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        // pointer
        g.setColour (Colours::aqua);
        g.fillPath (p);
    }
    
    Font getTextButtonFont (TextButton &, int buttonHeight) override {
        const float fontHeight = jmin(15.0f, buttonHeight * 0.6f);
        Font f = Font(bodyTypefacePtr);
        f.setHeightWithoutChangingWidth(fontHeight);
        return f;
    }
    
    Font getLabelFont(Label &) override {
        return Font(bodyTypefacePtr);
    }
    
    Font getComboBoxFont (ComboBox &) override {
        return Font(bodyTypefacePtr);
    }
    
    Typeface::Ptr getTypefaceForFont (const Font &) override {
        return bodyTypefacePtr;
    }
    
    void drawToggleButton (Graphics& g, ToggleButton& button, bool isMouseOverButton, bool isButtonDown) override {
        const auto fontSize = jmin (15.0f, button.getHeight() * 0.75f);
        const auto tickWidth = fontSize * 1.1f;
        
        Font font (getToggleButtonFont(button, button.getHeight()));
        
        drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
                     tickWidth, tickWidth,
                     button.getToggleState(),
                     button.isEnabled(),
                     isMouseOverButton,
                     isButtonDown);
        
        g.setColour (button.findColour (ToggleButton::textColourId));
        g.setFont (font);
        
        if (! button.isEnabled())
            g.setOpacity (0.5f);
        
        const auto textX = roundToInt (tickWidth) + 10;
        
        g.drawFittedText (button.getButtonText(), textX, 0, button.getWidth() - textX - 2, button.getHeight(),
                          Justification::centredLeft, 10);
    }

};