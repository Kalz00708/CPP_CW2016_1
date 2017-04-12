#pragma once
#include "DisplayableObject.h"

class Psyzl2Engine;

class Psyzl2Object1 :
	public DisplayableObject
{
public:
	Psyzl2Object1(Psyzl2Engine* pEngine, double m_speed, double p_r);
	~Psyzl2Object1();
	void Draw();
	void DoUpdate(int iCurrentTime);

private:
	int time;
	double speed;
	double angle;
	double r;
public:

	double getX()
	{
		return m_iCurrentScreenX;
	}

	void setX(double x){
		m_iCurrentScreenX = x;
	}

	double getY()
	{
		return m_iCurrentScreenY;
	}

	void setY(double y){
		m_iCurrentScreenY = y;
	}

	double getSpeed(){
		return speed;
	}

	double getAngle(){
		return angle;
	}

	double getR(){
		return r;
	}
};

