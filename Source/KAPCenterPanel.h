/*
  ==============================================================================

    KAPCenterPanel.h
    Created: 12 Feb 2018 4:02:43pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

#include "KAPCenterPanelMenuBar.h"
#include "KAPFxPanel.h"

class KAPCenterPanel
:   public KAPPanelBase
{
public:
    KAPCenterPanel(KadenzeAudioPluginAudioProcessor* processor);
    ~KAPCenterPanel();
    
private:
    
    ScopedPointer<KAPCenterPanelMenuBar> mMenuBar;
    
    ScopedPointer<KAPFxPanel> mDelayPanel;
    
    ScopedPointer<KAPFxPanel> mChorusPanel;
};
