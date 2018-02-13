/*
  ==============================================================================

    KAPPresetManager.cpp
    Created: 13 Feb 2018 10:29:40am
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPPresetManager.h"


KAPPresetManager::KAPPresetManager(AudioProcessor* inProcessor)
:   mProcessor(inProcessor)
{
    const String pluginName = (String)mProcessor->getName();
    
    mPresetDirectory =
    (File::getSpecialLocation(File::userDocumentsDirectory)).getFullPathName()+"/Kadenze/"+pluginName;
    
    /** create our preset directory if it doesn't exist */
    if(!File(mPresetDirectory).exists()){
        File(mPresetDirectory).createDirectory();
    }
    
    
}

KAPPresetManager::~KAPPresetManager()
{
    
}

void KAPPresetManager::getXmlForPreset(XmlElement* inElement)
{
    const int numParameters = mProcessor->getNumParameters();
    
    for(int i = 0; i < numParameters; i ++){
        inElement->setAttribute(mProcessor->getParameterName(i), mProcessor->getParameter(i));
    }
}

void KAPPresetManager::loadPresetForXml(XmlElement* inElement)
{
    mCurrentPresetXml = inElement;
    
    /** iterate our XML for attribute name and value */
    for(int i = 0; i < mCurrentPresetXml->getNumAttributes(); i ++){
        String name = mCurrentPresetXml->getAttributeName(i);
        float value = mCurrentPresetXml->getDoubleAttribute(name);
        
        /** iterate our parameter list for name. */
        for(int j = 0; j < mProcessor->getNumParameters(); j++){
            if(mProcessor->getParameterName(j) == name){
                mProcessor->setParameter(j, value);
                break;
            }
        }
    }
}


void KAPPresetManager::createNewPreset()
{
    /** first, update connected parameters */
    const int numParameters = mProcessor->getNumParameters();
    for(int i = 0; i < numParameters; i ++){
        mProcessor->setParameter(i,
                                 mProcessor->getParameterDefaultValue(i));
    }
    
    /** second, broadcast change message to update UI. */
    sendChangeMessage();
}

void KAPPresetManager::savePreset()
{
    DBG("SAVE!");
}

void KAPPresetManager::saveAsPreset()
{
    String presetName = "Preset";    
    File presetFile = File(mPresetDirectory + "/" + presetName + PRESET_FILE_EXTENTION);
    
    if(!presetFile.exists()){
        presetFile.create();
    } else {
        presetFile.deleteFile();
    }
    
    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    presetFile.appendData(destinationData.getData(), destinationData.getSize());
    presetFile.revealToUser();
}
