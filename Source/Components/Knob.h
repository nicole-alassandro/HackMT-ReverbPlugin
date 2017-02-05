#ifndef KNOB_H
#define KNOB_H

#include "../JuceLibraryCode/JuceHeader.h"

class Knob : public juce::Slider
{
public:

	Knob();

private:

	void paint(Graphics& g) override;

    Image background;

};

#endif
