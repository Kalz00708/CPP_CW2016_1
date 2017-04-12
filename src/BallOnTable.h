#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
class Psyzl2Engine;

class BallOnTable :
	public DisplayableObject
{
public:
	BallOnTable(Psyzl2Engine* pEngine, double pM, int pR, int pColor, int pX, int pY);
	~BallOnTable();
	bool collisionCorrect(DisplayableObject* ob);
	virtual void accelerationMethod(int timeInterval);
	void Draw();
	void DoUpdate(int iCurrentTime);
	double correctAngle(double objectAngle);
	inline void setAngle(double angle){
		m_angle = angle;
	}
	inline void setSpeed(double speed){
		m_speed = speed;
	}
	inline void setTime(int time) {
		m_time = time;
	}
	static int counter;

protected:
	int m_time;
	double m_pX;
	double m_pY;
	double m_cX;
	double m_cY;
	double m_speed;
	double m_angle;
	double m_friction;
	double m_m;
	int m_r;
	int m_color;
	ImageData im;
	Psyzl2Engine* m_pMainEngine;
};

