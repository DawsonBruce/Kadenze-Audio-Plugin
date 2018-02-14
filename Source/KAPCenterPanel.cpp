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
    mMenuBar->addFxTypeComboBoxListener(this);
    addAndMakeVisible(mMenuBar);
    
    mDelayPanel = new KAPFxPanel(processor);
    mDelayPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    mDelayPanel->setFxPanelStyle(kKAPFxPanelStyle_Delay);
    addChildComponent(mDelayPanel);
    
    mChorusPanel = new KAPFxPanel(processor);
    mChorusPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    mChorusPanel->setFxPanelStyle(kKAPFxPanelStyle_Chorus);
    addChildComponent(mChorusPanel);
    
    showPanel(mProcessor->getLastOpenedPanel());
}

KAPCenterPanel::~KAPCenterPanel()
{
    
}

void KAPCenterPanel::showPanel(int inPanelID)
{
    switch(inPanelID){
        case(kKAPPanelIDs_FxDelay):{
            
            mDelayPanel->setVisible(true);
            mChorusPanel->setVisible(false);
            
        }break;
            
        case(kKAPPanelIDs_FxChorus):{
            
            mDelayPanel->setVisible(false);
            mChorusPanel->setVisible(true);
            
        }break;
    }
    
    mProcessor->setLastOpenedPanel(inPanelID);
}

void KAPCenterPanel::changeListenerCallback (ChangeBroadcaster* source)
{
    const int panelToShow = mProcessor->getParameter(kParameter_DelayType);
    showPanel(panelToShow);
}

void KAPCenterPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    const int panel = comboBoxThatHasChanged->getSelectedItemIndex();
    showPanel(panel);
}
