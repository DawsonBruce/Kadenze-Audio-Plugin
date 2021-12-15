/*
  ==============================================================================

    KAPGain.cpp
    Created: 12 Feb 2018 3:12:43pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPGain.h"

KAPGain::KAPGain()
{
    
}

KAPGain::~KAPGain()
{
    
}

void KAPGain::process(float* inAudio,
                      float inGain,
                      float* outAudio,
                      int inNumSamplesToRender)
{
    float gainMapped = jmap(inGain, 0.f, 1.f, -24.f, 24.f);
    gainMapped = Decibels::decibelsToGain(gainMapped, -24.f);
    
    mGainSmoothed = mGainSmoothed - kKAPParamSmoothCoeff_Generic*(mGainSmoothed-gainMapped);
    
    for(int i = 0; i < inNumSamplesToRender; i++){
        outAudio[i] = inAudio[i] * mGainSmoothed;
    }
    
    float absOutput = fabs(outAudio[0]);
    mOutputSmoothed = kKAPMeterSmoothingCoeff*(mOutputSmoothed - absOutput) + absOutput;
}

float KAPGain::getMeterLevel()
{
    float normalizedOutput = dBToNormalizedGain(mOutputSmoothed);
    return normalizedOutput;
}
