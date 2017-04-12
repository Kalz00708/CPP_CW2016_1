#include "header.h"

#include "Psyzl2TileManager.h"


Psyzl2TileManager::Psyzl2TileManager()
	:TileManager(20, 20)
{
}


Psyzl2TileManager::~Psyzl2TileManager()
{
}

void Psyzl2TileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	// Base class implementation just draws some grey tiles
	pEngine->DrawRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		pEngine->GetColour(GetValue(iMapX, iMapY)),
		pSurface);
}
