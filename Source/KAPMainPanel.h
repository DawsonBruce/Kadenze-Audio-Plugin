/*
  ==============================================================================

    KAPMainPanel.h
    Created: 12 Feb 2018 4:01:31pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

#include "KAPTopPanel.h"
#include "KAPGainPanel.h"
#include "KAPFxPanel.h"
#include "KAPCenterPanel.h"

class KAPMainPanel
:   public KAPPanelBase
{
public:
    KAPMainPanel(KadenzeAudioPluginAudioProcessor* processor);
    ~KAPMainPanel();
    
private:
    
    ScopedPointer<KAPTopPanel> mTopPanel;
    ScopedPointer<KAPGainPanel> mInputGainPanel;
    ScopedPointer<KAPGainPanel> mOutputputGainPanel;
    ScopedPointer<KAPCenterPanel> mCenterPanel;
};
