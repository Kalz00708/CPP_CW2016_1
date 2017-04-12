#include "header.h"
#include "templates.h"

#include "StaticBall.h"
#include "Psyzl2Engine.h"


StaticBall::StaticBall(Psyzl2Engine* pEngine, double pM, int pR, int pColor, int pX, int pY)
	:BallOnTable(pEngine, pM, pR, pColor, pX, pY)
{
	ImageData im2;
	im2.LoadImage("woolenBall.jpg");
	im.ShrinkFrom(&im2, 20);
}


StaticBall::~StaticBall()
{
}


void StaticBall::accelerationMethod(int timeInterval)
{
	if (m_angle != 8){
		m_speed -= m_friction / m_m * timeInterval / 1000;
		if (m_speed < 0) {
			m_speed = 0;
			m_angle = 8;
		}
	}
}
