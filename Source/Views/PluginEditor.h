/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Components/Title.h"


//==============================================================================
/**
*/
class HackMtreverbPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                                public Timer
{
public:
    HackMtreverbPluginAudioProcessorEditor (HackMtreverbPluginAudioProcessor&);
    ~HackMtreverbPluginAudioProcessorEditor();

    void timerCallback() override;

    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HackMtreverbPluginAudioProcessor& processor;

    Image background;
    Title title;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HackMtreverbPluginAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
