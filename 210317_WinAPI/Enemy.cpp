#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT Enemy::Init(float posX, float posY)
{
    return S_OK;
}

void Enemy::Release()
{
    
}

void Enemy::Update()
{
   
}

void Enemy::Render(HDC hdc)
{
    
}


//void Enemy::RandomLeft()
//{
//	randomTime += TimerManager::GetSingleton()->GetElapsedTime();
//
//	if (randomTime >= maxRandomTime)
//	{
//		srand(time(NULL));
//		int random = rand() % 2;
//
//		isLeft = (bool)random;
//	}
//}
