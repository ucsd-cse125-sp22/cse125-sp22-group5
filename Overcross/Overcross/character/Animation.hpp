#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <vector>
#include "Keyframe.hpp"
#include "Channel.hpp"
#include "Tokenizer.hpp"
#include "Skeleton.hpp"

class Animation
{
private:
	std::vector<Channel*> channels;
	Skeleton* skeleton;
	float start, end;
public:
	Animation(Skeleton * skeleton);
	~Animation();
	bool load(const char* file);
	void eval(float time);
	void play(float time);
};
#endif
