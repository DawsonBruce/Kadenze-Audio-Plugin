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

void KAPGainPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);
    
//    paintComponentLabel(g, mGain);
}

void KAPGainPanel::setParameterID(int inParameterID)
{
//    const int slider_size = 54;
//    mGain = new KAPParameterSlider(mProcessor->parameters[inParameterID]);
//    mGain->setBounds(getWidth()*0.5 - slider_size*0.5, slider_size*0.5, slider_size, slider_size);
//    addAndMakeVisible(mGain);
    
    const int vu_size = 36;
    mVuMeter = new KAPVuMeter(mProcessor);
    mVuMeter->setParameterID(inParameterID);
    mVuMeter->setBounds(getWidth()*0.5 - vu_size*0.5, vu_size*3, vu_size, vu_size*3);
    addAndMakeVisible(mVuMeter);
}

void KAPGainPanel::changeListenerCallback (ChangeBroadcaster* source)
{
    //mGain->updateValue();
}
