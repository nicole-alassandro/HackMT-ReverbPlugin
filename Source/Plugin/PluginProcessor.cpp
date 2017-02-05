#include "PluginProcessor.h"
#include "../Views/PluginEditor.h"

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

    currentRMS = 0;

    mix.reset(10, 0.1);
    width.reset(10, 0.1);
    delayTime.reset(10, 0.1);

    mix.setValue(1.0);
    width.setValue(25);
    delayTime.setValue(0);

}

HackMtreverbPluginAudioProcessor::~HackMtreverbPluginAudioProcessor()
{
}


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
    return 1;
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

void HackMtreverbPluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    currentRMS = 0;
	int combSizes[8] = { 1157, 1617, 1491, 1422, 1277, 1356, 1188, 1116 };
	int allpassSizes[4] = { 225, 556, 441, 341 };
	for (int j = 0; j < getNumInputChannels(); ++j) {
		for (int i = 0; i < 8; ++i)
		{
			combFilters[j][i].setSize(((int)sampleRate * (combSizes[i] + (j * width.getNextValue()))) / 44100);
			lateCombs[j][i].setSize(((int)sampleRate * (combSizes[i] + (j * width.getNextValue()))) / 44100);
		}

		for (int i = 0; i < 4; ++i)
		{
			allpassFilters[j][i].setSize(((int)sampleRate * (allpassSizes[i] + (j * width.getNextValue()))) / 44100);
		}

        int predelaySize = (int)((0.2f) / (1.0f/sampleRate));
        predelay[j].setBufferSize(predelaySize);
        predelay[j].setLength(predelaySize);
	}

    currentSampleRate = sampleRate;
}

void HackMtreverbPluginAudioProcessor::releaseResources()
{
    currentRMS = 0;
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HackMtreverbPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

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

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float input = channelData[sample];
			float dry = input;

            float output = 0;

			output = predelay[channel].process(input);

            for (int i = 0; i < 8; ++i)
            {
                output += combFilters[channel][i].process(input, 0.1f, 0.5f) / 8;
            }

            float tempComb = output;

            for (int i = 0; i < 8; ++i)
            {
                output += lateCombs[channel][i].process(input, 0.1f, 0.5f) / 8;
            }

            output = (tempComb + output) / 2;

            for (int i = 0; i < 2; ++i)
            {
                output = allpassFilters[channel][i].process(output);
            }

            float tempAllPass = output;

            for (int i = 3; i < 4; ++i)
            {
                output = allpassFilters[channel][i].process(output);
            }

            output = (output + tempAllPass) / 2;

            channelData[sample] = (input * (1.0 - mix.getNextValue())) + (output * mix.getNextValue());
        }

        currentRMS = buffer.getRMSLevel(0, 0, buffer.getNumSamples()) * mix.getNextValue();

    }
}

bool HackMtreverbPluginAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* HackMtreverbPluginAudioProcessor::createEditor()
{
    return new HackMtreverbPluginAudioProcessorEditor (*this);
}

void HackMtreverbPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{

}

void HackMtreverbPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HackMtreverbPluginAudioProcessor();
}
