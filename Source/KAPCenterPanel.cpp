/*
  ==============================================================================

    KAPCenterPanel.cpp
    Created: 12 Feb 2018 4:02:43pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPCenterPanel.h"

KAPCenterPanel::KAPCenterPanel(KadenzeAudioPluginAudioProcessor* processor)
:   KAPPanelBase(processor)
{
    setSize(CENTER_PANEL_WIDTH,
            CENTER_PANEL_HEIGHT);
    
    mMenuBar = new KAPCenterPanelMenuBar(processor);
    mMenuBar->setTopLeftPosition(0, 0);
    addAndMakeVisible(mMenuBar);
    
    mDelayPanel = new KAPFxPanel(processor);
    mDelayPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    addAndMakeVisible(mDelayPanel);
    
    mChorusPanel = new KAPFxPanel(processor);
    mChorusPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    addChildComponent(mDelayPanel);
}

KAPCenterPanel::~KAPCenterPanel()
{
    
}
