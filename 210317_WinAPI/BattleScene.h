#pragma once
#include "CameraObject.h"

// 기존 MainGame 클래스의 내용을 이동

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

