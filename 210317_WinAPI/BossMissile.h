#pragma once
#include "CameraObject.h"

class Image;
class Boss;

class BossMissile : public CameraObject
{
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
	float frameTime;

	Boss* owner;


public:
	HRESULT Init(Boss* owner);
	void Release();
	void Update();
	void Render(HDC hdc);
	void SetIsFired(bool isFired);
	void FrameWrok();

	virtual void SetPos(FPOINT pos) { this->pos = pos; }
	virtual FPOINT GetPos() { return this->pos; }

	virtual bool GetIsFired() { return this->isFired; }

	virtual void SetAngle(float angle) { this->angle = angle; }
	virtual void SetFireIndex(int fireIndex) { this->fireIndex = fireIndex; }
	virtual void SetTileMap(Image* tileMap) { this->tileImg = tileMap; }

	virtual int GetSize() { return this->size; }
	virtual RECT GetMissileRect() { return this->collisionBox; }

	virtual int GetDamege() { return this->damage; }
};

