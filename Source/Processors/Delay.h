#pragma once
#ifndef DELAY_H
#define DELAY_H

#include <vector>

using std::vector;

class Delay {
public:
	Delay();
	void setBufferSize(int size); // set buffer size
	void setLength(int size); // set delay size
	void clear();
	float process(float const &input);
private:
	vector<float> buffer;
	int length;
	int bufferIndex;
};

#endif
