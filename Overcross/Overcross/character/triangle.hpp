#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "vertex.hpp"

class triangle
{
private:
	std::vector<int> positions;
public:
	triangle(int a, int b, int c);
	std::vector<int>* getTriangle();
};
#endif


