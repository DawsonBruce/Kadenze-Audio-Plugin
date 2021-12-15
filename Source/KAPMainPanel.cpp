/*
  ==============================================================================

    KAPMainPanel.cpp
    Created: 12 Feb 2018 4:01:31pm
    Author:  Output Dev Laptop 2

  ==============================================================================
*/

#include "KAPMainPanel.h"

KAPMainPanel::KAPMainPanel(KadenzeAudioPluginAudioProcessor* inProcessor)
:KAPPanelBase(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH,
            MAIN_PANEL_HEIGHT);
    
    mTopPanel = std::make_unique<KAPTopPanel>(inProcessor);
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mTopPanel.get());
    
    mInputGainPanel = std::make_unique<KAPGainPanel>(inProcessor);
    mInputGainPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
    mInputGainPanel->setParameterID(kParameter_InputGain);
    addAndMakeVisible(mInputGainPanel.get());
    
    mCenterPanel = std::make_unique<KAPCenterPanel>(inProcessor);
    mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mCenterPanel.get());
    
    mOutputputGainPanel = std::make_unique<KAPGainPanel>(inProcessor);
    mOutputputGainPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH,
                                            TOP_PANEL_HEIGHT);
    mOutputputGainPanel->setParameterID(kParameter_OutputGain);
    addAndMakeVisible(mOutputputGainPanel.get());
}

KAPMainPanel::~KAPMainPanel()
{
    
}
