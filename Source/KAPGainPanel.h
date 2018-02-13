/*
  ==============================================================================

    KAPGainPanel.h
    Created: 12 Feb 2018 4:01:44pm
    Author:  Output Dev LapGain 2

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterSlider.h"

class KAPGainPanel
:   public KAPPanelBase
{
public:
    KAPGainPanel(KadenzeAudioPluginAudioProcessor* processor);
    ~KAPGainPanel();
    
    void setParameterID(int inParameterID);
    
private:
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    ScopedPointer<KAPParameterSlider> mGain;
};
