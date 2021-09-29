#pragma once
#include "Enemy.h"

class Enemy1 : public Enemy
{
public:
	HRESULT Init(float posX, float posY);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void FrameWrok();
	//void Jump();
	void Gravity();
	void TileCollisionIndex();

};

