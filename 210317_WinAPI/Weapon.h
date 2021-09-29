#pragma once
#include "CameraObject.h"

class Image;
class Player;
class MissileManager;

class Weapon :public CameraObject
{
public:
	enum WeaponChoice { starGun, MissileGun };
protected:
	
	Image* img;
	Image* gun;
	Image* UI;

	MissileManager* missiile;

	FPOINT pos;
	bool isFire;
	float delteTime;
	float size;
	float frameX;
	float bulletFrameX;
	float angle;

	WeaponChoice weaponChoice;
	Player* player;
public:
	virtual HRESULT Init(Player* player);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Fire();

	virtual void SetPos(FPOINT pos) = 0;

	virtual FPOINT GetPos() { return this->pos; }
	virtual WeaponChoice GetWeapon() { return this->weaponChoice; }
};

