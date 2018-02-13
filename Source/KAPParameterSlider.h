/*
  ==============================================================================

    KAPParameterSlider.h
    Created: 9 Feb 2018 3:08:09pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KAPParameterSlider
:   public Slider
{
public:
    
    KAPParameterSlider(AudioProcessorParameter* p);
    ~KAPParameterSlider();
    
    /** component override */
    void mouseDoubleClick (const MouseEvent&) override;
    /** slider override */
    void valueChanged() override;
    /** slider override */
    void startedDragging() override;
    /** slider override */
    void stoppedDragging() override;
    
    /** function for updating slider 
        position based on parameter value. 
     */
    void updateValue();
    
private:
    
    AudioProcessorParameter* mParameter;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KAPParameterSlider)
};
