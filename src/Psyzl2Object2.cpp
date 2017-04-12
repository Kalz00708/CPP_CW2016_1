#include "header.h"
#include "templates.h"

#include "Psyzl2Object1.h"
#include "Psyzl2Object2.h"
#include "Psyzl2Engine.h"


Psyzl2Object2::Psyzl2Object2(Psyzl2Engine* pEngine, double p_friction)
	:DisplayableObject(pEngine),
	m_pMainEngine(pEngine),
	time(0),
	speed(0),
	angle(8),
	r(25),
	friction(p_friction)
{
	m_iCurrentScreenX = m_iPreviousScreenX = GetEngine()->GetScreenWidth() / 2;
	m_iCurrentScreenY = m_iPreviousScreenY = GetEngine()->GetScreenHeight() / 2;

	m_iDrawWidth = 2 * r;
	m_iDrawHeight = 2 * r;

	m_iStartDrawPosX = -r;
	m_iStartDrawPosY = -r;
}


Psyzl2Object2::~Psyzl2Object2()
{
}


void Psyzl2Object2::Draw()
{
	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX + m_iStartDrawPosX,
		m_iCurrentScreenY + m_iStartDrawPosY,
		m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight - 1,
		0xB000B0);

	StoreLastScreenPositionForUndraw();
}


void Psyzl2Object2::DoUpdate(int iCurrentTime)
{
	/*Psyzl2Object1* ob = m_pMainEngine;
	bool isHit = false;
	double additionTime = 0;
	double obX = ob->getX();
	double obY = ob->getY();
	double disInX = m_iCurrentScreenX - obX;
	double disInY = m_iCurrentScreenY - obY;
	double pDisInX = pX - obX;
	double pDisInY = pY - obY;
	double dis = SDL_sqrt(disInX * disInX + disInY * disInY);
	double sumOfR = r + ob->getR();

	if (m_iCurrentScreenX - pX != 0){
		double k = (m_iCurrentScreenY - pY) / (m_iCurrentScreenX - pX);
		double t = m_iCurrentScreenY - k * m_iCurrentScreenX;
		double disToLine = SDL_abs(k * obX - obY + t) / SDL_sqrt(k * k + 1);
		//printf("disToLine:%f sumOdR:%f dis:%f\n", disToLine, sumOfR, dis);
		if (disToLine < sumOfR && (dis < sumOfR || disInX * pDisInX < 0 || disInY * pDisInY < 0)) {
			//printf("get\n");
			double alpha = SDL_asin(disToLine / sumOfR);
			double beta;
			if (alpha < M_PI / 2) {
				beta = angle - alpha;
			}
			else if (alpha < M_PI) {
				beta = angle + alpha;
			}
			else if (alpha < M_PI * 1.5) {
				beta = angle - alpha - M_PI;
			}
			else {
				beta = alpha + angle - M_PI;
			}
			double k2 = SDL_sin(beta) / SDL_cos(beta);
			double t2 = obY - k2 * obX;
			printf("k = %f t = %f k2 = %f t2 = %f\n", k, t, k2, t2);
			double posX = (t - t2) / (k2 - k);
			double posY = k * posX + t;
			double additionDisInX = m_iCurrentScreenX - posX;
			double additionDisInY = m_iCurrentScreenY - posY;
			additionTime = SDL_sqrt(additionDisInX * additionDisInX + additionDisInY * additionDisInY) / speed;
			m_iCurrentScreenX = posX;
			m_iCurrentScreenY = posY;
			disInX = m_iCurrentScreenX - obX;
			disInY = m_iCurrentScreenY - obY;
			dis = SDL_sqrt(disInX * disInX + disInY * disInY);
			isHit = true;
		}
	}
	else if (obX == pX && (dis < sumOfR || disInY * pDisInY < 0)){
		double posY;
		if (pY < obY) {
			posY = obY - sumOfR;
		}
		else {
			posY = obY + sumOfR;
		}
		double additionDisInY = SDL_abs(m_iCurrentScreenY - posY);
		additionTime = additionDisInY / speed;
		m_iCurrentScreenY = posY;
		disInY = m_iCurrentScreenY - obY;
		dis = SDL_sqrt(disInX * disInX + disInY * disInY);
		isHit = true;
	}
	pX = m_iCurrentScreenX;
	pY = m_iCurrentScreenY;

	if (dis < sumOfR){
		isHit = true;
	}

	if (isHit) {
		double tempAngle;
		if (disInX == 0){
			tempAngle = M_PI / 2;
		}
		else {
			tempAngle = SDL_atan2(disInY, disInX);
		}
		if (ob->getAngle() != 8){
			double tempSpeed = ob->getSpeed() * SDL_cos(tempAngle - ob->getAngle());
			if (angle == 8){
				angle = tempAngle;
				speed = tempSpeed;
				//printf("%f %f\n", angle, speed);
			}
			else {
				double speedInX = speed * SDL_cos(angle) + tempSpeed * SDL_cos(tempAngle);
				double speedInY = speed * SDL_sin(angle) + tempSpeed * SDL_sin(tempAngle);
				angle = SDL_atan2(speedInY, speedInX);
				speed = speedInY / SDL_sin(angle);
				//printf("%f %f\n", angle, speed);
			}
		}
		else if (angle != 8) {
			angle = M_PI - angle + 2 * tempAngle;
		}

		if (angle != 8){
			m_iCurrentScreenX += (sumOfR - dis) * SDL_cos(angle);
			m_iCurrentScreenY += (sumOfR - dis) * SDL_sin(angle);
		}
	}

	int prevTime = time;
	time = iCurrentTime;
	int disOfTime = time - prevTime;
	speed += friction * disOfTime / 1000;
	if (speed < 0){
		speed = 0;
		angle = 8;
	}

	m_iCurrentScreenX += speed * SDL_cos(angle) * (disOfTime + additionTime ) / 1000;
	m_iCurrentScreenY += speed * SDL_sin(angle) * (disOfTime + additionTime ) / 1000;
	//printf("over %f %f\n", angle, speed);

	//m_iCurrentScreenX += speed * SDL_cos(angle);
	//m_iCurrentScreenY += speed * SDL_sin(angle);

	/*
	double tempX = m_iCurrentScreenX + speed * SDL_cos(angle) * disOfTime / 1000;
	double tempY = m_iCurrentScreenY + speed * SDL_sin(angle) * disOfTime / 1000;
	double newDisInX = tempX - obX;
	double newDisInY = tempY - obY;
	double k = (tempY - m_iCurrentScreenY) / (tempX - m_iCurrentScreenX);
	double t = tempY - k * tempX;
	double disToLine = SDL_abs(k * obX - obY + t) / SDL_sqrt(k * k + 1);
	if (disToLine < sumOfR && (newDisInX * disInX < 0 || newDisInY * disInY < 0)) {
		double alpha = SDL_asin(disToLine / sumOfR);
		double beta;
		if (alpha < M_PI / 2) {
			beta = angle - alpha;
		}
		else if (alpha < M_PI) {
			beta = angle + alpha;
		}
		else if (alpha < M_PI * 1.5) {
			beta = angle - alpha - M_PI;
		}
		else {
			beta = alpha + angle - M_PI;
		}
		double k2 = SDL_sin(beta) / SDL_cos(beta);
		double t2 = obY - k2 * obX;
		double posX = (t - t2) / (k2 - k);
		double posY = k * posX + t;
		double disInX = posX - obX;
		double disInY = posY - obY;
		double tempAngle = SDL_atan2(disInY, disInX);
		double tempSpeed = ob->getSpeed() * SDL_cos(tempAngle - ob->getAngle());
		double speedInX = speed * SDL_cos(angle) + tempSpeed * SDL_cos(tempAngle);
		double speedInY = speed * SDL_sin(angle) + tempSpeed * SDL_sin(tempAngle);
		angle = SDL_atan2(speedInY, speedInX);
		speed = speedInY / SDL_sin(angle);
		m_iCurrentScreenX += speed * SDL_cos(angle) * disOfTime / 1000;
		m_iCurrentScreenY += speed * SDL_sin(angle) * disOfTime / 1000;
		printf("over %f %f\n", angle, speed);
	}
	else {
		m_iCurrentScreenX = tempX;
		m_iCurrentScreenY = tempY;
	}
	*/


	if (m_iCurrentScreenX + m_iStartDrawPosX < 0) {
		m_iCurrentScreenX = -m_iStartDrawPosX;
		angle = M_PI - angle;
	}
	if (m_iCurrentScreenX + m_iStartDrawPosX > GetEngine()->GetScreenWidth() - m_iDrawWidth){
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth - m_iStartDrawPosX;
		angle = M_PI - angle;
	}
	if (m_iCurrentScreenY + m_iStartDrawPosY < 0) {
		m_iCurrentScreenY = -m_iStartDrawPosY;
		angle = 2 * M_PI - angle;
	}
	if (m_iCurrentScreenY + m_iStartDrawPosY > GetEngine()->GetScreenHeight() - m_iDrawHeight){
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight - m_iStartDrawPosY;
		angle = 2 * M_PI - angle;
	}

	RedrawObjects();
}
