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
    addAndMakeVisible(mDelayPanel);
    
    mChorusPanel = new KAPFxPanel(processor);
    mChorusPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    mChorusPanel->setFxPanelStyle(kKAPFxPanelStyle_Chorus);
    addChildComponent(mChorusPanel);
}

KAPCenterPanel::~KAPCenterPanel()
{
    
}

void KAPCenterPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if(comboBoxThatHasChanged->getSelectedItemIndex() == 0 /** delay */){
        mDelayPanel->setVisible(true);
        mChorusPanel->setVisible(false);
    }
    
    else if(comboBoxThatHasChanged->getSelectedItemIndex() == 1 /** chorus */){
        mDelayPanel->setVisible(false);
        mChorusPanel->setVisible(true);
    }
}
