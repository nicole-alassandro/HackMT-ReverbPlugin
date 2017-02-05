#include "Delay.h"

Delay::Delay(){
	buffer.resize(10000); // max delay of ~200ms @ 44.1k
	bufferIndex = 0;
}

void Delay::setBufferSize(int size)
{
	if (size != buffer.size()) {
		buffer.resize(size);
	}

	clear();
}

void Delay::setLength(int size){
	length = size;
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
	++bufferIndex;

	return temp;
}
