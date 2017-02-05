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

    mix.setRange(0, 1.0, 0.1);
    mix.setTopLeftPosition(300, 300);
    mix.addListener(this);
    addAndMakeVisible(mix);

    predelay.setRange(1, 200, 1);
    predelay.setTopLeftPosition(500, 300);
    predelay.addListener(this);
    addAndMakeVisible(predelay);

    width.setRange(0, 50, 1);
    width.setTopLeftPosition(700, 300);
    width.addListener(this);
    addAndMakeVisible(width);

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

void HackMtreverbPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* s)
{
    if (s == &mix)
    {
        processor.mix.setValue(mix.getValue());
    }
    else if (s == &predelay)
    {
        processor.delayTime.setValue(predelay.getValue());
        processor.predelay[0].setLength((predelay.getValue()/1000.0f) / (1.0f/processor.currentSampleRate));
        processor.predelay[1].setLength((predelay.getValue()/1000.0f) / (1.0f/processor.currentSampleRate));
    }
    else if (s == &width)
    {
        processor.width = width.getValue();
    }
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
