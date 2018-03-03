/*
  ==============================================================================

    KAPParameterSlider.cpp
    Created: 9 Feb 2018 3:08:09pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPParameterSlider.h"

KAPParameterSlider::KAPParameterSlider(AudioProcessorValueTreeState& stateToControl,
                                       const String& parameterID)
:   juce::Slider(parameterID)
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
    setRange(0.f, 1.f, 0.001f);
    
    mAttachment =
    new AudioProcessorValueTreeState::SliderAttachment(stateToControl, parameterID, *this);
}

KAPParameterSlider::~KAPParameterSlider()
{
}

