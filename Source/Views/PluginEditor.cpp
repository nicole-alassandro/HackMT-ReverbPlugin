/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HackMtreverbPluginAudioProcessorEditor::HackMtreverbPluginAudioProcessorEditor (HackMtreverbPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    background = ImageCache::getFromMemory(BinaryData::Background_png, BinaryData::Background_pngSize);

    setSize (1024, 410);

    title.setBounds(100, 100, 248, 48);
    addAndMakeVisible(title);

    startTimerHz(10);
}

HackMtreverbPluginAudioProcessorEditor::~HackMtreverbPluginAudioProcessorEditor()
{
    stopTimer();
}

void HackMtreverbPluginAudioProcessorEditor::timerCallback()
{
    float dB = juce::Decibels::gainToDecibels(processor.currentRMS);
    dB += 20.0f;
    dB = jmax(-96.0f, dB);
    dB = jmin(0.0f , dB);
    title.setTarget((96.0f - std::abs(dB)) / 96.0f);
}

void HackMtreverbPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.drawImageAt(background, 0, 0);
}

void HackMtreverbPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
