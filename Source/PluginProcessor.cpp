/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


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
                       )
#endif
{
    setLastOpenedPanel(0);
    
    /** initialize our dsp */
    initializeDSP();
    
    /** initialize our parameters */
    initializeParameters();
    
    mPresetManager = new KAPPresetManager(this);
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
        
        /** process input gain */
        mInputGain[channel]->process(channelData,
                                     getParameter(kParameter_InputGain),
                                     channelData,
                                     numSamplesToRender);
        
        /** process lfo */
        float lfoBuffer [numSamplesToRender];
        float rate = channel==0 ? 0: getParameter(kParameter_ModulationRate);

        mLfo[channel]->process(rate,
                               getParameter(kParameter_ModulationDepth),
                               lfoBuffer,
                               numSamplesToRender);
        
        /** process delay. */
        mDelay[channel]->process(channelData,
                        getParameter(kParameter_DelayTime),
                        getParameter(kParameter_DelayFeedback),
                        getParameter(kParameter_DelayWetDry),
                        getParameter(kParameter_DelayType),
                        lfoBuffer,
                        channelData,
                        numSamplesToRender);
        
        /** process output gain */
        mOutputGain[channel]->process(channelData,
                                     getParameter(kParameter_OutputGain),
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
    DBG("KadenzeAudioPluginAudioProcessor::setStateInformation");
    
    XmlElement* xmlState = getXmlFromBinary(data, sizeInBytes);
    
    if(xmlState != nullptr){
        forEachXmlChildElement(*xmlState, subchild){
            mPresetManager->loadPresetForXml(subchild);
        }
    } else {
        
        DBG("KadenzeAudioPluginAudioProcessor::setStateInformation XML NULL");
    }
}

void KadenzeAudioPluginAudioProcessor::setParameter (int parameterIndex, float newValue)
{
    DBG("parameter : " << parameterIndex);
    DBG("value : " << newValue);
    AudioProcessor::setParameter(parameterIndex, newValue);
    sendChangeMessage();
}

void KadenzeAudioPluginAudioProcessor::setLastOpenedPanel(int inPanelID)
{
    mLastOpenedPanel=inPanelID;
}

int KadenzeAudioPluginAudioProcessor::getLastOpenedPanel()
{
    return mLastOpenedPanel;
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
    return mPresetManager;
}

void KadenzeAudioPluginAudioProcessor::initializeDSP()
{
    for(int i = 0; i < getTotalNumInputChannels(); i++){
        mLfo[i] = new KAPLfo();
        mDelay[i] = new KAPDelay();
        mInputGain[i] = new KAPGain();
        mOutputGain[i] = new KAPGain();
    }
}

void KadenzeAudioPluginAudioProcessor::initializeParameters()
{
    /** add our parameters to processor */
    addParameter (parameters[kParameter_InputGain]
                  = new AudioParameterFloat ("inputgain",  "InputGain", 0.0f, 1.0f, 0.5f));
    
    addParameter (parameters[kParameter_ModulationRate]
                  = new AudioParameterFloat ("rate", "Rate", 0.0f, 1.0f, 0.5f));
    
    addParameter (parameters[kParameter_ModulationDepth]
                  = new AudioParameterFloat ("depth",  "Depth", 0.0f, 1.0f, 0.5f));
    
    addParameter (parameters[kParameter_DelayTime]
                  = new AudioParameterFloat ("time", "Time", 0.0f, 1.0f, 0.5f));
    
    addParameter (parameters[kParameter_DelayFeedback]
                  = new AudioParameterFloat ("feedback", "Feedback", 0.0f, 1.0f, 0.5f));
    
    addParameter (parameters[kParameter_DelayWetDry]
                  = new AudioParameterFloat ("wetdry",  "WetDry", 0.0f, 1.0f, 0.5f));
    
    addParameter (parameters[kParameter_DelayType]
                  = new AudioParameterFloat ("type",  "Type", 0.0f, 1.0f, 0.0f));
    
    addParameter (parameters[kParameter_OutputGain]
                  = new AudioParameterFloat ("outputgain",  "OutputGain", 0.0f, 1.0f, 0.5f));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KadenzeAudioPluginAudioProcessor();
}
