/*
  ==============================================================================

    KAPCenterPanelMenuBar.h
    Created: 12 Feb 2018 4:03:12pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

class KAPCenterPanelMenuBar
:   public KAPPanelBase
{
public:
    KAPCenterPanelMenuBar(KadenzeAudioPluginAudioProcessor* processor);
    ~KAPCenterPanelMenuBar();
    
    void addFxTypeComboBoxListener(ComboBox::Listener* inListener);
    
private:
    
    ScopedPointer<ComboBox> mFxType;
};
