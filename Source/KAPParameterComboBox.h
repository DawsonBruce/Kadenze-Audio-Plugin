/*
  ==============================================================================

    KAPParameterComboBox.h
    Created: 12 Feb 2018 5:44:06pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KAPParameterComboBox
:   public ComboBox
{
public:
    KAPParameterComboBox(AudioProcessorValueTreeState& stateToControl,
                         const String& parameterID);
    ~KAPParameterComboBox();
    
private:
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;
};
