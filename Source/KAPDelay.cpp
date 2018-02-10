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
:   mTimeSmoothed(0),
    mFeedbackSmoothed(0),
    mFeedbackSample(0),
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
    
    mFeedbackSmoothed = mFeedbackSmoothed - kKAPParamSmoothCoeff_Generic*(mFeedbackSmoothed-inFeedback);
    
    for(int i = 0; i < inNumSamplesToRender; i++){
        
        mTimeSmoothed = mTimeSmoothed - kKAPParamSmoothCoeff_Fine*(mTimeSmoothed-inTime);
        const double delayTimeInSamples = (mSampleRate * mTimeSmoothed);
        const double sample = getInterpolatedSample(delayTimeInSamples);
        
        mBuffer[mDelayIndex] = inAudio[i] + (mFeedbackSample * mFeedbackSmoothed);
        
        kapassert_isnan(sample);
        
        mFeedbackSample = sample;
        
        outAudio[i] = sample;
        
        mDelayIndex = mDelayIndex + 1;
        
        if(mDelayIndex >= kMaxDelayBufferSize){
            mDelayIndex = mDelayIndex - kMaxDelayBufferSize;
        }
    }
}


double KAPDelay::getInterpolatedSample(float inDelayTimeInSamples)
{
    double readPosition = (double)mDelayIndex - inDelayTimeInSamples;
    
    if(readPosition < 0.0){
        readPosition = readPosition + (double)kMaxDelayBufferSize;
    }
    
    int index_y0 = (int)readPosition - 1;
    if(index_y0 < 0){
        index_y0 = index_y0 + kMaxDelayBufferSize;
    }
    
    int index_y1 = readPosition;
    if(index_y1 >= kMaxDelayBufferSize){
        index_y1 = index_y1 - kMaxDelayBufferSize;
    }
    
    int index_y2 = index_y1 + 1;
    if(index_y2 >= kMaxDelayBufferSize){
        index_y2 = index_y2 - kMaxDelayBufferSize;
    }
    
    int index_y3 = index_y2 + 1;
    if(index_y3 >= kMaxDelayBufferSize){
        index_y3 = index_y3 - kMaxDelayBufferSize;
    }
    
    const float sample_y0 = mBuffer[index_y0];
    const float sample_y1 = mBuffer[index_y1];
    const float sample_y2 = mBuffer[index_y2];
    const float sample_y3 = mBuffer[index_y3];
    const double mu = readPosition - (int)readPosition;
    
    double outSample = kap_cubic_interpolation(sample_y0, sample_y1, sample_y2, sample_y3, mu);
    
    return outSample;
}
