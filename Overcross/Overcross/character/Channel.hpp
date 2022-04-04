#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include <vector>
#include <iostream>
#include <string>
#include "Keyframe.hpp"
#include "Tokenizer.hpp"

class Channel
{
private:
	std::vector<Keyframe*> keyframes;
	int extrapolateIn, extrapolateOut;
public:
	Channel();
	~Channel();
	bool load(Tokenizer& t);
	float Evaluate(float time);
};
#endif
