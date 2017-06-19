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
    
    /* universal colors */
    Colour testGridColour;
    Colour softOutlineColour;
    Colour opaqueStringColour;
    
    /* beta colors */
    Colour backgroundColour;
    Colour stringColour;
    Colour secondarySectionColour;
    Colour highlightColour;
    Colour tertiarySectionColour;
    Colour componentFillColour;
    Colour componentShadowColour;
    
    /* vaporwave colors */
    Colour vwBackgroundColour;
    Colour vwStringColour;
    Colour vwHighlightColour;
    Colour vwSecondarySectionColour;
    Colour vwTertiarySectionColour;
    Colour vwComponentFillColour;
    Colour vwComponentShadowColour;
    
    /* Typefaces and fonts */
    Typeface::Ptr bodyTypefacePtr;
    Typeface::Ptr titleTypefacePtr;
    const float titleFontSize = 19.0f;
    const float maxComponentFontSize = 15.0f;
    
    /* Other attributes */
    const float smallLineWidth = 0.5f;
    const float mediumLineWidth = 1.0f;
    const float largeLineWidth = 2.0f;
    const float hugeLineWidth = 3.0f;
    const float comboBoxTickHeight = 0.5f;
    
    DadBodLookAndFeel()
    {
        /* change this to switch between vapor wave and beta colors */
        const bool isVaporWaveColorScheme = true;
        
        /* assign universal colors */
        testGridColour = Colour::fromFloatRGBA(255.0f, 255.0f, 255.0f, 0.2f); // opaque white
        softOutlineColour = Colour(testGridColour);
        opaqueStringColour = Colour::fromFloatRGBA(166.0f, 207.0f, 213.0f, 0.2f); // opaque greyish
        
        /* vaporwave colors -- based on the color scheme of: http://imgur.com/JGhcvtF */
        vwBackgroundColour = Colour(10.0f,9.0f,44.0f); // dark navy
        vwStringColour = Colours::aqua; // light blue
        vwHighlightColour = Colour(251.0f,31.0f,254.0f); // neon pink
        vwSecondarySectionColour = Colour(246.0f, 81.0f, 29.0f);  // orange
        vwTertiarySectionColour = Colour(249.0f,43.0f,58.0f); // red
        vwComponentFillColour = Colour(23.0f, 0.0f, 137.0f); // lighter-than-medium-dark blue
        vwComponentShadowColour = Colour(12.0f,0.0f,75.0f); // medium-dark blue
        
        /* assign colors */
        if (isVaporWaveColorScheme ) {
            backgroundColour = Colour(vwBackgroundColour);
            stringColour = Colour(vwStringColour);
            highlightColour = Colour(vwHighlightColour);
            secondarySectionColour = Colour(vwSecondarySectionColour);
            tertiarySectionColour = Colour(vwTertiarySectionColour);
            componentFillColour = Colour(vwComponentFillColour);
            componentShadowColour = Colour(vwComponentShadowColour);
        } else {
            backgroundColour = Colour(18, 44, 52); // navy-ish
            stringColour = Colour(166, 207, 213); // light blue-ish grey
            highlightColour = Colours::aqua; // aqua
            secondarySectionColour = Colour(214,255,183); // light green
            tertiarySectionColour = Colour(findColour(ComboBox::ColourIds::buttonColourId));
            componentFillColour = Colour(stringColour);
            componentShadowColour = Colour(componentFillColour);
        }
        
        setColour(ResizableWindow::backgroundColourId, backgroundColour);
        setColour(Slider::ColourIds::rotarySliderFillColourId, componentFillColour);
        setColour(Slider::ColourIds::thumbColourId, highlightColour);
        setColour(Slider::ColourIds::rotarySliderOutlineColourId, softOutlineColour);
        setColour(Label::ColourIds::textColourId, stringColour);
        setColour(Label::ColourIds::textWhenEditingColourId, highlightColour);
        setColour(ToggleButton::ColourIds::tickColourId, stringColour);
        setColour(ToggleButton::ColourIds::tickDisabledColourId, softOutlineColour);
        setColour(HyperlinkButton::ColourIds::textColourId, secondarySectionColour);
        setColour(Label::ColourIds::outlineWhenEditingColourId, opaqueStringColour);
        setColour(ComboBox::ColourIds::backgroundColourId, componentFillColour);
        setColour(ComboBox::ColourIds::arrowColourId, stringColour);
        setColour(ComboBox::ColourIds::outlineColourId, softOutlineColour);
        setColour(ComboBox::ColourIds::textColourId, stringColour);
        setColour(PopupMenu::ColourIds::backgroundColourId, componentFillColour);
        setColour(PopupMenu::ColourIds::textColourId, stringColour);
        setColour(Slider::ColourIds::backgroundColourId, componentFillColour);
        setColour(Slider::ColourIds::textBoxBackgroundColourId, componentFillColour);
        setColour(Slider::ColourIds::trackColourId , componentFillColour);
        setColour(TextButton::ColourIds::buttonColourId, componentFillColour);
        setColour(TextButton::ColourIds::textColourOffId, stringColour);
        setColour(TextButton::ColourIds::textColourOnId, stringColour);
        
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
        g.setColour (findColour(Slider::ColourIds::rotarySliderFillColourId));
        g.fillEllipse (rx, ry, rw, rw);
        
        // outline
        g.setColour (findColour(Slider::ColourIds::rotarySliderOutlineColourId));
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
    
    void drawTickBox (Graphics& g, Component& component, float x, float y, float w, float h,
                                    const bool ticked, const bool isEnabled, const bool isMouseOverButton, const bool isButtonDown) override {
        
        ignoreUnused (isEnabled, isMouseOverButton, isButtonDown);
        
        Rectangle<float> tickBounds (x, y, w, h);
        
        /* modification on the two lines below */
        g.setColour(componentFillColour);
        g.fillRoundedRectangle(tickBounds, 4.0f);
        /* end of modification */
        
        g.setColour (component.findColour (ToggleButton::tickDisabledColourId));
        
        /* modified line thickness here */
        g.drawRoundedRectangle (tickBounds, 4.0f, 1.0f);
        
        if (ticked)
        {
            g.setColour (component.findColour (ToggleButton::tickColourId));
            const auto tick = getTickShape (0.75f);
            g.fillPath (tick, tick.getTransformToScaleToFit (tickBounds.reduced (4, 5).toFloat(), false));
        }
        
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
    
    void drawComboBox (Graphics& g, int width, int height, bool, int, int, int, int, ComboBox& box) override {
        const auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
        const Rectangle<int> boxBounds (0, 0, width, height);
        
        g.setColour (box.findColour (ComboBox::backgroundColourId));
        g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);
        
        g.setColour (box.findColour (ComboBox::outlineColourId));
        g.drawRoundedRectangle (boxBounds.toFloat().reduced (0.5f, 0.5f), cornerSize, 1.0f);
        
        Rectangle<int> arrowZone (width - 30, 0, 20, height);
        Path path;
        path.startNewSubPath (arrowZone.getX() + 3.0f, arrowZone.getCentreY() - 2.0f);
        path.lineTo (static_cast<float> (arrowZone.getCentreX()), arrowZone.getCentreY() + 3.0f);
        path.lineTo (arrowZone.getRight() - 3.0f, arrowZone.getCentreY() - 2.0f);
        
        g.setColour (box.findColour (ComboBox::arrowColourId).withAlpha ((box.isEnabled() ? 0.9f : 0.2f)));
        g.strokePath (path, PathStrokeType (2.0f));
    }
    
    Font getPopupMenuFont() override {
        return Font(bodyTypefacePtr);
    }
    
    /* This is called when a combobox is clicked. */
    void drawPopupMenuItem (Graphics& g, const Rectangle<int>& area, const bool isSeparator, const bool isActive,
                                            const bool isHighlighted, const bool isTicked, const bool hasSubMenu, const String& text, const String& shortcutKeyText,
                                            const Drawable* icon, const Colour* const textColourToUse) override {
        if (isSeparator) {
            auto r  = area.reduced (5, 0);
            r.removeFromTop (roundToInt ((r.getHeight() * 0.5f) - 0.5f));
            
            g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.3f));
            g.fillRect (r.removeFromTop (1));
        } else {
            auto textColour = (textColourToUse == nullptr ? findColour (PopupMenu::textColourId)
                               : *textColourToUse);
            
            auto r  = area.reduced (1);
            
            if (isHighlighted && isActive) {
                g.setColour (findColour (PopupMenu::highlightedBackgroundColourId));
                g.fillRect (r);
                
                g.setColour (findColour (PopupMenu::highlightedTextColourId));
            } else {
                g.setColour (textColour.withMultipliedAlpha (isActive ? 1.0f : 0.5f));
            }
            
            r.reduce (jmin (5, area.getWidth() / 20), 0);
            
            auto font = getPopupMenuFont();
            
            const auto maxFontHeight = r.getHeight() / 1.3f;
            
            if (font.getHeight() > maxFontHeight)
                font.setHeight (maxFontHeight);
            
            g.setFont (font);
            
            auto iconArea = r.removeFromLeft (roundToInt (maxFontHeight)).toFloat();
            
            if (icon != nullptr) {
                icon->drawWithin (g, iconArea, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
            } else if (isTicked) {
                
                /* MODIFIED the argument for getTickShape */
                const auto tick = getTickShape (comboBoxTickHeight);
                g.fillPath (tick, tick.getTransformToScaleToFit (iconArea.reduced (iconArea.getWidth() / 5, 0).toFloat(), true));
            }
            
            if (hasSubMenu) {
                const auto arrowH = 0.6f * getPopupMenuFont().getAscent();
                
                const auto x = (float) r.removeFromRight ((int) arrowH).getX();
                const auto halfH = (float) r.getCentreY();
                
                Path path;
                path.startNewSubPath (x, halfH - arrowH * 0.5f);
                path.lineTo (x + arrowH * 0.6f, halfH);
                path.lineTo (x, halfH + arrowH * 0.5f);
                
                g.strokePath (path, PathStrokeType (2.0f));
            }
            
            r.removeFromRight (3);
            g.drawFittedText (text, r, Justification::centredLeft, 1);
            
            if (shortcutKeyText.isNotEmpty()) {
                auto f2 = font;
                f2.setHeight (f2.getHeight() * 0.75f);
                f2.setHorizontalScale (0.95f);
                g.setFont (f2);
                
                g.drawText (shortcutKeyText, r, Justification::centredRight, true);
            }
        }
    }

};