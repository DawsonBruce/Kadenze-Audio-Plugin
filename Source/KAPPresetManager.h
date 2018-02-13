/*
  ==============================================================================

    KAPPresetManager.h
    Created: 13 Feb 2018 10:29:40am
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KAPPresetManager
:   public ChangeBroadcaster
{
public:
    
    KAPPresetManager(AudioProcessor* inProcessor);
    ~KAPPresetManager();
    
    void getXmlForPreset(XmlElement* inElement);
    
    void loadPresetForXml(XmlElement* inElement);
    
    /** used for loading a 'new' preset -- essentially resets all parameters to their default values. */
    void createNewPreset();
    
    /** used for saving a preset. This is used on presets that have already been saved and are being overriden. */
    void savePreset();
    
    /** used for saving a NEW preset. 
        this'll store a new preset on the disk at a file location specified in the parameter manager. */
    void saveAsPreset();
    
private:
    
    AudioProcessor* mProcessor;
};
