/*
 ==============================================================================
 
 KAPGainPanel.cpp
 Created: 12 Feb 2018 4:01:08pm
 Author:  Output Dev LapGain 2
 
 ==============================================================================
 */

#include "KAPGainPanel.h"

KAPGainPanel::KAPGainPanel(KadenzeAudioPluginAudioProcessor* processor)
:   KAPPanelBase(processor)
{
    setSize(GAIN_PANEL_WIDTH,
            GAIN_PANEL_HEIGHT);
}

KAPGainPanel::~KAPGainPanel()
{
    
}
