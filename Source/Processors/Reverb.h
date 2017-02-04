#ifndef REVERB_H
#define REVERB_H

class Reverb
{
public:

	Reverb();

	virtual void process() = 0;
	virtual void setBufferSizes() = 0;

	virtual void setRoomsize(float s);
	virtual void setWidth(float w);
	virtual void setDamping(float d);

private:

	float roomSize;
	float width;
	float damping;

};

#endif
