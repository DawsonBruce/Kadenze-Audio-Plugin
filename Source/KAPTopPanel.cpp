/*
  ==============================================================================

    KAPTopPanel.cpp
    Created: 12 Feb 2018 4:01:08pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPTopPanel.h"

KAPTopPanel::KAPTopPanel(KadenzeAudioPluginAudioProcessor* processor)
:   KAPPanelBase(processor)
{
    setSize(TOP_PANEL_WIDTH,
            TOP_PANEL_HEIGHT);
}

KAPTopPanel::~KAPTopPanel()
{
    
}
