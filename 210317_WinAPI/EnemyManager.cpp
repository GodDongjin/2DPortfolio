#include "EnemyManager.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "CollisionManager.h"

HRESULT EnemyManager::Init()
{
	for (int i = 0; i < enemy1Count; i++)
	{
		vEnemys.push_back(new Enemy1());
	}

	for (int j = 0; j < enemy2Count; j++)
	{
		vEnemys.push_back(new Enemy2());
		//vEnemys[i]->Init(pos.x, pos.y);
		//CollisionManager::GetSingleton()->AddEnemy(vEnemys[i]);
	}

	random_shuffle((*vPos).begin(), (*vPos).end());

	for (int i = 0; i < vEnemys.size(); i++)
	{
		vEnemys[i]->Init((*vPos)[i].x, (*vPos)[i].y);
		CollisionManager::GetSingleton()->AddEnemy(vEnemys[i]);
	}
	int a;
	return S_OK;
}

void EnemyManager::Release()
{
	for (int i = 0; i < vEnemys.size(); i++)
	{
		SAFE_RELEASE(vEnemys[i]);
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < vEnemys.size(); i++)
	{
		vEnemys[i]->Update();
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (int i = 0; i < vEnemys.size(); i++)
	{
		vEnemys[i]->Render(hdc);
	}
}

