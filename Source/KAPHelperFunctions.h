/*
  ==============================================================================

    KAPHelperFunctions.h
    Created: 9 Feb 2018 9:18:20pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

/** KAP NaN Macro -- we'll assert if we hit a NaN, so we can break before the code crashes. */
#define kapassert_isnan(expression)  jassert(!isnan(expression))

inline void paintComponentLabel(Graphics& g, Component* inComponent)
{
    const int x = inComponent->getX();
    const int y = inComponent->getY() + inComponent->getHeight();
    const int w = inComponent->getWidth();
    const int h = 20;
    const String label = inComponent->getName();
    
    g.drawFittedText(label, x, y, w, h, Justification::centred, 1);
}
