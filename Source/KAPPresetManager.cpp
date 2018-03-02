/*
  ==============================================================================

    KAPPresetManager.cpp
    Created: 13 Feb 2018 10:29:40am
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPPresetManager.h"
#include "KAPUsedParameters.h"

KAPPresetManager::KAPPresetManager(AudioProcessor* inProcessor)
:   mCurrentPresetIsSaved(false),
    mCurrentPresetName("Untitled"),
    mProcessor(inProcessor)
{
    const String pluginName = (String)mProcessor->getName();
    
    mPresetDirectory =
    (File::getSpecialLocation(File::userDocumentsDirectory)).getFullPathName()+"/Kadenze/"+pluginName;
    
    /** create our preset directory if it doesn't exist */
    if(!File(mPresetDirectory).exists()){
        File(mPresetDirectory).createDirectory();
    }
    
    /** store our presets internally to the preset manager. */
    storeLocalPresets();
}

KAPPresetManager::~KAPPresetManager()
{
    
}

void KAPPresetManager::getXmlForPreset(XmlElement* inElement)
{
    const int numParameters = mProcessor->getNumParameters();
    
    for(int i = 0; i < numParameters; i ++){
        inElement->setAttribute(mProcessor->getParameterName(i),
                                mProcessor->getParameter(i));
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
                mProcessor->setParameterNotifyingHost(j, value);
                break;
            }
        }
    }
}

int KAPPresetManager::getNumberOfPresets()
{
    return mLocalPresets.size();
}

String KAPPresetManager::getPresetName(int inPresetIndex)
{
    return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
}

void KAPPresetManager::createNewPreset()
{
    /** first, update connected parameters */
    const int numParameters = mProcessor->getNumParameters();
    for(int i = 0; i < numParameters; i ++){
        mProcessor->setParameterNotifyingHost(i, mProcessor->getParameterDefaultValue(i));
    }
    
    /** update our bool */
    mCurrentPresetIsSaved = false;
    mCurrentPresetName = "Untitled";
}

void KAPPresetManager::savePreset()
{
    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    /** delete original file */
    mCurrentlyLoadedPreset.deleteFile();
    
    /** append data */
    mCurrentlyLoadedPreset.appendData(destinationData.getData(), destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
    sendChangeMessageLambda();
}

void KAPPresetManager::saveAsPreset(String inPresetName)
{
    File presetFile = File(mPresetDirectory + "/" + inPresetName + PRESET_FILE_EXTENTION);
    
    if(!presetFile.exists()){
        presetFile.create();
    } else {
        presetFile.deleteFile();
    }
    
    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    presetFile.appendData(destinationData.getData(), destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
    mCurrentPresetName = inPresetName;
    
    storeLocalPresets();
    sendChangeMessageLambda();
}

void KAPPresetManager::loadPreset(int inPresetIndex)
{
    mCurrentlyLoadedPreset = mLocalPresets[inPresetIndex];
    MemoryBlock presetBinary;
    
    if(mCurrentlyLoadedPreset.loadFileAsData(presetBinary)){
        mCurrentPresetIsSaved = true;
        mCurrentPresetName = getPresetName(inPresetIndex);
        mProcessor->setStateInformation(presetBinary.getData(), (int)presetBinary.getSize());
        sendChangeMessageLambda();
    }
}

bool KAPPresetManager::getIsCurrentPresetSaved()
{
    return mCurrentPresetIsSaved;
}

String KAPPresetManager::getCurrentPresetName()
{
    return mCurrentPresetName;
}

void KAPPresetManager::sendChangeMessageLambda()
{
    std::function<void(void)> changeMessageLambda = [this](){
        this->sendChangeMessage();
    };
    
    MessageManager::getInstance()->callAsync(changeMessageLambda);
}

void KAPPresetManager::storeLocalPresets()
{
    mLocalPresets.clear();
    
    /** iterate our preset directory and store preset files in array */
    for (DirectoryIterator di (File(mPresetDirectory),
                               false,
                               "*"+(String)PRESET_FILE_EXTENTION,
                               File::TypesOfFileToFind::findFiles); di.next();){
        
        const File presetFile =  di.getFile();
        mLocalPresets.add(presetFile);
    }
}
