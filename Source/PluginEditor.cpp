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
    
    mLookAndFeel = new KAPLookAndFeel();
    setLookAndFeel(mLookAndFeel);
    LookAndFeel::setDefaultLookAndFeel(mLookAndFeel);
    
    mBackground = ImageCache::getFromMemory(BinaryData::kadenze_bg_png,
                                            BinaryData::kadenze_bg_pngSize);
}

KadenzeAudioPluginAudioProcessorEditor::~KadenzeAudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void KadenzeAudioPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.drawImage(mBackground, getBounds().toFloat());
}

void KadenzeAudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
