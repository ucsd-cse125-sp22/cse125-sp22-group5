#ifndef _JOINT_H_
#define _JOINT_H_

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "DOF.hpp"
#include "Cube.hpp"
#include "Tokenizer.hpp"

class Joint
{
private:
	std::string name;
	Joint * parent;
	std::vector<Joint *> children;
	std::vector<DOF *> freedom;
	glm::vec3 Offset = glm::vec3(0,0,0);
	glm::vec3 box_min = glm::vec3(-0.1, -0.1, -0.1);
	glm::vec3 box_max = glm::vec3(0.1, 0.1, 0.1);
	glm::mat4 Local = glm::mat4(1);
	glm::mat4 World = glm::mat4(1);
	glm::mat4 transform = glm::mat4(1);
	Cube * box;

public:
	Joint();
	~Joint();
	void Update(glm::mat4& C);
	bool Load(Tokenizer& t, std::vector<Joint*>* jointList);
	void addChild(Joint * child);
	void Draw(const glm::mat4& viewProjMtx, GLuint shader);
	std::string getName();
	std::vector<Joint*> getChildren();
	std::vector<DOF*> getFreedom();
	glm::mat4 getWorld();
	void setOffset(glm::vec3 offset);
	void setFreedom(glm::vec3 DOFs);
};

#endif