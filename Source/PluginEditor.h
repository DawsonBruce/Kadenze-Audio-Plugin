/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "KAPParameterSlider.h"

#include "KAPMainPanel.h"
#include "KAPLookAndFeel.h"

//==============================================================================
/**
*/
class KadenzeAudioPluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    KadenzeAudioPluginAudioProcessorEditor (KadenzeAudioPluginAudioProcessor&);
    ~KadenzeAudioPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    Image mBackground;
    
    std::unique_ptr<KAPLookAndFeel> mLookAndFeel;
    std::unique_ptr<KAPMainPanel> mMainPanel;
    std::unique_ptr<KAPParameterSlider> mParameterSlider[kParameter_TotalNumParameters];
    std::unique_ptr<Label> mLabel[kParameter_TotalNumParameters];
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KadenzeAudioPluginAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KadenzeAudioPluginAudioProcessorEditor)
};
