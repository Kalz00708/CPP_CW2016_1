#pragma once
#include "TileManager.h"

class Psyzl2TileManager :
	public TileManager
{
public:
	Psyzl2TileManager();
	~Psyzl2TileManager();
	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
};

