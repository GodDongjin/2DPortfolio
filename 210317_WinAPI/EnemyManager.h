#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;

class EnemyManager : public GameNode
{
private:
	vector<Enemy*> vEnemys;

	vector<FPOINT>* vPos;

	int enemy1Count;
	int enemy2Count;
	int enemy3Count;
	int enemy4Count;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetPos(vector<FPOINT>* vPos) { this->vPos = vPos; } // zzzzzせせせせせせせせせせせせせ
	void SetEnemy1Count(int cout) { this->enemy1Count = cout; }
	void SetEnemy2Count(int cout) { this->enemy2Count = cout; }

};

