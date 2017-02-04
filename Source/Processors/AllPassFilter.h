#pragma once
#ifndef ALLPASSFILTER_H
#define ALLPASSFILTER_H

#include <vector>

using std::vector;

class AllPassFilter {
public:
	AllPassFilter() : bufferIndex(0), gain(0.5) {};
	void setSize(int size);
	void clear();
	float process(const float &input);

private:
	vector<float> buffer;
	int bufferIndex;
	float gain;
};

#endif