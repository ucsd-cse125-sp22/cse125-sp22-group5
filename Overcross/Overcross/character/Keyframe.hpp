#ifndef _KEYFRAME_H_
#define _KEYFRAME_H_

class Keyframe 
{
private:
	float Time;
	float Value;
	float TangentIn, TangentOut;
	int RuleIn, RuleOut;
	float a, b, c, d;
public:
	Keyframe(float Time, float Value, int RuleIn, int RuleOut);
	float getTime();
	float getValue();
	void setTangentIn(float TangentIn);
	void setTangentOut(float TangentOut);
	float getTangentIn();
	float getTangentOut();
	int getRuleIn();
	int getRuleOut();
	void setABCD(float a, float b, float c, float d);
	float getA();
	float getB();
	float getC();
	float getD();
};
#endif