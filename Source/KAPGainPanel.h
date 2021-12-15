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
#include "KAPVuMeter.h"

class KAPGainPanel
:   public KAPPanelBase
{
public:
    KAPGainPanel(KadenzeAudioPluginAudioProcessor* processor);
    ~KAPGainPanel();
    
    /** component override */
    void paint(Graphics& g) override;
    
    void setParameterID(int inParameterID);
    
private:
    
    std::unique_ptr<KAPParameterSlider> mGain;
    std::unique_ptr<KAPVuMeter> mVuMeter;
};
