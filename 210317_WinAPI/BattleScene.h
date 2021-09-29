#pragma once
#include "CameraObject.h"

// ���� MainGame Ŭ������ ������ �̵�

class Image;
class Player;
class TileMap;
class EnemyManager;

class BattleScene : public CameraObject
{
private:
	Image* backGround;
	Image* pixelMap;
	
	FPOINT mapPos;

	Player* player;
	EnemyManager* enemyManager;
	TileMap* tileMap;

	vector<FPOINT> vPos;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	//void pixelRender();
	//void PixelCollision();




	virtual ~BattleScene() {};
};

