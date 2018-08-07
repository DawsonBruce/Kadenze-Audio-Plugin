/*
  ==============================================================================

    KAPLfo.cpp
    Created: 12 Feb 2018 12:11:45pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPLfo.h"

KAPLfo::KAPLfo()
{
    reset();
}

KAPLfo::~KAPLfo()
{
}

void KAPLfo::setSampleRate(double inSampleRate)
{
    mSampleRate=inSampleRate;
    reset();
}

void KAPLfo::reset()
{
    mPhase = 0.0;
    zeromem(mBuffer, kMaxChannelBufferSize * sizeof(float));
}

void KAPLfo::process(float inRate,
                     float inDepth,
                     int inNumSamplesToRender)
{
    
    const float rate = jmap(inRate, 0.f, 1.f, 0.01f, 10.f);
    
    /** calculate phase */
    for(int i = 0; i < inNumSamplesToRender; i++){
        
        mPhase = mPhase + (rate / mSampleRate);
        
        if(mPhase > 1.f){
            mPhase = mPhase - 1.f;
        }
        
        const float lfoPosition = sinf(mPhase * kPI2) * inDepth;
        mBuffer[i] = lfoPosition;
    }
}
