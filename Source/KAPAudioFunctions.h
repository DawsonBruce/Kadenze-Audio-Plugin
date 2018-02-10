/*
  ==============================================================================

    KAPAudioFunctions.h
    Created: 9 Feb 2018 8:49:54pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#define kKAPParamSmoothCoeff_Generic 0.04
#define kKAPParamSmoothCoeff_Fine 0.002


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
}
