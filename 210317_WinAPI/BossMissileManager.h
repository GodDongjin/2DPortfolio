#pragma once
#include "GameNode.h"
class BossMissile;
class Image;
class Boss;

class BossMissileManager : public GameNode
{
private:
	vector<BossMissile*> vMissiles;

	Boss* owner;
	Image* tileImg;

public:
	HRESULT Init(Boss* owner);
	void Release();
	void Update();
	void Render(HDC hdc);
	void AddMsiile();

	void Fire(FPOINT pos, float angle);
	void SetTileMap(Image* tileImg) { this->tileImg = tileImg; }

};

