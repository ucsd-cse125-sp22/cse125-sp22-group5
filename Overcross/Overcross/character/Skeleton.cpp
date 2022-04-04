#include "Skeleton.hpp"

Skeleton::Skeleton() {
	jointList = {};
	hasSkel = false;
}
Skeleton::~Skeleton() {
	if (root != nullptr) {
		delete root;
	}
}

void Skeleton::Update() {
	if (root != nullptr) {
		glm::mat4 temp = glm::mat4(1);
		root->Update(temp);
	}
}

bool Skeleton::Load(const char* file) {

	hasSkel = true;
	Tokenizer token;
	token.Open(file);
	token.FindToken("balljoint");
	// Parse tree
	root = new Joint;
	jointList.push_back(root);
	root->Load(token, &jointList);
	// Finish
	token.Close();

	return true;

}

void Skeleton::Draw(const glm::mat4& viewProjMtx, GLuint shader) {
	if (root != nullptr) {
		root->Draw(viewProjMtx, shader);
	}
}

Joint* Skeleton::getRoot() {
	return root;
}

glm::mat4 Skeleton::getWorldMatrix(int joint) {
	if (!hasSkel) {	
		return glm::mat4(1);
	}
	return jointList[joint]->getWorld();
}

std::vector<Joint*>* Skeleton::getJointList() {
	return &jointList;
}