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
    /** sine */
    mPhase = 0.0;
    mPhaseShift = 0.0;
    mPreviousRate = 0.0;
    
    mTableSize = (int)kMaxChannelBufferSize * 0.5;
    mInvTableSize = 1.0f / mTableSize;
    mRange = 4.0f * kPI;
    mInvRange = 1.0f / mRange;
    mDelta = 1.0 / mSampleRate;
    mTableWidth = (float)mTableSize / mRange;
    
    for(int i = 0; i < mTableSize; i++){
        mSinTable[i] = sinf(mRange * i * mInvTableSize);
        mCosTable[i] = cosf(mRange * i * mInvTableSize);
    }
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
        
        if(mPhase < -1.f){
            mPhase = 1.f;
        }
        
//        DBG("mPhase: " << mPhase);
    }
    
    /** calculate phase */
    for(int i = 0; i < inNumSamplesToRender; i++){
        
        float address = mPhase * mTableWidth;
        int index = address;
        float delta = address - index;
        
        outAudio[i] = (mSinTable[index] + delta * (mSinTable[index+1] - mSinTable[index])) * inDepth;
    }
}
