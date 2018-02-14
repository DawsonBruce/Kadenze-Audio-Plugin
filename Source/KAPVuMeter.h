/*
  ==============================================================================

    KAPVuMeter.h
    Created: 12 Feb 2018 4:43:57pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class KAPVuMeter
:   public Component,
    public Timer
{
public:
    
    KAPVuMeter(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPVuMeter();
    
    /** component override */
    void paint(Graphics& g) override;
    /** timer override */
    void timerCallback() override;
    
    void setParameterID(int inParameterID);
    
private:
    
    int mParameterID;
    
    float mCh0Level, mCh1Level;
    
    KadenzeAudioPluginAudioProcessor* mProcessor;
};
