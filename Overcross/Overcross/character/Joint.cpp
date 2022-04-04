#include "Joint.hpp"

Joint::Joint() {
	freedom = { new DOF(), new DOF(), new DOF() };
}

Joint::~Joint() {
	delete freedom[0];
	delete freedom[1];
	delete freedom[2];
	delete box;
	for (int i = 0; i < children.size(); i++) {
		delete children[i];
	}
}

void Joint::Update(glm::mat4& C) {
	
	glm::mat4 Rx = glm::mat4(1);
	float x = freedom[0]->getValue();
	Rx[1] = glm::vec4(0, cos(x), sin(x), 0);
	Rx[2] = glm::vec4(0, -sin(x), cos(x), 0);

	glm::mat4 Ry = glm::mat4(1);
	float y = freedom[1]->getValue();
	Ry[0] = glm::vec4(cos(y), 0, -sin(y), 0);
	Ry[2] = glm::vec4(sin(y), 0, cos(y), 0);

	glm::mat4 Rz = glm::mat4(1);
	float z = freedom[2]->getValue();

	Rz[0] = glm::vec4(cos(z), sin(z), 0, 0);
	Rz[1] = glm::vec4(-sin(z), cos(z), 0, 0);

	transform[3] = glm::vec4(Offset, 1.0);

	Local = transform * Rz * Ry * Rx * glm::mat4(1);
	World = C * Local;

	box->update(World);

	for (int i = 0; i < children.size(); i++) {
		children[i]->Update(World);
	}
}

bool Joint::Load(Tokenizer& t, std::vector<Joint*>* jointList) {
	char temp[256];
	t.GetToken(temp);
	this->name = temp;

	t.FindToken("{");
	while (1) {
		t.GetToken(temp);
		if (strcmp(temp, "offset") == 0) {
			Offset.x = t.GetFloat();
			Offset.y = t.GetFloat();
			Offset.z = t.GetFloat();
		}
		else if (strcmp(temp, "boxmin") == 0) {
			box_min.x = t.GetFloat();
			box_min.y = t.GetFloat();
			box_min.z = t.GetFloat();
		}
		else if (strcmp(temp, "boxmax") == 0) {
			box_max.x = t.GetFloat();
			box_max.y = t.GetFloat();
			box_max.z = t.GetFloat();
		}
		else if (strcmp(temp, "rotxlimit") == 0) {
			freedom[0]->setMinMax(t.GetFloat(), t.GetFloat());
		}
		else if (strcmp(temp, "rotylimit") == 0) {
			freedom[1]->setMinMax(t.GetFloat(), t.GetFloat());
		}
		else if (strcmp(temp, "rotzlimit") == 0) {
			freedom[2]->setMinMax(t.GetFloat(), t.GetFloat());
		}
		else if (strcmp(temp, "pose") == 0) {
			freedom[0]->setValue(t.GetFloat());
			freedom[1]->setValue(t.GetFloat());
			freedom[2]->setValue(t.GetFloat());
		}
		else if (strcmp(temp, "balljoint") == 0) {
			Joint* jnt = new Joint();
			jointList->push_back(jnt);
			jnt->Load(t, jointList);
			this->addChild(jnt);
		}
		else if (strcmp(temp, "}") == 0) {
			transform[3] = glm::vec4(Offset, 1.0);
			box = new Cube(box_min, box_max);
			return true;
		}
		else t.SkipLine(); // Unrecognized token
	}
}

void Joint::addChild(Joint* child) {
	children.push_back(child);
}

void Joint::Draw(const glm::mat4& viewProjMtx, GLuint shader) {

	box->draw(viewProjMtx, shader);
	for (int i = 0; i < children.size(); i++) {
		children[i]->Draw(viewProjMtx, shader);;
	}
}

std::string Joint::getName() {
	return name;
}

std::vector<Joint*> Joint::getChildren() {
	return children;
}

std::vector<DOF*> Joint::getFreedom() {
	return freedom;
}

glm::mat4 Joint::getWorld() {
	return World;
}

void Joint::setOffset(glm::vec3 offset) {
	this->Offset = offset;
}

void Joint::setFreedom(glm::vec3 DOFs) {
	freedom[0]->setValue(DOFs.x);
	freedom[1]->setValue(DOFs.y);
	freedom[2]->setValue(DOFs.z);
}