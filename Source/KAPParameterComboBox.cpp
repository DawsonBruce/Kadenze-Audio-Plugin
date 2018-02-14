/*
  ==============================================================================

    KAPParameterComboBox.cpp
    Created: 12 Feb 2018 5:44:06pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPParameterComboBox.h"

KAPParameterComboBox::KAPParameterComboBox(AudioProcessorParameter* p)
:   mParameter(p)
{
    updateValue();
    addListener(this);
}

KAPParameterComboBox::~KAPParameterComboBox()
{
    
}

void KAPParameterComboBox::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    mParameter->setValueNotifyingHost((float)ComboBox::getSelectedItemIndex());
}

void KAPParameterComboBox::updateValue()
{
    setSelectedItemIndex((int)mParameter->getValue(), dontSendNotification);
}