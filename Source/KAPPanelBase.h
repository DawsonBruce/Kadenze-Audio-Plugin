/*
 ==============================================================================
 
 KAPPanelBase.h
 Created: 12 Feb 2018 4:01:31pm
 Author:  Output Dev Laptop 2
 
 ==============================================================================
 */

#pragma once

#include "PluginProcessor.h"
#include "KAPInterfaceDefines.h"
#include "JuceHeader.h"

class KAPPanelBase
:   public Component
{
public:
    KAPPanelBase(KadenzeAudioPluginAudioProcessor* processor);
    ~KAPPanelBase();
    
    void paint(Graphics& g) override;
    
protected:
    
    KadenzeAudioPluginAudioProcessor* mProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPPanelBase);
};