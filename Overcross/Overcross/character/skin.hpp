#ifndef _SKIN_H_
#define _SKIN_H_

#include "triangle.hpp"
#include "Skeleton.hpp"

class skin
{
private:

	GLuint VAO;
	GLuint VBO_positions, VBO_normals, EBO;

	glm::mat4 model;
	glm::vec3 color;

	bool hasSkel;

	std::vector<vertex*> vertexs;
	std::vector<triangle*> triangles;
	Skeleton* skeleton;
	std::vector<glm::mat4*> bindings;
	std::vector<glm::mat4*> skinMatrix;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
public:
	skin(Skeleton* s, bool hasSkel);
	~skin();
	bool load(const char* file);
	void setModel(glm::mat4 m);
	void update();
	void draw(const glm::mat4& viewProjMtx, GLuint shader);
};
#endif
