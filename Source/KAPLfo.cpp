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
    /** sine */
    mPhase = 0.0;
    mPreviousRate = 0.0;
    mDelta = 1.0 / mSampleRate;
}

void KAPLfo::process(float inRate,
                     float inDepth,
                     float* outAudio,
                     int inNumSamplesToRender)
{
    
    float rate = jmap(inRate, 0.f, 1.f, 0.01f, 10.f);
    rate = rate * mDelta;
    
    if(mPreviousRate != rate){
        mPhase = mPhase + (mPreviousRate / rate) * mPhase - mPhase;
        mPreviousRate = rate;
    }
    
    /** calculate phase */
    for(int i = 0; i < inNumSamplesToRender; i++){
        mPhase = mPhase + kPI2 * rate;
        
        if(mPhase > kPI2){
            mPhase = mPhase - kPI2;
        }
        
        if(mPhase < 0.f){
            mPhase = 0.f;
        }
        
        float lfoPosition = sinf(mPhase) * inDepth;
        outAudio[i] = lfoPosition;
    }
}
