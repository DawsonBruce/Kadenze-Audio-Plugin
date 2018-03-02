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

/** cubic hermite interpolation function
 
 @param         y0              interpolation point minus one.
 @param         y1              interpolation current point.
 @param         y2              interpolation point plus one.
 @param         y3              interpolation point plus two.
 @param         mu              target inter-point value.
 */
inline double kap_cubic_interpolation( double y0, double y1, double y2, double y3, double mu )
{
    double c0 = y1;
    double c1 = 0.5 * ( y2 - y0 );
    double c2 = y0 - 2.5 * y1 + 2.0 * y2 - 0.5 * y3;
    double c3 = 0.5 * ( y3 - y0 ) + 1.5 * ( y1 - y2 );
    return ( (c3 * mu + c2 ) * mu + c1 ) * mu + c0;
    
    //CHECK OUT OTHER OPEN SOURCE INTERPOLATIONS THAT ARE EASILY ACCESSIBLE
}

/** function for returning a time signature based on an unmapped 0.f - 1.f value.
 
@param      inUnmappedValue     the unmapped 0.f - 1.f value we'd like to return a time signature for.
 */

inline float kap_time_signature(float inUnmappedValue)
{
    if(inUnmappedValue<1.0f/18.0f)       return 1.0f/24.0f;//1/64T
    else if(inUnmappedValue<2.0f/18.0f)  return 1.0f/16.0f; //1/64
    else if(inUnmappedValue<3.0f/18.0f)  return 1.0f/12.0f; //1/32T
    else if(inUnmappedValue<4.0f/18.0f)  return 1.0f/16.0f+1.0f/16.0f*0.5f; //1/64D
    else if(inUnmappedValue<5.0f/18.0f)  return 1.0f/8.0f; //1/32
    else if(inUnmappedValue<6.0f/18.0f)  return 1.0f/6.0f; //1/16T
    else if(inUnmappedValue<7.0f/18.0f)  return 1.0f/8.0+1.0f/8.0*0.5f; //1/32D
    else if(inUnmappedValue<8.0f/18.0f)  return 1.0f/4.0f; //1/16
    else if(inUnmappedValue<9.0f/18.0f)  return 1.0f/3.0f; //1/8T
    else if(inUnmappedValue<10.0f/18.0f) return 1.0f/4.0f+1.0f/4.0f*0.5f; //1/16D
    else if(inUnmappedValue<11.0f/18.0f) return 1.0f/2.0f; //1/8
    else if(inUnmappedValue<12.0f/18.0f) return 2.0f/3.0f; //1/4T
    else if(inUnmappedValue<13.0f/18.0f) return 1.0f/2.0f+1.0f/2.0f*0.5f; //1/8D
    else if(inUnmappedValue<14.0f/18.0f) return 1.0f/1.0f; //1/4
    else if(inUnmappedValue<15.0f/18.0f) return 4.0f/3.0f; //1/2T
    else if(inUnmappedValue<16.0f/18.0f) return 1.0f/1.0f+1.0f/1.0f*0.5f; //1/4D
    else if(inUnmappedValue<17.0f/18.0f) return 2.0f/1.0f; //1/2
    else return 2.0f/1.0f+2.0f/1.0f*0.5f; //1/2D
}
