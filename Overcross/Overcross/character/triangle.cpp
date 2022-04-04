#include "triangle.hpp"

triangle::triangle(int a, int b, int c) {
	positions = { a, b, c };
}


std::vector<int>* triangle::getTriangle() {
	return &positions;
}