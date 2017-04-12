#include "header.h"
#include "templates.h"

#include "AutomatedBall.h"
#include "Psyzl2Engine.h"


AutomatedBall::AutomatedBall(Psyzl2Engine* pEngine, double pM, int pR, int pColor, double pPower, int pX, int pY)
	:BallOnTable(pEngine, pM, pR, pColor, pX, pY),
	m_power(pPower)
{
	ImageData im2;
	im2.LoadImage("cat.jpg");
	im.ShrinkFrom(&im2, 10);
}


AutomatedBall::~AutomatedBall()
{
}


void AutomatedBall::accelerationMethod(int timeInterval)
{
	double mouseX = GetEngine()->GetCurrentMouseX();
	double mouseY = GetEngine()->GetCurrentMouseY();

	double disOfObAndMouseX = mouseX - m_iCurrentScreenX;
	double disOfObAndMouseY = mouseY - m_iCurrentScreenY;

	double angleOfA = SDL_atan2(disOfObAndMouseY, disOfObAndMouseX);

	if (m_angle == 8) {
		m_speed = 1;
		m_angle = angleOfA;
	}

	int i;
	double f, a;
	double speedInX;
	double speedInY;
	for (i = 0; i < timeInterval * 1; i++){
		f = m_power / m_speed;
		a = f / m_m;
		if (a > -0.1 && a < 0.1){
			speedInX = m_speed * SDL_cos(m_angle) + a * SDL_cos(angleOfA) * timeInterval / 1000 / 10 * (timeInterval * 10 - i);
			speedInY = m_speed * SDL_sin(m_angle) + a * SDL_sin(angleOfA) * timeInterval / 1000 / 10 * (timeInterval * 10 - i);
			break;
		}
		speedInX = m_speed * SDL_cos(m_angle) + a * SDL_cos(angleOfA) * timeInterval / 1000;
		speedInY = m_speed * SDL_sin(m_angle) + a * SDL_sin(angleOfA) * timeInterval / 1000;
	}
	//printf("a = %f angleOfA = %f", a, angleOfA);
	m_angle = SDL_atan2(speedInY, speedInX);
	m_speed = SDL_sqrt(speedInX * speedInX + speedInY * speedInY) - m_friction * timeInterval / m_m / 1000;
	//printf("angle = %f apeed = %f\n", m_angle, m_speed);

	double max_speed = m_power / m_friction;
	if (m_speed > max_speed) {
		m_speed = max_speed;
	}
	else if (m_speed < 0) {
		correctAngle(m_angle - M_PI);
	}
}
