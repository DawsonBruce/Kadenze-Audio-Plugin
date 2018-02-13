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
    
    const int comboBox_w = 200;
    const int comboBox_x = TOP_PANEL_WIDTH*0.5 - comboBox_w*0.5;
    
    mPresetDisplay = new ComboBox();
    mPresetDisplay->setText("Untitled", dontSendNotification);
    mPresetDisplay->setBounds(comboBox_x, button_y, comboBox_w, button_h);
    mPresetDisplay->addListener(this);
    addAndMakeVisible(mPresetDisplay);
    
    KAPPresetManager* presetManager = mProcessor->getPresetManager();
    const int numPresets = presetManager->getNumberOfPresets();
    
    for(int i = 0; i < numPresets; i++){
        mPresetDisplay->addItem(presetManager->getPresetName(i), (i+1));
    }
}

KAPTopPanel::~KAPTopPanel()
{
    
}

void KAPTopPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if(comboBoxThatHasChanged == mPresetDisplay){
        
        KAPPresetManager* presetManager = mProcessor->getPresetManager();
        presetManager->loadPreset(mPresetDisplay->getSelectedItemIndex());
    }
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
        
        String currentPresetName = mPresetDisplay->getText();
        AlertWindow window ("Save As","Please Enter a name for you preset.", AlertWindow::NoIcon);
        window.addTextEditor("presetName", currentPresetName, "preset name:");
        window.addButton("Confirm", 1);
        window.addButton("Cancel", 0);
        
        /** confirm has been clicked, and we exit modal loop*/
        if(window.runModalLoop() != 0){
            String presetName = window.getTextEditor("presetName")->getText();
            KAPPresetManager* presetManager = mProcessor->getPresetManager();
            presetManager->saveAsPreset(presetName);
        }
    }
}

void KAPTopPanel::changeListenerCallback (ChangeBroadcaster* source)
{
    KAPPresetManager* presetManager = mProcessor->getPresetManager();
    const int numPresets = presetManager->getNumberOfPresets();
    
    const int selectedItemIndex = mPresetDisplay->getSelectedItemIndex();
    mPresetDisplay->clear(dontSendNotification);
    
    for(int i = 0; i < numPresets; i++){
        mPresetDisplay->addItem(presetManager->getPresetName(i), (i+1));
    }
    
    mPresetDisplay->setSelectedItemIndex(selectedItemIndex, dontSendNotification);
}
