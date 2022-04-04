#include "base_character.hpp"

base_character::base_character(skin* s, glm::vec3 f, glm::vec3 u, glm::vec3 p)
{
	this->mySkin = s;
	this->face = glm::normalize(f);
	this->up = glm::normalize(u);
	this->pos = p;
}

base_character::~base_character()
{
	delete mySkin;
}

void base_character::update()
{
	glm::mat4 newModel = glm::mat4(1);
	newModel = glm::translate(newModel, this->pos);
	mySkin->setModel(newModel);
	this->mySkin->update();
}

void base_character::draw(const glm::mat4& viewProjMtx, GLuint shader)
{
	this->mySkin->draw(viewProjMtx, shader);
}

void base_character::changeFace(glm::vec3 f)
{
	this->face = glm::normalize(f);
}

void base_character::changeUp(glm::vec3 u)
{
	this->up = glm::normalize(u);
}

void base_character::changePos(glm::vec3 p)
{
	this->pos = p;
}

glm::vec3 base_character::getFace()
{
	return this->face;
}

glm::vec3 base_character::getUp()
{
	return this->up;
}

glm::vec3 base_character::getPos()
{
	return this->pos;
}
