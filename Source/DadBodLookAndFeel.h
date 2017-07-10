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
    Colour componentIntermediateShadowColour;
    
    /* vaporwave colors */
    Colour vwBackgroundColour;
    Colour vwStringColour;
    Colour vwHighlightColour;
    Colour vwSecondarySectionColour;
    Colour vwTertiarySectionColour;
    Colour vwComponentFillColour;
    Colour vwComponentShadowColour;
    
    const float componentFillContrast = 0.1f;
    
    /* svg files */
    String svgFilePath = "/Users/zig/git_stuff/GenTremolo/hexmap_half_inch.svg";
    
    /* Typefaces and fonts */
    Typeface::Ptr bodyTypefacePtr;
    Typeface::Ptr titleTypefacePtr;
    Typeface::Ptr alienBoldTypefacePtr;
    Typeface::Ptr alienSolidBoldTypefacePtr;
//    const float titleFontSize = 19.0f;
    const float titleFontSize = 28.5f;
    const float maxComponentFontSize = 15.0f;
    const float textButtonFontSize = 20.0f;
    
    /* Line widths */
    const float smallLineWidth = 0.5f;
    const float mediumLineWidth = 1.0f;
    const float largeLineWidth = 2.0f;
    const float hugeLineWidth = 3.0f;
    
    /* toggle sizes */
    const int defaultToggleHeight = 28;
    const float comboBoxTickHeight = 0.5f;
    const float tickBoxMarginSize = 3.0f;
    
    /* knob sizes */
    const int mediumKnobDiameter = 70;
    const int largeKnobDiameter = 82;
    const int giantKnobDiameter = 95;
    const float lightArcMargin = 1.0f;
    const float innerLightArcMargin = 1.0f;
    const float lightArcThickness = 0.8f;
    
    /* margin sizes */
    const float smallMarginSize = tickBoxMarginSize;
    const float mediumMarginSize = 2.0f*tickBoxMarginSize;
    const float largeMarginSize = 2.0f*mediumMarginSize;
    
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
//        vwBackgroundColour = Colours::white;
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
        
//        componentIntermediateShadowColour = Colour(getMidpointColour(componentFillColour, componentShadowColour));
        componentIntermediateShadowColour = Colour(17.0f, 0.0f, 106.0f);
//        setIntermediateShadowColour(componentFillColour, componentShadowColour);
        
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
        setColour(TextButton::ColourIds::textColourOnId, componentFillColour);
        
        /* assign fonts */
        bodyTypefacePtr = Typeface::createSystemTypefaceFor(BinaryData::VT323Regular_ttf, BinaryData::VT323Regular_ttfSize);
        titleTypefacePtr = Typeface::createSystemTypefaceFor(BinaryData::VCR_OSD_MONO_1_001_ttf, BinaryData::VCR_OSD_MONO_1_001_ttfSize);
        alienBoldTypefacePtr = Typeface::createSystemTypefaceFor(BinaryData::AlienEncountersBold_ttf, BinaryData::AlienEncountersBold_ttfSize);
        alienSolidBoldTypefacePtr = Typeface::createSystemTypefaceFor(BinaryData::AlienEncountersSolidBold_ttf, BinaryData::AlienEncountersSolidBold_ttfSize);
        
    }
    
    /*** CUSTOM METHODS BELOW ***/
    
    float getMidpointFloat(float f1, float f2) {
        return fabsf(f1 - f2)/2.0f + fminf(f1, f2);
    }
    
    void setIntermediateShadowColour(Colour c1, Colour c2) {
        const float midRed = getMidpointFloat(c1.getFloatRed(), c2.getFloatRed());
        const float midGreen = getMidpointFloat(c1.getFloatGreen(), c2.getFloatGreen());
        const float midBlue = getMidpointFloat(c1.getFloatBlue(), c2.getFloatBlue());
        componentIntermediateShadowColour = Colour(midRed, midGreen, midBlue);
    }
    
    Colour getMidpointColour(Colour c1, Colour c2) {
        const float midRed = getMidpointFloat(c1.getFloatRed(), c2.getFloatRed());
        const float midGreen = getMidpointFloat(c1.getFloatGreen(), c2.getFloatGreen());
        const float midBlue = getMidpointFloat(c1.getFloatBlue(), c2.getFloatBlue());
        Colour c = Colour(midRed, midGreen, midBlue);
        return c;
    }
    
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
        return alienBoldTypefacePtr;
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
        
        const float innerRadius = 0.66f * radius;
        const float innerRx = centreX - innerRadius;
        const float innerRy = centreY - innerRadius;
        const float innerRw = innerRadius * 2.0f;
        
        // outter fill and gradient fill
        const float radiiDist = radius - innerRadius;
        const float shineSpotDistanceFromCentre = innerRadius + radiiDist/2.0f;
        const float sqrtTwoApprox = 1.414;
        const float shineSpotX = centreX - shineSpotDistanceFromCentre/sqrtTwoApprox;
        const float shineSpotY = centreY - shineSpotDistanceFromCentre/sqrtTwoApprox;
        ColourGradient shineGradient = ColourGradient(componentFillColour, shineSpotX, shineSpotY, componentShadowColour, shineSpotX + radiiDist, shineSpotY + radiiDist, true);
        g.setFillType(FillType::FillType(shineGradient));
        g.fillEllipse(rx, ry, rw, rw);
        g.setFillType(FillType(findColour(Slider::ColourIds::rotarySliderFillColourId)));
        
        // outline
        g.setColour(findColour(Slider::ColourIds::rotarySliderOutlineColourId));
        g.drawEllipse (rx, ry, rw, rw, 1.0f);
        
        // knob pointer line and outer arc level
        Path p;
        const float pointerLength = radius * 0.25f;
        const float pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        // pointer
        g.setColour (Colours::aqua);
        g.fillPath (p);
        
        float arcWidth = (radius+lightArcMargin)*2.0f;
        Path arcPath1;
        arcPath1.addArc(rx - lightArcMargin, ry - lightArcMargin, arcWidth, arcWidth, rotaryStartAngle, angle, true);
        g.setColour(secondarySectionColour.withAlpha(0.7f));
        g.strokePath(arcPath1, PathStrokeType(lightArcThickness));
        
        arcWidth = (radius+lightArcMargin+innerLightArcMargin)*2.0f;
        Path arcPath2;
        arcPath2.addArc(rx - lightArcMargin - innerLightArcMargin, ry - lightArcMargin - innerLightArcMargin, arcWidth, arcWidth, rotaryStartAngle, angle, true);
        g.setColour(highlightColour.withAlpha(0.7f));
        g.strokePath(arcPath2, PathStrokeType(lightArcThickness));
        
        arcWidth = (radius+lightArcMargin+innerLightArcMargin*2.0f)*2.0f;
        Path arcPath3;
        arcPath3.addArc(rx - lightArcMargin - innerLightArcMargin*2.0f, ry - lightArcMargin - innerLightArcMargin*2.0f, arcWidth, arcWidth, rotaryStartAngle, angle, true);
        g.setColour(stringColour.withAlpha(0.7f));
        g.strokePath(arcPath3, PathStrokeType(lightArcThickness));
        
        // inline
        if (slider.isMouseOverOrDragging()) {
            g.setColour(findColour(Slider::ColourIds::rotarySliderFillColourId).contrasting(componentFillContrast));
        } else {
            g.setColour(findColour(Slider::ColourIds::rotarySliderFillColourId));
        }
        g.fillEllipse(innerRx, innerRy, innerRw, innerRw);
        g.setColour(softOutlineColour);
        g.drawEllipse(innerRx, innerRy, innerRw, innerRw, smallLineWidth);
    }
    
    Font getTextButtonFont (TextButton &, int buttonHeight) override {
        const float fontHeight = jmin(20.0f, buttonHeight * 0.6f);
        Font f = Font(bodyTypefacePtr);
        f.setHeight(fontHeight);
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
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override {
        const auto cornerSize = 6.0f;
        const auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);
        const auto innerBounds = button.getLocalBounds().toFloat().reduced(mediumMarginSize, mediumMarginSize);
        const float centerX = bounds.getCentreX();
        const float centerY = bounds.getCentreY();
        Point<float> centerPoint = Point<float>(centerX, centerY);
        
        /* paths */
        Path topTrapezoid;
        topTrapezoid.addTriangle(innerBounds.getTopLeft(), bounds.getTopLeft(), Point<float>(innerBounds.getTopLeft().x, bounds.getTopLeft().y));
        topTrapezoid.addRectangle(innerBounds.getTopLeft().x, bounds.getTopLeft().y, innerBounds.getWidth(), mediumMarginSize);
        topTrapezoid.addTriangle(innerBounds.getTopRight(), bounds.getTopRight(), Point<float>(innerBounds.getTopRight().x, bounds.getTopRight().y));
        Path bottomTrapezoid;
        bottomTrapezoid.addTriangle(innerBounds.getBottomRight(), bounds.getBottomRight(), Point<float>(innerBounds.getBottomRight().x, bounds.getBottomRight().y));
        bottomTrapezoid.addTriangle(innerBounds.getBottomLeft(), bounds.getBottomLeft(), Point<float>(innerBounds.getBottomLeft().x, bounds.getBottomLeft().y));
        bottomTrapezoid.addRectangle(innerBounds.getBottomLeft().x, innerBounds.getBottomLeft().y, innerBounds.getWidth(), mediumMarginSize);
        Path leftTrapezoid;
        leftTrapezoid.addTriangle(innerBounds.getBottomLeft(), bounds.getBottomLeft(), Point<float>(bounds.getBottomLeft().x, innerBounds.getBottomLeft().y));
        leftTrapezoid.addTriangle(innerBounds.getTopLeft(), bounds.getTopLeft(), Point<float>(bounds.getTopLeft().x,innerBounds.getTopLeft().y));
        leftTrapezoid.addRectangle(bounds.getTopLeft().x, innerBounds.getTopLeft().y, mediumMarginSize, innerBounds.getHeight());
        
        
        auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
        .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);
        
        if (isButtonDown || isMouseOverButton) {
            baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.05f);
        }
        
        g.setColour (baseColour);
        
        if (button.isConnectedOnLeft() || button.isConnectedOnRight()) {
            Path path;
            path.addRoundedRectangle (bounds.getX(), bounds.getY(),
                                      bounds.getWidth(), bounds.getHeight(),
                                      cornerSize, cornerSize,
                                      ! button.isConnectedOnLeft(),
                                      ! button.isConnectedOnRight(),
                                      ! button.isConnectedOnLeft(),
                                      ! button.isConnectedOnRight());
//            path.addRectangle (bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
            
            g.fillPath (path);
            
            g.setColour (button.findColour (ComboBox::outlineColourId));
            g.strokePath (path, PathStrokeType (1.0f));
        } else {
            
            g.setColour(componentFillColour.brighter());
            g.fillRect(bounds);
            g.setColour(baseColour);
            
            g.setColour(componentIntermediateShadowColour);
            g.fillPath(topTrapezoid);
            g.fillPath(bottomTrapezoid);
            g.setColour(componentShadowColour.darker());
            g.fillPath(leftTrapezoid);
            
            g.setColour(baseColour);
            
            if (button.getToggleState()) {
                ColourGradient onGradient = ColourGradient(stringColour, centerPoint, componentFillColour,
                                                           Point<float>(innerBounds.getRight(),centerPoint.getY()), true);
                g.setFillType(FillType::FillType(onGradient));
                g.fillRect(innerBounds);
                g.setFillType(FillType(findColour(Slider::ColourIds::rotarySliderFillColourId)));
                g.setColour(baseColour);
            } else {
                g.fillRect(innerBounds);
            }
            
//            g.setColour(highlightColour.withAlpha(0.4f).brighter());
            g.setColour(softOutlineColour);
            g.drawRect (bounds, 1.0f);
            g.setColour(Colours::black);
            g.drawRect(innerBounds);
        }
    }
    
    void drawTickBox (Graphics& g, Component& component, float x, float y, float w, float h,
                                    const bool ticked, const bool isEnabled, const bool isMouseOverButton, const bool isButtonDown) override {
        
        ignoreUnused (isEnabled, isMouseOverButton, isButtonDown);
        
        const float tickBoundsWidth = w - 2.0f*tickBoxMarginSize;
        const float tickBoundsHeight = h - 2.0f*tickBoxMarginSize;
        
        const float centerX = x + tickBoundsWidth/2.0f;
        const float centerY = y + tickBoundsHeight/2.0f;
        
        Rectangle<float> tickBounds (x, y, tickBoundsWidth, tickBoundsHeight);
        Rectangle<float> marginBounds(x - tickBoxMarginSize, y - tickBoxMarginSize, w, h);
 
        const float outLeftX = marginBounds.getBottomLeft().x;
        const float outTopY = marginBounds.getTopLeft().y;
        const float outRightX = marginBounds.getRight();
        const float outBotY = marginBounds.getBottom();
        
        const float inLeftX = tickBounds.getBottomLeft().x;
        const float inTopY = tickBounds.getTopLeft().y;
        const float inRightX = tickBounds.getRight();
        const float inBotY = tickBounds.getBottom();
        
        Point<float> centerPoint = Point<float>(centerX, centerY);
        Path topTriangle;
        topTriangle.addTriangle(centerPoint, marginBounds.getTopLeft(), marginBounds.getTopRight());
        Path rightTriangle;
        rightTriangle.addTriangle(centerPoint, marginBounds.getTopRight(), marginBounds.getBottomRight());
        Path bottomTriangle;
        bottomTriangle.addTriangle(centerPoint, marginBounds.getBottomLeft(), marginBounds.getBottomRight());
        Path leftTriangle;
        leftTriangle.addTriangle(centerPoint, marginBounds.getBottomLeft(), marginBounds.getTopLeft());
        
        g.setColour(componentShadowColour);
        g.fillRect(marginBounds);
        
        g.setColour(componentFillColour.brighter());
        g.fillPath(rightTriangle);
        
        g.setColour(componentIntermediateShadowColour);
        g.fillPath(topTriangle);
        g.fillPath(bottomTriangle);
        g.setColour(componentShadowColour);
        g.fillPath(leftTriangle);
        
        if (isButtonDown || isMouseOverButton) {
            g.setColour(componentFillColour.contrasting(componentFillContrast));
        } else {
            g.setColour(componentFillColour);
        }
        g.fillRect(tickBounds);
        g.setColour (component.findColour (ToggleButton::tickDisabledColourId));
        
        /* when on, fill with radial gradient from orange to red. */
        if (ticked)
        {
//            ColourGradient onGradient = ColourGradient(stringColour, centerX, centerY, opaqueStringColour, x, y, true);
            ColourGradient onGradient = ColourGradient(stringColour, centerX, centerY, componentFillColour, x, y, true);
            g.setFillType(FillType::FillType(onGradient));
            g.fillRect(tickBounds);
            g.setFillType(FillType(findColour(Slider::ColourIds::rotarySliderFillColourId)));
        }
        Colour opaqueBlack = Colours::black.withAlpha(0.4f);
        g.setColour(Colours::black);
        g.drawRect (tickBounds);
        g.setColour(softOutlineColour);
        g.drawRect(marginBounds, 1.0f);
       
        g.setColour(opaqueBlack);
        g.drawLine(outLeftX, outTopY, inLeftX, inTopY, smallLineWidth);
        g.drawLine(outLeftX, outBotY, inLeftX, inBotY, smallLineWidth);
        g.setColour(softOutlineColour);
        g.drawLine(outRightX, outTopY, inRightX, inTopY, smallLineWidth);
        g.drawLine(outRightX, outBotY, inRightX, inBotY, smallLineWidth);
        
        
    }
    
    void drawToggleButton (Graphics& g, ToggleButton& button, bool isMouseOverButton, bool isButtonDown) override {
        const auto fontSize = jmin (15.0f, button.getHeight() * 0.75f);
        const auto tickWidth = fontSize * 1.1f + 2.0f*tickBoxMarginSize;
        
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
                
        g.drawFittedText (button.getButtonText(), textX, 0, button.getWidth() - textX - 2, button.getHeight(), Justification::centredLeft, 10);
    }
    
    void drawComboBox (Graphics& g, int width, int height, bool, int, int, int, int, ComboBox& box) override {
        const auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
        const Rectangle<int> boxBounds (0, 0, width, height);
        
        g.setColour (box.findColour (ComboBox::backgroundColourId));
        g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);
        
        g.setColour (box.findColour (ComboBox::outlineColourId));
//        g.drawRoundedRectangle (boxBounds.toFloat().reduced (0.5f, 0.5f), cornerSize, 1.0f);
        g.drawRect(boxBounds.toFloat().reduced (0.5f, 0.5f));
        
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