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
    memset(mBuffer, 0, sizeof(double)*kMaxChannelBufferSize);
}

void KAPDelay::process(float* inAudio, float inTime, float inFeedback, float inWetDry, float inType,
                       float* inModulationBuffer, float* outAudio, int inNumSamplesToRender)
{
    const float wet = inWetDry;
    const float dry = 1.f - wet;
    const float feedbackMapped = (inType==kKAPDelayType_Delay) ? jmap(inFeedback, 0.f, 1.f, 0.f, 0.95f) : 0.f;
        
    for(int i = 0; i < inNumSamplesToRender; i++){
    
       if((int)inType == kKAPDelayType_Chorus){
            const double delayTimeModulation = (0.003 + 0.002 * inModulationBuffer[i]);
            mTimeSmoothed = mTimeSmoothed - kKAPParamSmoothCoeff_Fine*(mTimeSmoothed-delayTimeModulation);
        } else {
           mTimeSmoothed = mTimeSmoothed - kKAPParamSmoothCoeff_Fine*(mTimeSmoothed-inTime);
        }
        
        const double delayTimeInSamples = (mSampleRate * mTimeSmoothed);
        const double sample = getInterpolatedSample(delayTimeInSamples);
        
        mBuffer[mDelayIndex] = inAudio[i] + (mFeedbackSample * feedbackMapped);
        
        kapassert_isnan(sample);
        
        mFeedbackSample = sample;
        
        outAudio[i] = (inAudio[i]*dry + sample*wet);
        
        mDelayIndex = mDelayIndex + 1;
        
        if(mDelayIndex >= kMaxChannelBufferSize){
            mDelayIndex = mDelayIndex - kMaxChannelBufferSize;
        }
    }
}


double KAPDelay::getInterpolatedSample(float inDelayTimeInSamples)
{
    double readPosition = (double)mDelayIndex - inDelayTimeInSamples;
    
    if(readPosition < 0.f){
        readPosition = readPosition + (double)kMaxChannelBufferSize;
    }
    
    int index_y0 = (int)readPosition - 1;
    if(index_y0 < 0){
        index_y0 = index_y0 + kMaxChannelBufferSize;
    }
    
    int index_y1 = readPosition;
    if(index_y1 >= kMaxChannelBufferSize){
        index_y1 = index_y1 - kMaxChannelBufferSize;
    }
    
    const float sample_y0 = mBuffer[index_y0];
    const float sample_y1 = mBuffer[index_y1];
    const double mu = readPosition - (int)readPosition;
        
    float outSample = kap_linear_interp(sample_y0, sample_y1, mu);
    
    return outSample;
}
