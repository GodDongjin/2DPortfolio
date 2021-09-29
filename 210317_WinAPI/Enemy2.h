#pragma once
#include "Enemy.h"

class Enemy2 : public Enemy
{
public:
	HRESULT Init(float posX = 0, float posY = 0);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void FrameWrok();
	void NowState(EnemyState state);
	void RandomLeft();
	void Gravity();
	void TileCollisionIndex();

};

