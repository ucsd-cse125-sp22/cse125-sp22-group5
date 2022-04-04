#ifndef _SKELETON_H_
#define _SKELETON_H_

#include <GL/glew.h>
#include "DOF.hpp"
#include "Cube.hpp"
#include "Joint.hpp"
#include "Tokenizer.hpp"

class Skeleton
{
private:
	Joint* root;
	std::vector<Joint*> jointList;
	bool hasSkel;

public:
	Skeleton();
	~Skeleton();
	void Update();
	bool Load(const char* file);
	void Draw(const glm::mat4& viewProjMtx, GLuint shader);
	Joint* getRoot();
	glm::mat4 getWorldMatrix(int joint);
	std::vector<Joint*>* getJointList();
};

#endif
