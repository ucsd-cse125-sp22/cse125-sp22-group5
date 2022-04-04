#include "Animation.hpp"

Animation::Animation(Skeleton* skeleton) {
	this->skeleton = skeleton;
}
Animation::~Animation() {
	for (int i = 0; i < channels.size(); i++) {
		delete channels[i];
	}
}
bool Animation::load(const char* file) {
	
	Tokenizer token;
	token.Open(file);
	token.FindToken("animation");
	// Parse tree
	
	token.FindToken("{");
	token.FindToken("range");
	start = token.GetFloat();
	end = token.GetFloat();
	token.FindToken("numchannels");
	int size = token.GetInt();
	
	for (int i = 0; i < size; i++) {
		
		Channel* newChannel = new Channel();
		newChannel->load(token);
		channels.push_back(newChannel);
	}

	token.FindToken("}");
	// Finish
	token.Close();
	
	return true;
}
void Animation::eval(float time) {

	skeleton->getRoot()->setOffset( glm::vec3(channels[0]->Evaluate(time), channels[1]->Evaluate(time), channels[2]->Evaluate(time)));

	for (int i = 1; i < channels.size() / 3; i++) {
		(*(skeleton->getJointList()))[i - 1]->setFreedom(glm::vec3(channels[i*3]->Evaluate(time), channels[i*3+1]->Evaluate(time), channels[i*3+2]->Evaluate(time)));
	}
}

void Animation::play(float time) {
	if (time >= start&& time <= end) {
		eval(time);
	}
	else if (time < start) {
		play(time + end - start);
	}
	else {
		play(time - end + start);
	}
}
