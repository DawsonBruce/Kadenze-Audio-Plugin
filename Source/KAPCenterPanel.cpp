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
    
    mMenuBar = std::make_unique<KAPCenterPanelMenuBar>(processor);
    mMenuBar->setTopLeftPosition(0, 0);
    mMenuBar->addFxTypeComboBoxListener(this);
    addAndMakeVisible(mMenuBar.get());
    
    mDelayPanel = std::make_unique<KAPFxPanel>(processor);
    mDelayPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    mDelayPanel->setFxPanelStyle(kKAPFxPanelStyle_Delay);
    addChildComponent(mDelayPanel.get());
    
    mChorusPanel = std::make_unique<KAPFxPanel>(processor);
    mChorusPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    mChorusPanel->setFxPanelStyle(kKAPFxPanelStyle_Chorus);
    addChildComponent(mChorusPanel.get());
    
    AudioProcessorValueTreeState& tree = mProcessor->parameters;
    
    const float panelToShow =
    *tree.getRawParameterValue(KAPParameterID[kParameter_DelayType]);
    
    showPanel((int)panelToShow);
}

KAPCenterPanel::~KAPCenterPanel()
{
    mMenuBar->removeFxTypeComboBoxListener(this);
}

void KAPCenterPanel::showPanel(int inPanelID)
{
    switch(inPanelID){
        case(kKAPFxPanelStyle_Delay):{
            
            mDelayPanel->setVisible(true);
            mChorusPanel->setVisible(false);
            
        }break;
            
        case(kKAPFxPanelStyle_Chorus):{
            
            mDelayPanel->setVisible(false);
            mChorusPanel->setVisible(true);
            
        }break;
    }
}

void KAPCenterPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    showPanel(comboBoxThatHasChanged->getSelectedItemIndex());
}
