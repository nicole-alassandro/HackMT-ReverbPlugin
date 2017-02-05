#ifndef KNOB_H
#define KNOB_H

#include "../JuceLibraryCode/JuceHeader.h"

class Knob : public juce::Slider,
             public juce::LookAndFeel_V3
{
public:

	Knob();

private:

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;

    Image background;

    Rectangle<int> indicator;

};

#endif
