#pragma once
#include "BallOnTable.h"
class AutomatedBall :
	public BallOnTable
{
public:
	AutomatedBall(Psyzl2Engine* pEngine, double pM, int pR, int pColor, double pPower, int pX, int pY);
	~AutomatedBall();
private:
	double m_power;
public:
	void accelerationMethod(int timeInterval);
};

