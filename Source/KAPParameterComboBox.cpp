/*
  ==============================================================================

    KAPParameterComboBox.cpp
    Created: 12 Feb 2018 5:44:06pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPParameterComboBox.h"

KAPParameterComboBox::KAPParameterComboBox(AudioProcessorValueTreeState& stateToControl,
                                           const String& parameterID)
:   ComboBox(parameterID)
{
    mAttachment =
    new AudioProcessorValueTreeState::ComboBoxAttachment(stateToControl, parameterID, *this);
}

KAPParameterComboBox::~KAPParameterComboBox()
{
}

