#pragma once
#include "CameraObject.h"

class Image;
class Weapon;

class Missile : public CameraObject
{
public:
	enum MISSLEKIND
	{
		STAR,
		MISSILE,
	};

protected:
	Image* img;
	Image* tileImg;

	FPOINT pos;
	float moveSpeed;
	float moveTime;
	int size;
	RECT collisionBox;
	int damage;
	float angle;
	bool isFired;
	int fireIndex;
	int fireStep;
	float frameX;
	float destAngle;
	float time;

	MISSLEKIND missileKind;

	Weapon* owner;
	

public:
	virtual HRESULT Init(Weapon* owner);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SetIsFired(bool isFired);

	virtual void SetPos(FPOINT pos) { this->pos = pos; }
	virtual FPOINT GetPos() { return this->pos; }

	virtual bool GetIsFired() { return this->isFired; }

	virtual void SetAngle(float angle) { this->angle = angle; }
	virtual void SetFireIndex(int fireIndex) { this->fireIndex = fireIndex; }
	virtual void SetTileMap(Image* tileMap) { this->tileImg = tileMap; }

	virtual void SetFrameX(int num) { this->frameX = num; }

	virtual int GetSize() { return this->size; }
	virtual RECT GetMissileRect() { return this->collisionBox; }

	virtual int GetDamege() { return this->damage; }

	virtual MISSLEKIND GetMissileKind() { return this->missileKind; }
};

