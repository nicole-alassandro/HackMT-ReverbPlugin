#include "Knob.h"

Knob::Knob()
{
    setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    setSize(96, 96);
    setLookAndFeel(this);
    background = ImageCache::getFromMemory(BinaryData::Knob_png, BinaryData::Knob_pngSize);
    indicator.setSize(8, 8);
}

void Knob::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    g.drawImageAt(background, 0, 0);
    Point<float> finalPos = Point<float>(48, 48).getPointOnCircumference(32, rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle));
    indicator.setCentre(finalPos.x, finalPos.y);
    g.setColour(Colours::white.withAlpha(0.5f));
    g.fillEllipse(indicator.getX(), indicator.getY(), indicator.getWidth(), indicator.getHeight());
}
