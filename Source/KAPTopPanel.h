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
    public Button::Listener,
    public ComboBox::Listener
{
public:
    KAPTopPanel(KadenzeAudioPluginAudioProcessor* processor);
    ~KAPTopPanel();
    
private:
    
    /** internal function displays popup menu for 'save as' functionality */
    void displaySaveAsPopup();
    
    /** listener override */
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
    /** button::listener override */
    void buttonClicked(Button* b) override;
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    ScopedPointer<ComboBox> mPresetDisplay;
    
    ScopedPointer<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
    
};
