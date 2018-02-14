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
    KAPPresetManager* presetManager = mProcessor->getPresetManager();
    presetManager->addChangeListener(this);
    
    mProcessor->addChangeListener(this);
}

KAPPanelBase::~KAPPanelBase()
{
    KAPPresetManager* presetManager = mProcessor->getPresetManager();
    presetManager->removeChangeListener(this);
    
    mProcessor->removeChangeListener(this);
}

void KAPPanelBase::paint(Graphics& g)
{
    g.setColour(Colour(75,75,75));
    g.drawRect(0, 0, getWidth(), getHeight());
}
