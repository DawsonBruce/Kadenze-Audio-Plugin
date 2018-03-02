/*
  ==============================================================================

    KAPLookAndFeel.h
    Created: 14 Feb 2018 4:14:25pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "KAPInterfaceDefines.h"

class KAPLookAndFeel
:   public LookAndFeel_V4
{
public:
    
    KAPLookAndFeel(){
        
        SliderImage = ImageCache::getFromMemory(BinaryData::kadenze_knob_png,
                                                BinaryData::kadenze_knob_pngSize);
        
        /** comboBox colours */
        setColour(ComboBox::backgroundColourId, KAPColour_3);
        setColour(ComboBox::outlineColourId, KAPColour_2);
        setColour(ComboBox::arrowColourId, KAPColour_1);
        setColour(ComboBox::textColourId, KAPColour_1);
        
        /** button colours */
        setColour(TextButton::buttonColourId, KAPColour_1);
        setColour(TextButton::textColourOnId, KAPColour_1);
        setColour(TextButton::textColourOffId, KAPColour_1);
    }
    
    /** BUTTONS */
    Font getTextButtonFont (TextButton&, int buttonHeight) override
    {
        return font_1;
    }
    
    void drawButtonBackground (Graphics& g,
                               Button& button,
                               const Colour& backgroundColour,
                               bool isMouseOverButton,
                               bool isButtonDown) override
    {
        Colour fillColour;
        
        if(isButtonDown){
            fillColour = KAPColour_5;
        } else if(isMouseOverButton){
            fillColour = KAPColour_4;
        } else {
            fillColour = KAPColour_3;
        }
        
        const float cornerSize = 6.0f;
        const Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);
        
        g.setColour (fillColour);
        g.fillRoundedRectangle (bounds.reduced(1), cornerSize);
    }
    
    /** COMBOBOX */
    Font getLabelFont (Label& label) override
    {
        return font_1;
    }
    
    void drawPopupMenuBackground(juce::Graphics &g, int width, int height) override
    {
        g.setColour(KAPColour_4);
        g.fillRect(0,0,width,height);
    }
    
    void drawPopupMenuItem (Graphics& g, const juce::Rectangle<int>& area,
                            const bool isSeparator, const bool isActive,
                            const bool isHighlighted, const bool isTicked,
                            const bool hasSubMenu, const String& text,
                            const String& shortcutKeyText,
                            const Drawable* icon, const Colour* const textColourToUse) override
    {
        juce::Rectangle<int> r (area);
        
        Colour fillColour = isHighlighted ? KAPColour_6 : KAPColour_4;
        g.setColour(fillColour);
        g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight()-1);
        
        Colour textColour = isTicked ? KAPColour_7 : KAPColour_1;
        g.setColour(textColour);
        g.setFont (font_1);
        r.setLeft(10);
        r.setY(1);
        g.drawFittedText (text, r, Justification::centredLeft, 1);
    }
    
    void drawComboBox (Graphics& g, int width, int height, bool,
                       int, int, int, int, ComboBox& box) override
    {
        const float cornerSize = 3.f;
        const Rectangle<int> boxBounds (0, 0, width, height);
        
        g.setColour (KAPColour_3);
        g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);
        
        Rectangle<int> arrowZone (width - 30, 0, 20, height);
        Path path;
        path.startNewSubPath (arrowZone.getX() + 3.0f, arrowZone.getCentreY() - 2.0f);
        path.lineTo (static_cast<float> (arrowZone.getCentreX()), arrowZone.getCentreY() + 3.0f);
        path.lineTo (arrowZone.getRight() - 3.0f, arrowZone.getCentreY() - 2.0f);
        
        g.setColour (box.findColour (ComboBox::arrowColourId).withAlpha ((box.isEnabled() ? 0.9f : 0.2f)));
        g.strokePath (path, PathStrokeType (2.0f));
    }
    
    /** SLIDER */
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        const int numFrames = SliderImage.getHeight() / SliderImage.getWidth();
        const int frameIdx = (int)ceil(sliderPos * (numFrames-1));
        
        const float radius = jmin(width*0.5, height * 0.5);
        const float centerX = x+width * 0.5;
        const float centerY = y+height * 0.5;
        const float rx = centerX - radius;
        const float ry = centerY - radius;
        
        g.drawImage(SliderImage,
                    rx,
                    ry,
                    2*radius,
                    2*radius,
                    0,
                    frameIdx*SliderImage.getWidth(),
                    SliderImage.getWidth(),
                    SliderImage.getWidth());
    }
private:
    
    Image SliderImage;
};
