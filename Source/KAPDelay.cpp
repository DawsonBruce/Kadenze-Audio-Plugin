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

void KAPDelay::process(float* inAudio, float inTime, float inFeedback, float inWetDry,
                       float* inModulationBuffer, float* outAudio, int inNumSamplesToRender)
{
    const float time = kap_time_signature(inTime);
    const float wet = inWetDry;
    const float dry = 1.f - wet;
    const float feedbackMapped = jmap(inFeedback, 0.f, 1.f, 0.f, 0.95f);
        
    for(int i = 0; i < inNumSamplesToRender; i++){
        
        const double delayTimeModulation = time + (0.003 + 0.002 * inModulationBuffer[i]);

        mTimeSmoothed = mTimeSmoothed - kKAPParamSmoothCoeff_Fine*(mTimeSmoothed-delayTimeModulation);
        
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
    
    int index_y2 = index_y1 + 1;
    if(index_y2 >= kMaxChannelBufferSize){
        index_y2 = index_y2 - kMaxChannelBufferSize;
    }
    
    int index_y3 = index_y2 + 1;
    if(index_y3 >= kMaxChannelBufferSize){
        index_y3 = index_y3 - kMaxChannelBufferSize;
    }
    
    const float sample_y0 = mBuffer[index_y0];
    const float sample_y1 = mBuffer[index_y1];
    const float sample_y2 = mBuffer[index_y2];
    const float sample_y3 = mBuffer[index_y3];
    const double mu = readPosition - (int)readPosition;
    
    double outSample = kap_cubic_interpolation(sample_y0, sample_y1, sample_y2, sample_y3, mu);
    
    return outSample;
}
