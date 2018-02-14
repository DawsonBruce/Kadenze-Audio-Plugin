/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "KAPUsedParameters.h"
#include "KAPAudioFunctions.h"

#include "KAPDelay.h"
#include "KAPLfo.h"
#include "KAPGain.h"

#include "KAPPresetManager.h"

//==============================================================================
/**
*/
class KadenzeAudioPluginAudioProcessor  : public AudioProcessor, public ChangeBroadcaster
{
public:
    //==============================================================================
    KadenzeAudioPluginAudioProcessor();
    ~KadenzeAudioPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void setParameter (int parameterIndex, float newValue) override;
    
    void setLastOpenedPanel(int inPanelID);
    
    int getLastOpenedPanel();
    
    float getInputGainMeterLevel(int inChannel);
    
    float getOutputGainMeterLevel(int inChannel);
    
    KAPPresetManager* getPresetManager();

    // Our parameters
    AudioParameterFloat* parameters[kParameter_TotalNumParameters];
    
private:
    
    /** internal */
    void initializeDSP();
    /** internal */
    void initializeParameters();
    
    int mLastOpenedPanel;
    
    ScopedPointer<KAPPresetManager> mPresetManager;
    
    ScopedPointer<KAPDelay> mDelay [kMaxNumChannels];
    ScopedPointer<KAPLfo> mLfo [kMaxNumChannels];
    ScopedPointer<KAPGain> mInputGain [kMaxNumChannels];
    ScopedPointer<KAPGain> mOutputGain [kMaxNumChannels];
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KadenzeAudioPluginAudioProcessor)
};
