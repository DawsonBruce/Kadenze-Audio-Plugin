/*
  ==============================================================================

    KAPGain.h
    Created: 12 Feb 2018 3:12:43pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "KAPAudioFunctions.h"

class KAPGain
{
public:
    
    KAPGain();
    ~KAPGain();
    
    void process(float* inAudio,
                 float inGain,
                 float* outAudio,
                 int inNumSamplesToRender);
    
    float getMeterLevel();
    
private:
    
    float mGainSmoothed;
    float mOutputSmoothed;
};
