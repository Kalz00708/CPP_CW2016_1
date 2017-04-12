#pragma once
#include "BaseEngine.h"
#include "Psyzl2TileManager.h"
class Psyzl2Object1;

class Psyzl2Engine :
	public BaseEngine
{
public:
	Psyzl2Engine();
	~Psyzl2Engine();
	void SetupBackgroundBuffer();
	int InitialiseObjects();
	inline double getCoefficient(){
		return m_coefficientOfFriction;
	}
	inline int getNumOfBall() {
		return m_numOfBall;
	}
protected:
	void DrawBackgroundIcon(double pointOfX, double pointOfY);
	void moveArray(int arraySize, double* pArray, double move);
private:
	double m_coefficientOfFriction;
	int m_numOfBall;
	Psyzl2TileManager m_oTiles;
public:
	void DrawStrings();
};

