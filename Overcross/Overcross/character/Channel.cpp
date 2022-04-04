#include "Channel.hpp"

Channel::Channel() {

}
Channel::~Channel() {
	for (int i = 0; i < keyframes.size(); i++) {
		delete keyframes[i];
	}
}
bool Channel::load(Tokenizer& t) {
	t.FindToken("channel");
	t.GetInt();
	t.FindToken("{");
	t.FindToken("extrapolate");

	char temp[256];
	t.GetToken(temp);
	if (strcmp(temp, "constant") == 0) {
		extrapolateIn = 0;
	}
	else if (strcmp(temp, "linear") == 0) {
		extrapolateIn = 1;
	}
	else if (strcmp(temp, "cycle") == 0) {
		extrapolateIn = 2;
	}
	else if (strcmp(temp, "cycle_offset") == 0) {
		extrapolateIn = 3;
	}
	else if (strcmp(temp, "bounce") == 0) {
		extrapolateIn = 4;
	}

	t.GetToken(temp);
	if (strcmp(temp, "constant") == 0) {
		extrapolateOut = 0;
	}
	else if (strcmp(temp, "linear") == 0) {
		extrapolateOut = 1;
	}
	else if (strcmp(temp, "cycle") == 0) {
		extrapolateOut = 2;
	}
	else if (strcmp(temp, "cycle_offset") == 0) {
		extrapolateOut = 3;
	}
	else if (strcmp(temp, "bounce") == 0) {
		extrapolateOut = 4;
	}
	
	t.FindToken("keys");
	int size = t.GetInt();
	t.FindToken("{");
	for (int i = 0; i < size; i++) {
		float time = t.GetFloat();
		float value = t.GetFloat();
		int ruleIn, ruleOut;
		std::string tangentIn, tangentOut;

		t.GetToken(temp);
		if (strcmp(temp, "flat") == 0) {
			ruleIn = 0;
		}
		else if (strcmp(temp, "linear") == 0) {
			ruleIn = 1;
		}
		else if (strcmp(temp, "smooth") == 0) {
			ruleIn = 2;
		}
		else {
			ruleIn = 3;
			tangentIn = temp;
		}

		t.GetToken(temp);
		if (strcmp(temp, "flat") == 0) {
			ruleOut = 0;
		}
		else if (strcmp(temp, "linear") == 0) {
			ruleOut = 1;
		}
		else if (strcmp(temp, "smooth") == 0) {
			ruleOut = 2;
		}
		else {
			ruleOut = 3;
			tangentOut = temp;
		}

		Keyframe* newKey = new Keyframe(time, value, ruleIn, ruleOut);
		if (ruleIn == 3) {
			newKey->setTangentIn(std::stof(tangentIn));
		}
		if (ruleOut == 3) {
			newKey->setTangentOut(std::stof(tangentOut));
		}
		keyframes.push_back(newKey);
	}
	t.FindToken("}");
	t.FindToken("}");
	
	for (int i = 0; i < keyframes.size(); i++) {
		if (keyframes[i]->getRuleIn() == 0) {
			keyframes[i]->setTangentIn(0);
		}
		else if (keyframes[i]->getRuleIn() == 1) {
			if (i == 0) {
				keyframes[i]->setTangentIn(0);
			}
			else {
				keyframes[i]->setTangentIn( (keyframes[i]->getValue() - keyframes[i-1]->getValue()) / (keyframes[i]->getTime() - keyframes[i - 1]->getTime()));
			}
		}
		else if (keyframes[i]->getRuleIn() == 2) {
			
			if (i == 0) {
				keyframes[i]->setTangentIn(0);
			}
			else if (i == keyframes.size() - 1) {
				keyframes[i]->setTangentIn((keyframes[i]->getValue() - keyframes[i - 1]->getValue()) / (keyframes[i]->getTime() - keyframes[i - 1]->getTime()));
			}
			else {
				keyframes[i]->setTangentIn((keyframes[i+1]->getValue() - keyframes[i - 1]->getValue()) / (keyframes[i+1]->getTime() - keyframes[i - 1]->getTime()));
			}
		}

		if (keyframes[i]->getRuleOut() == 0) {
			keyframes[i]->setTangentOut(0);
		}
		else if (keyframes[i]->getRuleOut() == 1) {
			if (i == keyframes.size() - 1) {

				keyframes[i]->setTangentOut(0);

			}
			else {
				keyframes[i]->setTangentOut((keyframes[i+1]->getValue() - keyframes[i]->getValue()) / (keyframes[i+1]->getTime() - keyframes[i]->getTime()));
			}
		}
		else if (keyframes[i]->getRuleOut() == 2) {
			if (i == keyframes.size() - 1) {
				keyframes[i]->setTangentOut(0);
			} else if (i == 0) {
				keyframes[i]->setTangentOut((keyframes[i + 1]->getValue() - keyframes[i]->getValue()) / (keyframes[i + 1]->getTime() - keyframes[i]->getTime()));
			}else {
				keyframes[i]->setTangentOut((keyframes[i + 1]->getValue() - keyframes[i - 1]->getValue()) / (keyframes[i + 1]->getTime() - keyframes[i - 1]->getTime()));
			}
		}
	}
	
	for (int i = 0; i < keyframes.size() - 1; i++) {
		float p1 = keyframes[i]->getValue();
		float p2 = keyframes[i+1]->getValue();
		float p3 = keyframes[i]->getTangentOut() * (keyframes[i+1]->getTime() - keyframes[i]->getTime());
		float p4 = keyframes[i+1]->getTangentIn() * (keyframes[i+1]->getTime() - keyframes[i]->getTime());
		keyframes[i]->setABCD(2 * p1 - 2* p2 + p3 + p4,
			-3 * p1 + 3 * p2 - 2 * p3 - p4,
			p3,
			p1);
	}
	
	return true;
}
float Channel::Evaluate(float time) {
	if (time < keyframes[0]->getTime()) {
		if (extrapolateIn == 0) {
			return keyframes[0]->getValue();
		}
		else if (extrapolateIn == 1) {
			return keyframes[0]->getValue() - (keyframes[0]->getTime() - time) * keyframes[0]->getTangentIn() ;
		}
		else if (extrapolateIn == 2) {
			return Evaluate(time + keyframes[keyframes.size() - 1]->getTime() - keyframes[0]->getTime());
		}
		else if (extrapolateIn == 3) {
			return Evaluate(time + keyframes[keyframes.size() - 1]->getTime() - keyframes[0]->getTime()) 
				- (keyframes[keyframes.size() - 1]->getValue() - keyframes[0]->getValue());
		}
		else {
			return Evaluate(2 * keyframes[0]->getTime() - time);
		}
	}
	else if (time > keyframes[keyframes.size() - 1]->getTime()) {
		if (extrapolateOut == 0) {
			return keyframes[keyframes.size() - 1]->getValue();
		}
		else if (extrapolateOut == 1) {
			return keyframes[keyframes.size() - 1]->getValue() + 
				(time - keyframes[keyframes.size() - 1]->getTime()) * keyframes[keyframes.size() - 1]->getTangentIn();
		}
		else if (extrapolateOut == 2) {
			return Evaluate(time - keyframes[keyframes.size() - 1]->getTime() + keyframes[0]->getTime());
		}
		else if (extrapolateOut == 3) {
			return Evaluate(time - keyframes[keyframes.size() - 1]->getTime() + keyframes[0]->getTime())
				+ keyframes[keyframes.size() - 1]->getValue() - keyframes[0]->getValue();
		}
		else {
			return Evaluate(2 * keyframes[keyframes.size() - 1]->getTime() - time);
		}
	}
	else {
		int wanted = 0;
		for (int i = 0; i < keyframes.size(); i++) {
			if (keyframes[i]->getTime() == time) {
				return keyframes[i]->getValue();
			}
			if (keyframes[i]->getTime() > time) {
				wanted = i - 1;
				break;
			}
		}

		float u = (time - keyframes[wanted]->getTime()) / (keyframes[wanted + 1]->getTime() - keyframes[wanted]->getTime());
		return u * u * u * keyframes[wanted]->getA() + u * u * keyframes[wanted]->getB() + 
			u * keyframes[wanted]->getC() + keyframes[wanted]->getD();
	}
}
