#include "Keyframe.hpp"
Keyframe::Keyframe(float Time, float Value, int RuleIn, int RuleOut) {
	this->Time = Time;
	this->Value = Value;
	this->RuleIn = RuleIn;
	this->RuleOut = RuleOut;
}
float Keyframe::getTime() {
	return Time;
}
float Keyframe::getValue() {
	return Value;
}
void Keyframe::setTangentIn(float TangentIn) {
	this->TangentIn = TangentIn;
}
void Keyframe::setTangentOut(float TangentOut) {
	this->TangentOut = TangentOut;
}
float Keyframe::getTangentIn() {
	return TangentIn;
}
float Keyframe::getTangentOut() {
	return TangentOut;
}
int Keyframe::getRuleIn() {
	return RuleIn;
}
int Keyframe::getRuleOut() {
	return RuleOut;
}
void Keyframe::setABCD(float a, float b, float c, float d) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}
float Keyframe::getA() {
	return a;
}
float Keyframe::getB() {
	return b;
}
float Keyframe::getC() {
	return c;
}
float Keyframe::getD() {
	return d;
}