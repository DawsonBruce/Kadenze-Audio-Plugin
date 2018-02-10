/*
  ==============================================================================

    KAPParameterSlider.cpp
    Created: 9 Feb 2018 3:08:09pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPParameterSlider.h"

KAPParameterSlider::KAPParameterSlider(AudioProcessorParameter* p)
:   juce::Slider(p->getName(256)),
    mParameter(p)
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
    setRange(0.f, 1.f, 0.001f);
    setValue(mParameter->getValue(), dontSendNotification);
    
}

KAPParameterSlider::~KAPParameterSlider()
{
    
}

void KAPParameterSlider::mouseDoubleClick (const MouseEvent& e)
{
    /** on double click, update slider to default value and notify host. */
    setValue(mParameter->getDefaultValue(), sendNotification);
}

void KAPParameterSlider::valueChanged()
{
    mParameter->setValueNotifyingHost((float)Slider::getValue());
}

void KAPParameterSlider::startedDragging()
{
    mParameter->beginChangeGesture();
}

void KAPParameterSlider::stoppedDragging()
{
    mParameter->endChangeGesture();
}
