#include "header.h"
#include "templates.h"

#include "Psyzl2Object1.h"
#include "Psyzl2Engine.h"


Psyzl2Object1::Psyzl2Object1(Psyzl2Engine* pEngine, double p_speed, double p_r)
	:DisplayableObject(pEngine), 
	time(0),
	speed(p_speed),
	angle(8),
	r(p_r)
{
	m_iCurrentScreenX = m_iPreviousScreenX = r;
	m_iCurrentScreenY = m_iPreviousScreenY = r;

	m_iDrawWidth = 2 * r;
	m_iDrawHeight = 2 * r;

	m_iStartDrawPosX = -r;
	m_iStartDrawPosY = -r;
}


Psyzl2Object1::~Psyzl2Object1()
{
}


void Psyzl2Object1::Draw()
{
	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX + m_iStartDrawPosX, 
		m_iCurrentScreenY + m_iStartDrawPosY,
		m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight - 1,
		0x00ff00);

	StoreLastScreenPositionForUndraw();
}


void Psyzl2Object1::DoUpdate(int iCurrentTime)
{
	int prevTime = time;
	time = iCurrentTime;
	int disOfTime = time - prevTime;

	double mouseX = GetEngine()->GetCurrentMouseX();
	double mouseY = GetEngine()->GetCurrentMouseY();

	double disOfObAndMouseX = mouseX - m_iCurrentScreenX;
	double disOfObAndMouseY = mouseY - m_iCurrentScreenY;

	double disInLine = SDL_sqrt(disOfObAndMouseX * disOfObAndMouseX + disOfObAndMouseY * disOfObAndMouseY);

	if (disInLine < 4){
		m_iCurrentScreenX = mouseX;
		m_iCurrentScreenY = mouseY;
		angle = 8;
	}
	else {
		angle = SDL_atan2(disOfObAndMouseY, disOfObAndMouseX);
		double moveX = speed * disOfObAndMouseX * disOfTime / (disInLine * 1000);
		double moveY = speed * disOfObAndMouseY * disOfTime / (disInLine * 1000);
		m_iCurrentScreenX += moveX;
		m_iCurrentScreenY += moveY;
	}

	if (m_iCurrentScreenX + m_iStartDrawPosX < 0) {
		m_iCurrentScreenX = -m_iStartDrawPosX;
	}
	if (m_iCurrentScreenX + m_iStartDrawPosX > GetEngine()->GetScreenWidth() - m_iDrawWidth){
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth - m_iStartDrawPosX;
	}
	if (m_iCurrentScreenY + m_iStartDrawPosY < 0) {
		m_iCurrentScreenY = -m_iStartDrawPosY;
	}
	if (m_iCurrentScreenY + m_iStartDrawPosY > GetEngine()->GetScreenHeight() - m_iDrawHeight){
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight - m_iStartDrawPosY;
	}

	RedrawObjects();
}
