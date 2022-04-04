#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <vector>

class vertex
{
private:
	std::vector<float> positions;
	std::vector<float> normals;
	std::vector<int> joints;
	std::vector<float> weights;
public:
	vertex(float a, float b, float c);
	void setNormal(float a, float b, float c);
	void addBind(int joint, float weight);
	std::vector<float>* getVertex();
	std::vector<float>* getNormal();
	std::vector<int>* getJoints();
	std::vector<float>* getWeights();
};
#endif

