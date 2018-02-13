/*
 ==============================================================================
 
 KAPFxPanel.cpp
 Created: 12 Feb 2018 4:01:08pm
 Author:  Output Dev LapFx 2
 
 ==============================================================================
 */

#include "KAPFxPanel.h"

KAPFxPanel::KAPFxPanel(KadenzeAudioPluginAudioProcessor* processor)
:   KAPPanelBase(processor)
{
    setSize(FX_PANEL_WIDTH,
            FX_PANEL_HEIGHT);
}

KAPFxPanel::~KAPFxPanel()
{
    
}
