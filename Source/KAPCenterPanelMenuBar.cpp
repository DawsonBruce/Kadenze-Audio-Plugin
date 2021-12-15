/*
  ==============================================================================

    KAPCenterPanelMenuBar.cpp
    Created: 12 Feb 2018 4:03:12pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPCenterPanelMenuBar.h"

KAPCenterPanelMenuBar::KAPCenterPanelMenuBar(KadenzeAudioPluginAudioProcessor* processor)
:   KAPPanelBase(processor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH,
            CENTER_PANEL_MENU_BAR_HEIGHT);
    
    const int comboBox_w = 100;
    const int comboBox_h = CENTER_PANEL_MENU_BAR_HEIGHT;
    
    const StringArray fxTypes = StringArray{
        "delay",
        "chorus"
    };

    int value = *processor->parameters.getRawParameterValue(KAPParameterID[kParameter_DelayType]);
    
    mFxType = std::make_unique<KAPParameterComboBox>(mProcessor->parameters,
                                       KAPParameterID[kParameter_DelayType]);
    mFxType->addItemList(fxTypes, 1);
    mFxType->setSelectedItemIndex(value, dontSendNotification);
    mFxType->setBounds(CENTER_PANEL_MENU_BAR_WIDTH - comboBox_w, 0, comboBox_w, comboBox_h);
    addAndMakeVisible(mFxType.get());
}

KAPCenterPanelMenuBar::~KAPCenterPanelMenuBar()
{
    
}

void KAPCenterPanelMenuBar::addFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
    mFxType->addListener(inListener);
}

void KAPCenterPanelMenuBar::removeFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
    mFxType->removeListener(inListener);
}
