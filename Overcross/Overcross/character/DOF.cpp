#include "DOF.hpp"

DOF::DOF() {
	this->value = 0.0f;
	this->min = -100000.0f;
	this->max = 100000.0f;
}

DOF::DOF(float value, float min, float max) {
	this->min = min;
	this->max = max;
	this->setValue(value);
}

void DOF::setValue(float input) {
	if (input >= this->min && input <= this->max) {
		this->value = input;
	}
	else if (input < this->min) {
		this->value = this->min;
	}
	else if (input > this->max) {
		this->value = this->max;
	}
}

float DOF::getValue() {
	return this->value;
}


void DOF::setMinMax(float max_input, float min_input) {
	this->min = min_input;
	this->max = max_input;
}

float DOF::getMin() {
	return min;
}
float DOF::getMax() {
	return max;
}

float* DOF::getValueAddr() {
	return &value;
}