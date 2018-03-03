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
    
    KAPParameterSlider(AudioProcessorValueTreeState& stateToControl,
                       const String& parameterID);
    ~KAPParameterSlider();
    
private:
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KAPParameterSlider)
};
