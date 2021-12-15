/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<AudioParameterFloat>> params;
    
    for(int i = 0; i < kParameter_TotalNumParameters; i++){
        
        params.push_back(std::make_unique<AudioParameterFloat>(KAPParameterID[i],
                                                               KAPParameterLabel[i],
                                                               NormalisableRange<float> (0.0f, 1.0f),
                                                               KAPParameterDefaultValue[i]));
    }
    
    return { params.begin(), params.end() };
}

//==============================================================================
KadenzeAudioPluginAudioProcessor::KadenzeAudioPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
    parameters(*this /** reference to processor */,
               nullptr /** null pointer to undoManager (optional) */,
               juce::Identifier("KAP") /** valueTree identifier */,
               createParameterLayout() /** initialize parameters */)
#endif
{
    /** initialize our dsp */
    initializeDSP();
    
    /** initialize our parameters */
    //initializeParameters();
    
    /** JUCE 5.1.2
    mPresetManager = new KAPPresetManager(this);
    */
    
    mPresetManager =
    std::make_unique<KAPPresetManager>(this);
}

KadenzeAudioPluginAudioProcessor::~KadenzeAudioPluginAudioProcessor()
{
}

//==============================================================================
const String KadenzeAudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KadenzeAudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KadenzeAudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KadenzeAudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KadenzeAudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KadenzeAudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KadenzeAudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KadenzeAudioPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String KadenzeAudioPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void KadenzeAudioPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void KadenzeAudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    for(int i = 0; i < getTotalNumInputChannels(); i++){
        mDelay[i]->setSampleRate(sampleRate);
        mLfo[i]->setSampleRate(sampleRate);
    }
}

void KadenzeAudioPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KadenzeAudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void KadenzeAudioPluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        const int numSamplesToRender = buffer.getNumSamples();
        
        /** JUCE 5.1.2
        mInputGain[channel]->process(channelData,
                                     getParameter(kParameter_InputGain),
                                     channelData,
                                     numSamplesToRender);
        */
        
        /** process input gain */
        mInputGain[channel]->process(channelData,
                                     *parameters.getRawParameterValue(KAPParameterID[kParameter_InputGain]),
                                     channelData,
                                     numSamplesToRender);
        
        /** JUCE 5.1.2
        float rate = channel==0 ? 0: getParameter(kParameter_ModulationRate);
        
        mLfo[channel]->process(rate,
                               getParameter(kParameter_ModulationDepth),
                               numSamplesToRender);
        */
        
        /** process lfo */
        float rate = 0;
        
        if(channel==1){
            rate = *parameters.getRawParameterValue(KAPParameterID[kParameter_ModulationRate]);
        }
        
        mLfo[channel]->process(rate,
                               *parameters.getRawParameterValue(KAPParameterID[kParameter_ModulationDepth]),
                               numSamplesToRender);
        
        /** JUCE 5.1.2
        mDelay[channel]->process(channelData,
                        getParameter(kParameter_DelayTime),
                        getParameter(kParameter_DelayFeedback),
                        getParameter(kParameter_DelayWetDry),
                        getParameter(kParameter_DelayType),
                        mLfo[channel]->getBuffer(),
                        channelData,
                        numSamplesToRender);
        */
        
        /** process delay. */
        mDelay[channel]->process(channelData,
                                 *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayTime]),
                                 *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayFeedback]),
                                 *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayWetDry]),
                                 *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayType]),
                                 mLfo[channel]->getBuffer(),
                                 channelData,
                                 numSamplesToRender);
        
        /** JUCE 5.1.2
        mOutputGain[channel]->process(channelData,
                                     getParameter(kParameter_OutputGain),
                                     channelData,
                                     numSamplesToRender);
        */
        
        /** process output gain */
        mOutputGain[channel]->process(channelData,
                                      *parameters.getRawParameterValue(KAPParameterID[kParameter_OutputGain]),
                                      channelData,
                                      numSamplesToRender);
    }
}

//==============================================================================
bool KadenzeAudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* KadenzeAudioPluginAudioProcessor::createEditor()
{
    return new KadenzeAudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void KadenzeAudioPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    DBG("KadenzeAudioPluginAudioProcessor::getStateInformation");
    
    XmlElement preset(("KAP_StateInfo"));
    XmlElement* presetBody = new XmlElement("KAP_Preset");
    
    mPresetManager->getXmlForPreset(presetBody);
    
    preset.addChildElement(presetBody);
    copyXmlToBinary (preset, destData);
}

void KadenzeAudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    const auto xmlState = getXmlFromBinary(data, sizeInBytes);
    
    jassert (xmlState.get() != nullptr);
    
    for(auto* subchild : xmlState->getChildIterator()){
        mPresetManager->loadPresetForXml(subchild);
    }
}

float KadenzeAudioPluginAudioProcessor::getInputGainMeterLevel(int inChannel)
{
    return mInputGain[inChannel]->getMeterLevel();
}

float KadenzeAudioPluginAudioProcessor::getOutputGainMeterLevel(int inChannel)
{
    return mOutputGain[inChannel]->getMeterLevel();
}

KAPPresetManager* KadenzeAudioPluginAudioProcessor::getPresetManager()
{
    return mPresetManager.get();
}

void KadenzeAudioPluginAudioProcessor::initializeDSP()
{
    for(int i = 0; i < getTotalNumInputChannels(); i++){
        mLfo[i] = std::make_unique<KAPLfo>();
        mDelay[i] = std::make_unique<KAPDelay>();
        mInputGain[i] = std::make_unique<KAPGain>();
        mOutputGain[i] = std::make_unique<KAPGain>();
    }
}

void KadenzeAudioPluginAudioProcessor::initializeParameters()
{
//    /** add our parameters to processor */
//    for(int i = 0; i < kParameter_TotalNumParameters; i++){
//        parameters.createAndAddParameter(KAPParameterID[i],
//                                         KAPParameterID[i],
//                                         KAPParameterLabel[i],
//                                         NormalisableRange<float> (0.0f, 1.0f),
//                                         KAPParameterDefaultValue[i],
//                                         nullptr,
//                                         nullptr);
//    }
//
//    parameters.state = ValueTree (Identifier ("KAP"));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KadenzeAudioPluginAudioProcessor();
}
