#ifndef _DOF_H_
#define _DOF_H_

class DOF
{
private:
	float value;
	float min;
	float max;

public:
	DOF();
	DOF(float value, float min, float max);
	void setValue(float input);
	float getValue();
	float * getValueAddr();
	void setMinMax(float max_input, float min_input);
	float getMin();
	float getMax();
};

#endif