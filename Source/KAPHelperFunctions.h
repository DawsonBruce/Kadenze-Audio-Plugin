/*
  ==============================================================================

    KAPHelperFunctions.h
    Created: 9 Feb 2018 9:18:20pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

/** KAP NaN Macro -- we'll assert if we hit a NaN, so we can break before the code crashes. */
#define kapassert_isnan(expression)  jassert(!isnan(expression))
