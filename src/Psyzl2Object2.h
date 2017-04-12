#pragma once
#include "DisplayableObject.h"

class Psyzl2Engine;

class Psyzl2Object2 :
	public DisplayableObject
{
public:
	Psyzl2Object2(Psyzl2Engine* pEngine, double p_friction);
	~Psyzl2Object2();
private:
	int time;
	int pX;
	int pY;
	double speed;
	double angle;
	double friction;
	double r;
	Psyzl2Engine* m_pMainEngine;
public:
	void Draw();
	void DoUpdate(int iCurrentTime);
};

