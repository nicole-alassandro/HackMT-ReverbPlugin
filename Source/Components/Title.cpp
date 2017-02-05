#include "Title.h"

Title::Title()
{
    spriteSheet = ImageCache::getFromMemory(BinaryData::Title_png, BinaryData::Title_pngSize);
    currentFrame.reset(1, 2);
    startTimerHz(30);
}

void Title::setTarget(float target)
{
    currentFrame.setValue(target * 24.0f);
}

void Title::timerCallback()
{
    repaint();
}

void Title::paint(juce::Graphics& g)
{
    g.drawImage(spriteSheet, 0, 0, 248, 48, 0, 48 * currentFrame.getNextValue(), 248, 48);
}
