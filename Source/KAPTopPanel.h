/*
  ==============================================================================

    KAPTopPanel.h
    Created: 12 Feb 2018 4:01:08pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

class KAPTopPanel
:   public KAPPanelBase
{
public:
    KAPTopPanel(KadenzeAudioPluginAudioProcessor* processor);
    ~KAPTopPanel();
    
    void paint(Graphics& g) override;
    
private:
    
    /** internal function displays popup menu for 'save as' functionality */
    void displaySaveAsPopup();
    
    /** internal */
    void updatePresetComboBox();
    
    std::unique_ptr<ComboBox> mPresetDisplay;
    
    std::unique_ptr<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
    
};
