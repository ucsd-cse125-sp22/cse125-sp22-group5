#include "vertex.hpp"

vertex::vertex(float a, float b, float c) {
	positions = { a, b, c };
}

void vertex::setNormal(float a, float b, float c) {
	normals = { a, b, c };
}

void vertex::addBind(int joint, float weight) {
	joints.push_back(joint);
	weights.push_back(weight);
}

std::vector<float>* vertex::getVertex() {
	return &positions;
}

std::vector<float>* vertex::getNormal() {
	return &normals;
}

std::vector<int>* vertex::getJoints() {
	return &joints;
}

std::vector<float>* vertex::getWeights() {
	return &weights;
}