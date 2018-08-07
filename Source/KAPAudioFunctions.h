/*
  ==============================================================================

    KAPAudioFunctions.h
    Created: 9 Feb 2018 8:49:54pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

/** KAP max buffer size. */
#define kMaxChannelBufferSize 192000

/** KAP max num channels. */
#define kMaxNumChannels 8

/** KAP smoothing parameters. */
#define kKAPParamSmoothCoeff_Generic 0.04
#define kKAPParamSmoothCoeff_Fine 0.002
#define kKAPMeterSmoothingCoeff 0.2

/** PI Constants */
static const double kPIHalf	= 1.5707963267948966192313216916397514420985846996;
static const double kPI = 3.1415926535897932384626433832795028841968;
static const double kPI2 = 6.2831853071795864769252867665590057683943;

// use M_PI for mac, and mention that it's not defined on windows

static inline float dBToNormalizedGain(float inVal){
    
    float inValdB = Decibels::gainToDecibels(inVal + 0.00001f);
    inValdB = (inValdB + 96.f) / 96.f;

    return inValdB;
}

/** simple denormalization function. 
    if our number is smaller than 1 times ten to the -15th power (ie. 0.000000000000001) 
    then return 0.0 -- otherwise return original value. 
 */
inline float kap_denorm(float inValue){
    
    float absValue = fabs(inValue);
    
    if(absValue < 1e-15){
        return 0.f;
    } else {
        return inValue;
    }
}

/** linear interpolation algorithm found on wikipedia.
    url: https://en.wikipedia.org/wiki/Linear_interpolation
*/
inline float kap_linear_interp (float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}
