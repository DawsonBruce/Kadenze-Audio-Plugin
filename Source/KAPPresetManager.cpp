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
    /** iterate our XML for attribute name and value */
    for(int i = 0; i < inElement->getNumAttributes(); i ++){
        String name = inElement->getAttributeName(i);
        float value = inElement->getDoubleAttribute(name);
        
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
    DBG("SAVE AS!");
}
