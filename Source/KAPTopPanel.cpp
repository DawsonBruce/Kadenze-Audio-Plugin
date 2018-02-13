/*
  ==============================================================================

    KAPTopPanel.cpp
    Created: 12 Feb 2018 4:01:08pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPTopPanel.h"

KAPTopPanel::KAPTopPanel(KadenzeAudioPluginAudioProcessor* processor)
:   KAPPanelBase(processor)
{
    setSize(TOP_PANEL_WIDTH,
            TOP_PANEL_HEIGHT);
    
    int button_x = 15;
    int button_y = 10;
    int button_w = 55;
    int button_h = 25;
    
    mNewPreset = new TextButton();
    mNewPreset->setButtonText("NEW");
    mNewPreset->setBounds(button_x, button_y, button_w, button_h);
    mNewPreset->addListener(this);
    addAndMakeVisible(mNewPreset);
    button_x = button_x + button_w;
    
    mSavePreset = new TextButton();
    mSavePreset->setButtonText("SAVE");
    mSavePreset->setBounds(button_x, button_y, button_w, button_h);
    mSavePreset->addListener(this);
    addAndMakeVisible(mSavePreset);
    button_x = button_x + button_w;
    
    mSaveAsPreset = new TextButton();
    mSaveAsPreset->setButtonText("SAVE AS");
    mSaveAsPreset->setBounds(button_x, button_y, button_w, button_h);
    mSaveAsPreset->addListener(this);
    addAndMakeVisible(mSaveAsPreset);
}

KAPTopPanel::~KAPTopPanel()
{
    
}

void KAPTopPanel::buttonClicked(Button* b)
{
    if(b == mNewPreset){
        KAPPresetManager* presetManager = mProcessor->getPresetManager();
        presetManager->createNewPreset();
    }
    
    else if(b == mSavePreset){
        
    }
    
    else if(b == mSaveAsPreset){
        KAPPresetManager* presetManager = mProcessor->getPresetManager();
        presetManager->saveAsPreset();
    }
}
