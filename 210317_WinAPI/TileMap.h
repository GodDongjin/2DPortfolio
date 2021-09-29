#pragma once
#include "CameraObject.h"

class Image;

class TileMap : public CameraObject
{
private:
	Image* tileImg;
	Image* collisionTileImg;

	TILE_INFO tileInfo[TILE_Y][TILE_X];
	COLLISION_TILE_INFO collisionTileInfo[TILE_Y][TILE_X];

	Image* collisionTile;

	FPOINT playerPos;
	vector<FPOINT> vE_pos;

	int stageNum;

	bool changeScene;

	char szText[128];
public:
	HRESULT Init(int num);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Load(int stageNum);
	void pixelLoad(int stageNum);
	void SetPixelMap(Image** pixelmap);

	RECT GetTileRect(int indexX, int indexY) { return tileInfo[indexY][indexX].rcTile; }
	TILETPYE GetTileType(int indexX, int indexY) { return tileInfo[indexY][indexX].tileType; }
	Image* GetCollisionTileImage() { return this->collisionTileImg; }
	FPOINT GetPlayerPos() { return this->playerPos; }
	vector<FPOINT>* GetVE_pos() { return &vE_pos; }
};

