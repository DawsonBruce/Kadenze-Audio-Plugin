/*
  ==============================================================================

    KAPPanelBase.cpp
    Created: 12 Feb 2018 4:11:46pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPPanelBase.h"

KAPPanelBase::KAPPanelBase(KadenzeAudioPluginAudioProcessor* processor)
:mProcessor(processor)
{
}

KAPPanelBase::~KAPPanelBase()
{
}

void KAPPanelBase::mouseEnter(const MouseEvent& event)
{
    repaint();
}

void KAPPanelBase::mouseExit(const MouseEvent& event)
{
    repaint();
}

void KAPPanelBase::paint(Graphics& g)
{
    // any paint code you have goes here.
    
    // hover logic
    if(isMouseOver(true)){
        
        const Colour hoverColour =
        Colour(Colours::black).withAlpha(0.4f);
        
        g.setColour(hoverColour);
        g.fillAll();
    }
}
