/*
  ==============================================================================

    KAPParameterControl.h
    Created: 9 Feb 2018 9:40:41pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

/** Our Kadenze Audio Plugin parameter base class. Here we can interact with JUCE's parameter management system. */

class KAPParameterControl
{
public:
    KAPParameterControl(AudioProcessorParameter* inParameter);
    ~KAPParameterControl();
    
    void setValueUnmapped(float inUnmappedValue);
    
    float getValueUnmapped();
    
    void setValueMapped(float inMappedValue);
    
    float getValueMapped();
    
    float getDefaultValueUnmapped();
    
    float getDefaultValueMapped();
    
    void beginChangeGesture();
    
    void endChangeGesture();
    
private:
    
    AudioProcessorParameter* mParameter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KAPParameterControl)
};
