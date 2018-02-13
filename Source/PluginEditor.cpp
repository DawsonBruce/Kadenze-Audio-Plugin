/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "KAPInterfaceDefines.h"

//==============================================================================
KadenzeAudioPluginAudioProcessorEditor::KadenzeAudioPluginAudioProcessorEditor (KadenzeAudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (MAIN_PANEL_WIDTH,
             MAIN_PANEL_HEIGHT);
    
    mMainPanel = new KAPMainPanel(&processor);
    mMainPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mMainPanel);
    
//    int x = 55;
//    int y = 10;
//    const int size = 64;
//    
//    for(int i = 0; i < kParameter_TotalNumParameters; i++){
//        mParameterSlider[i] = new KAPParameterSlider(processor.parameters[i]);
//        mParameterSlider[i]->setBounds(x, y, size, size);
//        addAndMakeVisible(mParameterSlider[i]);
//        
//        mLabel[i] = new Label(String(), mParameterSlider[i]->getName());
//        mLabel[i]->attachToComponent(mParameterSlider[i], true);
//        addAndMakeVisible(mLabel[i]);
//        
//        if((y+size) > (getHeight() - size)){
//            y = 10;
//            x = x + (size*2);
//        } else {
//            y = y + size;
//        }
//    }
}

KadenzeAudioPluginAudioProcessorEditor::~KadenzeAudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void KadenzeAudioPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.setGradientFill(ColourGradient(Colour(235,235,235),
                                     getWidth()*0.5, 0,
                                     Colour(205,205,205),
                                     getWidth()*0.5, getHeight(),
                                     false));
    g.fillAll();
}

void KadenzeAudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
