/*
  ==============================================================================

    KAPUsedParameters.h
    Created: 9 Feb 2018 2:46:05pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

enum {
    kParameter_InputGain = 0,
    kParameter_ModulationRate,
    kParameter_ModulationDepth,
    kParameter_DelayTime,
    kParameter_DelayFeedback,
    kParameter_DelayWetDry,
    kParameter_DelayType,
    kParameter_OutputGain,
    kParameter_TotalNumParameters
};

static String KAPParameterID [kParameter_TotalNumParameters] =
{
    "InputGain",
    "ModulationRate",
    "ModulationDepth",
    "DelayTime",
    "DelayFeedback",
    "DelayWetDry",
    "DelayType",
    "OutputGain"
};

static String KAPParameterLabel [kParameter_TotalNumParameters] =
{
    "Input Gain",
    "Modulation Rate",
    "Modulation Depth",
    "Delay Time",
    "Delay Feedback",
    "Delay WetDry",
    "Delay Type",
    "Output Gain"
};

static float KAPParameterDefaultValue [kParameter_TotalNumParameters] =
{
    0.5f,
    0.2f,
    1.0f,
    0.2f,
    0.5f,
    0.25f,
    0.0f,
    0.5f
};
