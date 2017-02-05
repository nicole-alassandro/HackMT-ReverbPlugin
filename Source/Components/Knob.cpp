#include "Knob.h"

Knob::Knob()
{

    setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);

    background = ImageCache::getFromMemory(BinaryData::Knob_png, BinaryData::Knob_pngSize);

}

void Knob::paint(Graphics& g)
{

    g.drawImageAt(background, 0, 0);

}
