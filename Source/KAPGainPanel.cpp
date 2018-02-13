/*
 ==============================================================================
 
 KAPGainPanel.cpp
 Created: 12 Feb 2018 4:01:08pm
 Author:  Output Dev LapGain 2
 
 ==============================================================================
 */

#include "KAPGainPanel.h"

KAPGainPanel::KAPGainPanel(KadenzeAudioPluginAudioProcessor* processor)
:   KAPPanelBase(processor)
{
    setSize(GAIN_PANEL_WIDTH,
            GAIN_PANEL_HEIGHT);
}

KAPGainPanel::~KAPGainPanel()
{
}

void KAPGainPanel::setParameterID(int inParameterID)
{
    const int size = 54;
    mGain = new KAPParameterSlider(mProcessor->parameters[inParameterID]);
    mGain->setBounds(getWidth()*0.5 - size*0.5, size*0.5, size, size);
    addAndMakeVisible(mGain);
}

void KAPGainPanel::changeListenerCallback (ChangeBroadcaster* source)
{
    mGain->updateValue();
}
