#include "CombFilter.h"

void CombFilter::setSize(const int & size)
{
	if (size != buffer.size()) {
		bufferIndex = 0;
		buffer.resize(size);
	}
}

void CombFilter::clear()
{
	lastCombOut = 0;
	for (auto iter = buffer.begin(); iter != buffer.end(); ++iter) {
		(*iter) = 0;
	}
}

float CombFilter::process(const float input, const float damp, const float feedbacklvl)
{
	// read element at current position in filter buffer
	const float output = buffer[bufferIndex];
	float filterOut;

	// implement LPF in feedback to simulate room damping
	lastCombOut = (output * (1.0 - damp)) + (lastCombOut * damp);
	
	// implement comb filter
	filterOut = input + (lastCombOut *feedbacklvl);

	// write filter output to buffer and inc index
	buffer[bufferIndex] = filterOut;
	bufferIndex = (bufferIndex + 1) % buffer.size();

	return filterOut;
}
