#pragma once
#include "GameNode.h"

class Weapon;
class Missile;
class Image;

class MissileManager : public GameNode
{
private:
	vector<Missile*> vMissiles;

	Weapon* owner;
	Image* tileImg;

public:
	HRESULT Init(Weapon* owner);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(FPOINT pos, float angle, float frameX);
	void SetTileMap(Image* tileImg) { this->tileImg = tileImg; }
};

