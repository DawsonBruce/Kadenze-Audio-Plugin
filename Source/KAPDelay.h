/*
  ==============================================================================

    KAPDelay.h
    Created: 9 Feb 2018 2:47:01pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define kMaxDelayBufferSize 96000


class KAPDelay
{
public:
    
    KAPDelay();
    ~KAPDelay();
    
    void setSampleRate(double inSampleRate);
    
    void reset();
    
    void process(float* inAudio, float inTime, float inFeedback, float* outAudio, int inNumSamplesToRender);
    
private:
    
    /** internal */
    double getInterpolatedSample(float inDelayTimeInSamples);
    
    float mTimeSmoothed;
    float mFeedbackSmoothed;
    
    double mSampleRate;
    double mBuffer[kMaxDelayBufferSize];
    double mFeedbackSample;
    
    int mDelayIndex;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KAPDelay)
};
