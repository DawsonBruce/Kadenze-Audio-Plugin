/*
 ==============================================================================
 
 KAPFxPanel.cpp
 Created: 12 Feb 2018 4:01:08pm
 Author:  Output Dev LapFx 2
 
 ==============================================================================
 */

#include "KAPFxPanel.h"

KAPFxPanel::KAPFxPanel(KadenzeAudioPluginAudioProcessor* processor)
:   KAPPanelBase(processor)
{
    setSize(FX_PANEL_WIDTH,
            FX_PANEL_HEIGHT);
    
    DBG("FX_PANEL_WIDTH: " << FX_PANEL_WIDTH);
    DBG("FX_PANEL_HEIGHT: " << FX_PANEL_HEIGHT);
}

KAPFxPanel::~KAPFxPanel()
{
    mSliders.clear();
}

void KAPFxPanel::visibilityChanged()
{
    /** update slider positions when set visible */
    for(int i = 0; i < mSliders.size(); i++){
        mSliders[i]->updateValue();
    }
}

void KAPFxPanel::paint(Graphics& g)
{
    String label;
    switch (mStyle) {
        case (kKAPFxPanelStyle_Delay):{
            label = "delay";
        }break;
            
        case (kKAPFxPanelStyle_Chorus):{
            label = "chorus";
        }break;
    }
    
    g.drawFittedText(label, 0, 0, getWidth(), 100, Justification::centred, 1);
}

void KAPFxPanel::setFxPanelStyle(KAPFxPanelStyle inStyle)
{
    mStyle=inStyle;
    
    mSliders.clear();
    
    const int size = 56;
    int x = 130;
    int y = getHeight()*0.5 - size*0.5;
    
    switch (mStyle) {
        case (kKAPFxPanelStyle_Delay):
        {
            KAPParameterSlider* time =
            new KAPParameterSlider(mProcessor->parameters[kParameter_DelayTime]);
            time->setBounds(x, y, size, size);
            mSliders.add(time);
            addAndMakeVisible(time);
            x = x + (size*2);
            
            KAPParameterSlider* feedback =
            new KAPParameterSlider(mProcessor->parameters[kParameter_DelayFeedback]);
            feedback->setBounds(x, y, size, size);
            mSliders.add(feedback);
            addAndMakeVisible(feedback);
            x = x + (size*2);
            
            KAPParameterSlider* wetdry =
            new KAPParameterSlider(mProcessor->parameters[kParameter_DelayWetDry]);
            wetdry->setBounds(x, y, size, size);
            mSliders.add(wetdry);
            addAndMakeVisible(wetdry);
            x = x + (size*2);
            
        } break;
            
        case (kKAPFxPanelStyle_Chorus):
        {
            KAPParameterSlider* rate =
            new KAPParameterSlider(mProcessor->parameters[kParameter_ModulationRate]);
            rate->setBounds(x, y, size, size);
            mSliders.add(rate);
            addAndMakeVisible(rate);
            x = x + (size*2);
            
            KAPParameterSlider* depth =
            new KAPParameterSlider(mProcessor->parameters[kParameter_ModulationDepth]);
            depth->setBounds(x, y, size, size);
            mSliders.add(depth);
            addAndMakeVisible(depth);
            x = x + (size*2);
            
            KAPParameterSlider* wetdry =
            new KAPParameterSlider(mProcessor->parameters[kParameter_DelayWetDry]);
            wetdry->setBounds(x, y, size, size);
            mSliders.add(wetdry);
            addAndMakeVisible(wetdry);
            x = x + (size*2);
        } break;
    }
}
