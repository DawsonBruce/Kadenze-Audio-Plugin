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
    mPresetDisplay->setBounds(comboBox_x, button_y, comboBox_w, button_h);
    mPresetDisplay->addListener(this);
    addAndMakeVisible(mPresetDisplay);
    
    KAPPresetManager* presetManager = mProcessor->getPresetManager();
    const int numPresets = presetManager->getNumberOfPresets();
    
    for(int i = 0; i < numPresets; i++){
        mPresetDisplay->addItem(presetManager->getPresetName(i), (i+1));
    }
    
    String presetName = presetManager->getCurrentPresetName();
    mPresetDisplay->setText(presetName, dontSendNotification);
}

KAPTopPanel::~KAPTopPanel()
{
    
}

void KAPTopPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);
    
    g.setColour(KAPColour_1);
    g.setFont(font_2);
    
    String label = "Kadenze Audio Plugin";
    const int label_w = 220;
    g.drawFittedText(label, TOP_PANEL_WIDTH - label_w, 0, label_w, TOP_PANEL_HEIGHT, Justification::centred, 1);
}

void KAPTopPanel::displaySaveAsPopup()
{
    KAPPresetManager* presetManager = mProcessor->getPresetManager();
    String currentPresetName = presetManager->getCurrentPresetName();
    
    if(presetManager->getIsCurrentPresetSaved()){
        currentPresetName = currentPresetName + "_2";
    }
    
    AlertWindow window ("Save As","Please Enter a name for you preset.", AlertWindow::NoIcon);
    window.centreAroundComponent(this, getWidth(), getHeight());
    window.addTextEditor("presetName", currentPresetName, "preset name:");
    window.addButton("Confirm", 1);
    window.addButton("Cancel", 0);
    
    /** confirm has been clicked, and we exit modal loop*/
    if(window.runModalLoop() != 0){
        String presetName = window.getTextEditor("presetName")->getText();
        presetManager->saveAsPreset(presetName);
    }
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
    KAPPresetManager* presetManager = mProcessor->getPresetManager();
    
    if(b == mNewPreset){
        
        presetManager->createNewPreset();
    }
    
    else if(b == mSavePreset){
     
        if(presetManager->getIsCurrentPresetSaved()){
            presetManager->savePreset();
        } else {
            displaySaveAsPopup();
        }
    }
    
    else if(b == mSaveAsPreset){
        
        displaySaveAsPopup();
    }
}

void KAPTopPanel::changeListenerCallback (ChangeBroadcaster* source)
{
    KAPPresetManager* presetManager = mProcessor->getPresetManager();
    String presetName = presetManager->getCurrentPresetName();
    
    mPresetDisplay->clear(dontSendNotification);
    const int numPresets = presetManager->getNumberOfPresets();
    for(int i = 0; i < numPresets; i++){
        mPresetDisplay->addItem(presetManager->getPresetName(i), (i+1));
    }
    
    mPresetDisplay->setText(presetName, dontSendNotification);
}
