/*
  ==============================================================================

    KAPDelay.cpp
    Created: 9 Feb 2018 2:47:01pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPDelay.h"
#include "KAPAudioFunctions.h"
#include "KAPHelperFunctions.h"

// add some smoothing

KAPDelay::KAPDelay()
:   mFeedbackSample(0),
    mDelayIndex(0)
{
}

KAPDelay::~KAPDelay()
{
}

void KAPDelay::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
    reset();
}

void KAPDelay::reset()
{
    memset(mBuffer, 0, sizeof(double)*kMaxDelayBufferSize);
}

void KAPDelay::process(float* inAudio, float inTime, float inFeedback,
                       float* outAudio, int inNumSamplesToRender)
{
    const double delayTimeInSamples = (mSampleRate * inTime);
    
    for(int i = 0; i < inNumSamplesToRender; i++){
        
        const double readPosition = getReadPosition(delayTimeInSamples);
        const double sample = getInterpolatedSample(readPosition);
        
        mBuffer[mDelayIndex] = inAudio[i] + (mFeedbackSample * inFeedback);
        
        kapassert_isnan(sample);
        
        mFeedbackSample = sample;
        
        outAudio[i] = sample;
        
        mDelayIndex = mDelayIndex + 1;
        if(mDelayIndex >= kMaxDelayBufferSize){
            mDelayIndex = mDelayIndex - kMaxDelayBufferSize;
        }
    }
}

double KAPDelay::getReadPosition(float inDelayTime)
{
    double readPosition = (double)mDelayIndex - inDelayTime;
    
    if(readPosition < 0.0){
        readPosition = readPosition + (double)kMaxDelayBufferSize;
    }
    
    
    return readPosition;
}

double KAPDelay::getInterpolatedSample(double readPosition)
{
    int index_y0 = (int)readPosition - 1;
    if(index_y0 < 0){
        index_y0 += mDelayIndex;
    }
    
    int index_y1 = readPosition;
    if(index_y1 >= mDelayIndex){
        index_y1 -= mDelayIndex;
    }
    
    int index_y2 = index_y1 + 1;
    if(index_y2 >= mDelayIndex){
        index_y2 -= mDelayIndex;
    }
    
    int index_y3 = index_y2 + 1;
    if(index_y3 >= mDelayIndex){
        index_y3 -= mDelayIndex;
    }
    
    float sample_y0 = mBuffer[index_y0];
    float sample_y1 = mBuffer[index_y1];
    float sample_y2 = mBuffer[index_y2];
    float sample_y3 = mBuffer[index_y3];
    
    // get interpolation position
    double mu = readPosition - (int)readPosition;
    
    double outSample = kap_cubic_interpolation(sample_y0, sample_y1, sample_y2, sample_y3, mu);
    
    return outSample;
}
