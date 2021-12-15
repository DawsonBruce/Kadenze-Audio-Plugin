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
:   public KAPPanelBase,
    public ComboBox::Listener
{
public:
    KAPCenterPanel(KadenzeAudioPluginAudioProcessor* processor);
    ~KAPCenterPanel();
    
private:
    
    /** internal */
    void showPanel(int inPanelID);
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
    std::unique_ptr<KAPCenterPanelMenuBar> mMenuBar;
    std::unique_ptr<KAPFxPanel> mDelayPanel;
    std::unique_ptr<KAPFxPanel> mChorusPanel;
};
