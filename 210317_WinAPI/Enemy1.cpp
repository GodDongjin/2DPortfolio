#include "Enemy1.h"
#include "Image.h"
#include "CollisionManager.h"
#include "CommonFunction.h"
#include "Camera.h"
#include "EffectManager.h"

HRESULT Enemy1::Init(float posX, float posY)
{
	img = ImageManager::GetSingleton()->FindImage("enemy1");

    this->pos.x = posX;
    this->pos.y = posY;

	isAlive = true;
	isLeft = false;
	isLanding = false;
	isMove = false;
	isLeftCollsion = false;
	isRightCollsion = false;
	isPixleCollsion = false;
	isJump = false;

	maxFrame = 2;
	moveSpeed = 100;
	frameY = 1;
	gravity = 9.81f;
	outLookDistance = 250;
	hp = 20;
	jumpPower = 50;

	damege = 2;

	state = EnemyState::IDLE; 
     return S_OK;
}

void Enemy1::Release()
{
	CollisionManager::GetSingleton()->EnemyRelese(this);
}

void Enemy1::Update()
{
	if (isAlive)
	{
		moveTime = TimerManager::GetSingleton()->GetElapsedTime();

		worldPos.x = pos.x;
		worldPos.y = pos.y;

		hitBox = GetRect(pos.x, pos.y, img->GetFrameWidth(), img->GetFrameHeight());
		collsionBox = GetRect(pos.x, pos.y, img->GetFrameWidth(), img->GetFrameHeight());

		if (isMove)
		{
			maxFrame = 1;
			if (isLeft)
			{
				frameY = 0;
			}
			else if (!isLeft)
			{
				frameY = 1;
			}
		
			FrameWrok();
		}
		
		Move();	
		
		if (isLanding)
		{
			jumpTime = 0;
			jumpHeight = 0;
			isJump = false;
		}

		if (!isMove)
		{
			frameX = 0;
		}
		if (hp <= 0)
		{
			isAlive = false;
			hitBox = GetRect(1000,1000, 48, 48);
		}

		if (isLeftCollsion)
		{
			pos.x += moveSpeed * moveTime;
		}
		if (isRightCollsion)
		{
			pos.x -= moveSpeed * moveTime;
		}
	
		TileCollisionIndex();
		Gravity();
		CameraObject::UpdatePosition();
		
	}

}

void Enemy1::Render(HDC hdc)
{
	if (isAlive)
	{ 
		img->FrameRender(hdc, screenPos.x, screenPos.y, frameX, frameY);
	}
}

void Enemy1::Move()
{
	if (isMove == true)
	{
		if (isLeft == true)
		{
			pos.x -= moveSpeed * moveTime;
		}
	
		if (isLeft == false)
		{
			pos.x += moveSpeed * moveTime;
		}
	}
}

void Enemy1::FrameWrok()
{
	frameTime += TimerManager::GetSingleton()->GetElapsedTime();

	if (frameTime > 0.4f)
	{
		frameX++;
		if (frameX > maxFrame)
		{
			frameX = 0;
		}
		frameTime = 0;
	}

}
void Enemy1::TileCollisionIndex()
{
	int index = 0;
	int tempX, tempY;
	for (int i = -1; i <= 1; i++)		// yÃà
	{
		for (int j = -1; j <= 1; j++)	// xÃà
		{
			tempX = ((((int)(pos.x + 0.5f)) + INGAMETILESIZE / 2) / (INGAMETILESIZE)+j);
			tempY = ((((((int)(pos.y + 0.5f)) + INGAMETILESIZE / 2) / INGAMETILESIZE) + i));

			tileCollisionIndex[index] = ((((((int)(pos.y + 0.5f)) + INGAMETILESIZE / 2) / INGAMETILESIZE) + i) * TILE_X) +
				((((int)(pos.x + 0.5f)) + INGAMETILESIZE / 2) / (INGAMETILESIZE)+j);;
			index++;
		}
	}
}

//void Enemy1::Jump()
//{
//	if (isJump == true)
//	{
//		state = EnemyState::JUMP;
//
//		isLanding = false;
//
//		jumpHeight = (jumpTime * jumpTime * (-gravity) / 2.0f) + (jumpTime * jumpPower);
//
//		pos.y = jumpStartPos.y - jumpHeight;
//
//		jumpTime += TimerManager::GetSingleton()->GetElapsedTime() * 10;
//
//		
//		//if (jumpHeight < jumpPrevHeight)
//		//{
// 		//	jumpTime = 0;
//		//	jumpHeight = 0;
//		//	isJump = false;
//		//}
//
//		jumpPrevHeight = jumpHeight;
//	}
//}

void Enemy1::Gravity()
{
	if (isLanding == false)
	{
		pos.y += gravity;
	}
}

//void Enemy1::SetIsLanding(bool isLanding)
//{
//	
//		this->isLanding = isLanding;
//
//}
