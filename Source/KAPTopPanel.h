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
:   public KAPPanelBase,
    public Button::Listener
{
public:
    KAPTopPanel(KadenzeAudioPluginAudioProcessor* processor);
    ~KAPTopPanel();
    
private:
    
    /** button::listener override */
    void buttonClicked(Button* b) override;
    
    ScopedPointer<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
    
};
