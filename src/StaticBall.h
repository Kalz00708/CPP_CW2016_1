#pragma once
#include "BallOnTable.h"
class StaticBall :
	public BallOnTable
{
public:
	StaticBall(Psyzl2Engine* pEngine, double pM, int pR, int pColor, int pX, int pY);
	~StaticBall();
	void accelerationMethod(int timeInterval);
};

