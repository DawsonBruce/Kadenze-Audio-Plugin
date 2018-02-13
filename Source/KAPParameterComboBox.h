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
:   public ComboBox,
    public ComboBox::Listener
{
public:
    KAPParameterComboBox(AudioProcessorParameter* p);
    ~KAPParameterComboBox();
    
    /** function for updating slider
     position based on parameter value.
     */
    void updateValue();
    
private:
    
    /** listener override */
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
    AudioProcessorParameter* mParameter;
};
