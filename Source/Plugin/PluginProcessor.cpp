/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
HackMtreverbPluginAudioProcessor::HackMtreverbPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

HackMtreverbPluginAudioProcessor::~HackMtreverbPluginAudioProcessor()
{
}

//==============================================================================
const String HackMtreverbPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HackMtreverbPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HackMtreverbPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double HackMtreverbPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HackMtreverbPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HackMtreverbPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HackMtreverbPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String HackMtreverbPluginAudioProcessor::getProgramName (int index)
{
    return String();
}

void HackMtreverbPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HackMtreverbPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    int combSizes[8] = { 1157, 1617, 1491, 1422, 1277, 1356, 1188, 1116 };
    int allpassSizes[4] = { 225, 556, 441, 341 };

    for (int i = 0; i < 8; ++i)
    {
        combFilters[i].setSize(((int)sampleRate * (combSizes[i] * 1.5)) / 44100);
        lateCombs[i].setSize(((int)sampleRate * (combSizes[i] * 1.5)) / 44100);
    }

    for (int i = 0; i < 4; ++i)
    {
        allpassFilters[i].setSize(((int)sampleRate * (allpassSizes[i] * 1.5)) / 44100);
    }
}

void HackMtreverbPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HackMtreverbPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HackMtreverbPluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
//    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
//        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < 1; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {

            float input = channelData[sample];

            float output = 0;

            for (int i = 0; i < 8; ++i)
            {
                output += combFilters[i].process(input, 0.1f, 0.5f) / 8;
            }

            float tempComb = output;

            for (int i = 0; i < 8; ++i)
            {
                output += lateCombs[i].process(input, 0.1f, 0.5f) / 8;
            }

            output = (tempComb + output) / 2;

            for (int i = 0; i < 2; ++i)
            {
                output = allpassFilters[i].process(output);
            }

            float tempAllPass = output;

            for (int i = 3; i < 4; ++i)
            {
                output = allpassFilters[i].process(output);
            }

            output = (output + tempAllPass) / 2;

            channelData[sample] = output;
        }

        // ..do something to the data...
    }
}

//==============================================================================
bool HackMtreverbPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HackMtreverbPluginAudioProcessor::createEditor()
{
    return new HackMtreverbPluginAudioProcessorEditor (*this);
}

//==============================================================================
void HackMtreverbPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HackMtreverbPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HackMtreverbPluginAudioProcessor();
}
