#pragma once
#include "CameraObject.h"

class Image;
class Player;
class TileMap;
class Boss;

class BossStage : public CameraObject
{
private:
	Image* backGround;
	Image* pixelMap;

	FPOINT mapPos;

	Player* player;
	Boss* boss;
	TileMap* tileMap;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~BossStage() {};
};


