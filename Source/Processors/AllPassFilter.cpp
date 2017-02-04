#include "AllPassFilter.h"

void AllPassFilter::setSize(int size) {
	if (size != buffer.size()) {
		buffer.resize(size);
	}
	clear();
}

void AllPassFilter::clear() {
	for (auto iter = buffer.begin(); iter != buffer.end(); ++iter) {
		(*iter) = 0;
	}
}

float AllPassFilter::process(const float & input){
	float fb = buffer[bufferIndex];
	float ff = input + (-gain) * fb;

    ff += 0.1f; ff -= 0.1f;

	float output = (ff * gain) + fb;

	buffer[bufferIndex] = ff;
	bufferIndex = (bufferIndex + 1) % buffer.size();

	return output;
}
