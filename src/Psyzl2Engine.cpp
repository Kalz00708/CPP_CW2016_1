#include "header.h"
#include "templates.h"

#include "Psyzl2Engine.h"
#include "Psyzl2Object1.h"
#include "Psyzl2Object2.h"
#include "AutomatedBall.h"
#include "StaticBall.h"

#include <string>
using namespace std;


Psyzl2Engine::Psyzl2Engine()
	:BaseEngine(3),
	m_coefficientOfFriction(0.1)
{
}


Psyzl2Engine::~Psyzl2Engine()
{
}


void Psyzl2Engine::SetupBackgroundBuffer()
{
	FillBackground(0xFFFFFF);
	DrawBackgroundIcon(600, 350);
	DrawBackgroundIcon(10, 10);

	m_oTiles.SetSize(7, 7);
	for (int x = 0; x < 7; x++)
		for (int y = 0; y < 7; y++)
			m_oTiles.SetValue(x, y, rand() % 41);

	m_oTiles.SetBaseTilesPositionOnScreen(330, 220);
	m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 6, 6);
}


void Psyzl2Engine::DrawBackgroundIcon(double pointOfX, double pointOfY)
{
	double xOfMainBuilding[24] = { 22, 50, 50, 64, 64, 103, 103, 144, 144, 131, 91, 95, 85, 85, 91, 91, 70, 41, 26, 21, 21, 31, 33, 22 };
	double yOfMainBuilding[24] = { 16, 4, 27, 24, 0, 0, 26, 37, 68, 78, 73, 58, 72, 128, 136, 176, 167, 167, 173, 170, 138, 130, 74, 65 };
	moveArray(24, xOfMainBuilding, pointOfX);
	moveArray(24, yOfMainBuilding, pointOfY);
	DrawBackgroundPolygon(24, xOfMainBuilding, yOfMainBuilding, 0x073362);
	double xOfRightTop[4] = { 118, 144, 144, 118 };
	double yOfRightTop[4] = { 4, 15, 34, 26 };
	moveArray(4, xOfRightTop, pointOfX);
	moveArray(4, yOfRightTop, pointOfY);
	DrawBackgroundPolygon(4, xOfRightTop, yOfRightTop, 0x073362);
	double xOfLeftWindow[6] = { 51, 53, 57, 59, 62, 50 };
	double yOFLeftWindow[6] = { 83, 80, 80, 83, 125, 125 };
	moveArray(6, xOfLeftWindow, pointOfX);
	moveArray(6, yOFLeftWindow, pointOfY);
	DrawBackgroundPolygon(6, xOfLeftWindow, yOFLeftWindow, 0xFFFFFF);
	double xOfRightWindow[6] = { 105, 107, 111, 113, 116, 104 };
	double yOFRightWindow[6] = { 83, 80, 80, 83, 125, 125 };
	moveArray(6, xOfRightWindow, pointOfX);
	moveArray(6, yOFRightWindow, pointOfY);
	DrawBackgroundPolygon(6, xOfRightWindow, yOFRightWindow, 0x073362);
	double xOfBottom[6] = { 0, 45, 114, 152, 110, 45 };
	double yOfBottom[6] = { 198, 172, 192, 180, 203, 185 };
	moveArray(6, xOfBottom, pointOfX);
	moveArray(6, yOfBottom, pointOfY);
	DrawBackgroundPolygon(6, xOfBottom, yOfBottom, 0x073362);
}


void Psyzl2Engine::moveArray(int arraySize, double* pArray, double move)
{
	for (int i = 0; i < arraySize; i++)
	{
		*pArray += move;
		pArray++;
	}
}


int Psyzl2Engine::InitialiseObjects()
{
	DrawableObjectsChanged();

	DestroyOldObjects();

	CreateObjectArray(6);

	StoreObjectInArray(0, new AutomatedBall(this, 100, 10, 0xB000B0, 100000, 100, 100));
	StoreObjectInArray(1, new StaticBall(this, 4, 10, 0x000000, 200, 200));
	StoreObjectInArray(2, new StaticBall(this, 2, 10, 0x000000, 220, 220));
	StoreObjectInArray(3, new StaticBall(this, 1, 10, 0x000000, 240, 240));
	StoreObjectInArray(4, new StaticBall(this, 1, 10, 0x000000, 260, 260));
	StoreObjectInArray(5, NULL);
	m_numOfBall = 5;

	return 0;
}


void Psyzl2Engine::DrawStrings()
{
	string s = to_string(GetTime());
	CopyBackgroundPixels(0/*X*/, 0/*Y*/, GetScreenWidth(), 100/*Height*/);
	DrawScreenString(360, 40, s.c_str(), 0x0, NULL);
}
