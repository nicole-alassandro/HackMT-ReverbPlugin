#include "Delay.h"

Delay::Delay(){
	buffer.resize(8820); // max delay of ~200ms @ 44.1k
	bufferIndex = 0;
    length = 1;
}

void Delay::setBufferSize(int size)
{
	if (size != buffer.size()) {
		buffer.resize(size);
	}

	clear();
}

void Delay::setLength(int size){
	if (size < buffer.size()) {
		length = size;
	}
	else {
		length = buffer.size() - 1;
	}
}

void Delay::clear(){
	for (auto iter = buffer.begin(); iter != buffer.end(); ++iter) {
		(*iter) = 0;
	}
}

float Delay::process(float const &input)
{
	float temp = buffer[bufferIndex]; // read out delayed sample
	buffer[bufferIndex] = input; // store new sample
	
	// move the index!
	bufferIndex = (bufferIndex + 1) % length;

	return temp;
}
