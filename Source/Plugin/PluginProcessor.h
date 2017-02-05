/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "../Processors/CombFilter.h"
#include "../Processors/AllPassFilter.h"
#include "../Processors/Delay.h"

//==============================================================================
/**
*/
class HackMtreverbPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    HackMtreverbPluginAudioProcessor();
    ~HackMtreverbPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	int width; // in samples for allpass and comb filter buffers
	int delayTime; // in samples!
	float mix; // wet/dry

private:
    //==============================================================================

    CombFilter combFilters[2][8];
    CombFilter lateCombs[2][8];
    AllPassFilter allpassFilters[2][4];
	Delay predelay[2];
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HackMtreverbPluginAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
