#pragma once
#ifndef COMBFILTER_H
#define COMBFILTER_H

#include <vector>

using std::vector;

class CombFilter {
public:
	CombFilter() : bufferIndex(0), lastCombOut(0) {};
	void setSize(const int& size);
	void clear();
	float process(const float input, const float damp, const float feedbacklvl);
private:
	vector<float> buffer;
	int bufferIndex;
	float lastCombOut;
};


#endif