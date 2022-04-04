#ifndef _BASECHARACTER_H_
#define _BASECHARACTER_H_

#include <vector>
#include "skin.hpp"

class base_character {
private:
	skin* mySkin;
	glm::vec3 face;
	glm::vec3 up;
	glm::vec3 pos;
public:
	base_character(skin* s, glm::vec3 f, glm::vec3 u, glm::vec3 p);
	~base_character();
	void update();
	void draw(const glm::mat4& viewProjMtx, GLuint shader);
	void changeFace(glm::vec3 f);
	void changeUp(glm::vec3 u);
	void changePos(glm::vec3 p);
	glm::vec3 getFace();
	glm::vec3 getUp();
	glm::vec3 getPos();
};

#endif