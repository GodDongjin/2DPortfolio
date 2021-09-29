#pragma once
#include "CameraObject.h"

class Image;
class Player;
class TileMap;
class EnemyManager;

class Stage2 : public CameraObject
{
private:
	Image* backGround;
	Image* pixelMap;

	FPOINT mapPos;

	Player* player;
	EnemyManager* enemyManager;
	TileMap* tileMap;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~Stage2() {};
};

