#ifndef TITLE_H
#define TITLE_H

#include "../JuceLibraryCode/JuceHeader.h"

class Title : public Component,
              public Timer
{
public:

	Title();

	void setTarget(float target);

private:

	void paint(Graphics& g) override;

    void timerCallback() override;

    LinearSmoothedValue<int> currentFrame;

    Image spriteSheet;

};

#endif
