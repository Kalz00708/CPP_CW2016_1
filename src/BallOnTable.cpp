#include "header.h"
#include "templates.h"
#include "JPGImage.h"

#include "BallOnTable.h"
#include "Psyzl2Engine.h"

#define TIMEINTERVAL 20


int BallOnTable::counter = 0;
BallOnTable::BallOnTable(Psyzl2Engine* pEngine, double pM, int pR, int pColor, int pX, int pY)
	:DisplayableObject(pEngine),
	m_pMainEngine(pEngine),
	m_time(TIMEINTERVAL),
	m_speed(0),
	m_angle(8),
	m_m(pM),
	m_r(pR),
	m_color(pColor)
{
	m_friction = m_m * m_pMainEngine->getCoefficient() * 9.8;

	m_cX = m_pX = m_iCurrentScreenX = pX;
	m_cY = m_pY = m_iCurrentScreenY = pY;

	m_iDrawWidth = 2 * m_r;
	m_iDrawHeight = 2 * m_r;

	m_iStartDrawPosX = -m_r;
	m_iStartDrawPosY = -m_r;
}


BallOnTable::~BallOnTable()
{
}


bool BallOnTable::collisionCorrect(DisplayableObject* ob)
{
	//double x = ob->GetXCentre();
	//double y = ob->GetYCentre();
	BallOnTable* ball = dynamic_cast<BallOnTable*>(ob);
	double x = ball->m_cX;
	double y = ball->m_cY;
	double sumOfR = m_r + ball->m_r;
	double xA, yA;
	if (m_pX == m_cX){
		if (m_pY < y){
			yA = y - sumOfR;
			if (m_cY < yA) {
				return false;
			}
		}
		else {
			yA = y + sumOfR;
			if (m_cY > yA) {
				return false;
			}
		}
		xA = m_cX;
	}
	else {
		double k = (m_cY - m_pY) / (m_cX - m_pX);
		double t = m_cY - k * m_cX;
		double a = 1 + k * k;
		double doubleA = 2 * a;
		double b = 2 * k * t - 2 * x - 2 * y * k;
		double c = x * x + t * t - 2 * y * t + y * y - sumOfR * sumOfR;
		double delta;
		if ((delta = b * b - 4 * a * c) > 0){
			double x1 = (-b + SDL_sqrt(delta)) / doubleA;
			double x2 = (-b - SDL_sqrt(delta)) / doubleA;
			if (SDL_abs(x1 - m_pX) < SDL_abs(x2 - m_pX)){
				xA = x1;
			}
			else {
				xA = x2;
			}
			if (SDL_sqrt((x - m_cX) * (x - m_cX) + (y - m_cY) * (y - m_cY)) > sumOfR) {
				return false;
			}
		}
		else if (delta == 0){
			xA = -b / doubleA;
		}
		else {
			printf("k = %f t = %f a = %f b = %f c = %f delta = %f\n", k, t, a, b, c, delta);
			//getchar();
			return false;
		}
		yA = k * xA + t;
	}
	printf("x = %f, y = %f, xA = %f, yA = %f\n", x, y, xA, yA);
	printf("dis = %f\n", SDL_sqrt((x - xA) * (x - xA) + (y - yA) * (y - yA)) );
	double additionDisInX = m_cX - xA;
	double additionDisInY = m_cY - yA;
	double additionTime = SDL_sqrt(additionDisInX * additionDisInX + additionDisInY * additionDisInY) / m_speed; 
	m_time = additionTime * 1000;
	if (m_time == 0) {
		counter++;
	}
	printf("%f %f\n", m_speed, additionTime);

	double angleOfCollision;
	if (x == xA) {
		if (y < yA) {
			angleOfCollision = -M_PI / 2;
		}
		else if (y > yA) {
			angleOfCollision = M_PI / 2;
		}
	}
	else {
		angleOfCollision = SDL_atan2(y - yA, x - xA);
	}
	if (ball->m_angle == 8){
		ball->m_angle = angleOfCollision;
	}
	printf("%f\n", angleOfCollision);

	double vInX = m_speed * SDL_cos(m_angle);
	double vInY = m_speed * SDL_sin(m_angle);
	double oVInX = ball->m_speed * SDL_cos(ball->m_angle);
	double oVInY = ball->m_speed * SDL_sin(ball->m_angle);
	double v1 = m_speed * SDL_cos(m_angle - angleOfCollision);
	double v2 = ball->m_speed * SDL_cos(ball->m_angle - angleOfCollision);

	double v1N = ((m_m - ball->m_m) * v1 + 2 * ball->m_m * v2) / (m_m + ball->m_m);
	double v2N = ((ball->m_m - m_m) * v2 + 2 * m_m * v1) / (m_m + ball->m_m);
	printf("v1N= %f v2N= %f\n", v1N, v2N);
	vInX += (v1N - v1) * SDL_cos(angleOfCollision);
	vInY += (v1N - v1) * SDL_sin(angleOfCollision);
	if (vInX == 0){
		if (vInY > 0) {
			m_angle = M_PI / 2;
		}
		else if (vInY < 0) {
			m_angle = -M_PI / 2;
		}
		else {
			m_angle = 8;
		}
	}
	else {
		m_angle = SDL_atan2(vInY, vInX);
	}
	m_speed = SDL_sqrt(vInX * vInX + vInY * vInY);
	oVInX += (v2N - v2) * SDL_cos(angleOfCollision);
	oVInY += (v2N - v2) * SDL_sin(angleOfCollision);
	double ballAngle;
	if (oVInX == 0){
		if (oVInY > 0) {
			ballAngle = M_PI / 2;
		}
		else if (oVInY < 0) {
			ballAngle = -M_PI / 2;
		}
		else {
			ballAngle = 8;
		}
	}
	else {
		ballAngle = SDL_atan2(oVInY, oVInX);
	}
	ball->setAngle(ballAngle);
	//ball->m_speed = SDL_sqrt(oVInX * oVInX + oVInY * oVInY);
	ball->setSpeed(SDL_sqrt(oVInX * oVInX + oVInY * oVInY));
	if (ball->m_time == 0) {
		counter--;
		ball->m_time = TIMEINTERVAL / 4;
	}
	printf("ball %lu %f %f\n", ball, ball->m_angle, ball->m_speed);
	printf("this %f %f\n", m_angle, m_speed);
	m_cX = m_pX = xA;
	m_cY = m_pY = yA;
	double addInX = SDL_cos(m_angle);
	double addInY = SDL_sin(m_angle);
	double angleOfBall;
	if (x == xA) {
		if (y < yA) {
			angleOfBall = -M_PI / 2;
		}
		else {
			angleOfBall = M_PI / 2;
		}
	}
	else {
		angleOfBall = SDL_atan2(y - yA, x - xA);
	}
	printf("%f\n", angleOfBall);
	bool sameDir;
	if (m_angle < correctAngle(angleOfBall + M_PI / 2) || m_angle > correctAngle(angleOfBall - M_PI / 2)) {
		sameDir = true;
	}
	else {
		sameDir = false;
	}
	double curdis = SDL_sqrt((x - m_cX) * (x - m_cX) + (y - m_cY) * (y - m_cY));
	do {
		//getchar();
		if (sameDir) {
			m_cX -= addInX;
			m_cY -= addInY;
		}
		else {
			m_cX += addInX;
			m_cY += addInY;
		}
		curdis++;
		printf("X = %f Y = %f dis = %f", m_cX, m_cY, curdis);
	} while (curdis <= sumOfR + 1);
	//m_cX = m_pX + m_speed * SDL_cos(m_angle) * m_time / 1000;
	//m_cY = m_pY + m_speed * SDL_sin(m_angle) * m_time / 1000;
	//m_time = 0;
	//counter++;
	printf("%f %f\n", m_cX, m_cY);
	printf("disAfter = %f\n", SDL_sqrt((x - m_cX) * (x - m_cX) + (y - m_cY) * (y - m_cY)));
	//getchar();
	return true;
}


void BallOnTable::accelerationMethod(int timeInterval)
{
}


void BallOnTable::Draw()
{
	im.RenderImageWithMask(this->GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX,
		m_iCurrentScreenY + m_iStartDrawPosY, m_r * 2, m_r * 2);
	StoreLastScreenPositionForUndraw();
}


void BallOnTable::DoUpdate(int iCurrentTime)
{
	int i;
	bool unfinish = true;
	printf("in\n");
	//getchar();
	if (BallOnTable::counter == m_pMainEngine->getNumOfBall()){
		BallOnTable::counter = 0;
		for (i = 0; unfinish; i++) {
			BallOnTable* pO = dynamic_cast<BallOnTable*>(GetEngine()->GetDisplayableObject(i));
			if (pO == NULL) {
				unfinish = false;
			}
			else {
				pO->setTime(TIMEINTERVAL);
			}
		}
	}
	else if (m_time == 0){
		return;
	}
	printf("before %ld %f %f\n", this, m_angle, m_speed);

	accelerationMethod(m_time);
	printf("after %ld %f %f\n", this, m_angle, m_speed);
	if (m_angle == 8){
		m_time = 0;
		BallOnTable::counter++;
		return;
	}

	m_pX = m_cX;
	m_pY = m_cY;
	m_cX += m_speed * SDL_cos(m_angle) * m_time / 1000;
	m_cY += m_speed * SDL_sin(m_angle) * m_time / 1000;
	
	unfinish = true;
	for (i = 0; unfinish; i++) {
		DisplayableObject* pO = GetEngine()->GetDisplayableObject(i);
		if (pO == NULL) {
			unfinish = false;
		}
		else if (pO != this){
			if ( collisionCorrect(pO)) {
				break;
			}
		}
	}

	if (!unfinish) {
		m_time = 0;
		BallOnTable::counter++;
	}
	printf("after Coll %ld %f %f\n", this, m_angle, m_speed);

	m_iCurrentScreenX = m_cX;
	m_iCurrentScreenY = m_cY;
	printf("%d %d %f %f\n\n", m_iCurrentScreenX, m_iCurrentScreenY, m_cX, m_cY);

	if (m_iCurrentScreenX + m_iStartDrawPosX < 0) {
		m_iCurrentScreenX = -m_iStartDrawPosX;
		m_angle = correctAngle(M_PI - m_angle);
	}
	if (m_iCurrentScreenX + m_iStartDrawPosX > GetEngine()->GetScreenWidth() - m_iDrawWidth){
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth - m_iStartDrawPosX;
		m_angle = correctAngle(M_PI - m_angle);
	}
	if (m_iCurrentScreenY + m_iStartDrawPosY < 0) {
		m_iCurrentScreenY = -m_iStartDrawPosY;
		m_angle = correctAngle(2 * M_PI - m_angle);
	}
	if (m_iCurrentScreenY + m_iStartDrawPosY > GetEngine()->GetScreenHeight() - m_iDrawHeight){
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight - m_iStartDrawPosY;
		m_angle = correctAngle(2 * M_PI - m_angle);
	}

	RedrawObjects();
}


double BallOnTable::correctAngle(double objectAngle)
{
	if (objectAngle < -M_PI) {
		objectAngle += 2 * M_PI;
	}
	else if (objectAngle > M_PI) {
		objectAngle -= 2 * M_PI;
	}
	return objectAngle;
}
