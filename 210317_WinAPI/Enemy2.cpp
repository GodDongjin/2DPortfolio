#include "Enemy2.h"
#include "Image.h"
#include "CollisionManager.h"
#include "CommonFunction.h"
#include "Camera.h"

HRESULT Enemy2::Init(float posX, float posY)
{
	img = ImageManager::GetSingleton()->FindImage("enemy2_IDLE");

	this->pos.x = posX;
	this->pos.y = posY;

	isAlive = true;
	isLanding = false;
	isMove = false;
	isLeftCollsion = false;
	isRightCollsion = false;
	isPixleCollsion = false;
	srand(time(NULL));
	int random = rand() % 2;
	
	isLeft = (bool)random;

	maxFrame = 1;
	moveSpeed = 100;
	frameY = 1;
	gravity = 9.81f;
	hp = 10;
	randomTime = 0;
	maxRandomTime = 2.0f;

	damege = 2;

	state = EnemyState::IDLE;

    return S_OK;
}

void Enemy2::Release()
{
	CollisionManager::GetSingleton()->EnemyRelese(this);
}

void Enemy2::Update()
{
	if (isAlive)
	{
		moveTime += TimerManager::GetSingleton()->GetElapsedTime();

		worldPos.x = pos.x;
		worldPos.y = pos.y;

		hitBox = GetRect(pos.x, pos.y, 48, 48);
		collsionBox = GetRect(pos.x, pos.y, 48, 48);
		

		if (moveTime > 2.0f)
		{
			isMove = true;
		
		}
		if (moveTime > 4.0f)
		{
			isMove = false;
			moveTime = 0;
		}

		if (isMove)
		{
			Move();
			state = EnemyState::RUN;
		}
		if (!isMove)
		{
			state = EnemyState::IDLE;
		}

		if (hp <= 0)
		{
			hitBox = GetRect(1000, 1000, 48, 48);
			isAlive = false;
		}

		FrameWrok();
		TileCollisionIndex();
		Gravity();
		if (!isMove)
		{
			RandomLeft();
		}
		NowState(state);
		
		CameraObject::UpdatePosition();
	}
	if (!isAlive)
	{
		CollisionManager::GetSingleton()->EnemyRelese(this);
	}
}

void Enemy2::Render(HDC hdc)
{
	if (isAlive)
	{
		img->FrameRender(hdc, screenPos.x, screenPos.y, frameX, frameY);
	}
}

void Enemy2::Move()
{
	float time = TimerManager::GetSingleton()->GetElapsedTime();

	if (isLeft == true)
	{
		pos.x -= moveSpeed * time;
	}
	if (isLeftCollsion)
	{
		pos.x += moveSpeed * time;
	}
	if (isLeft == false)
	{
		pos.x += moveSpeed * time;
	}
	if (isRightCollsion)
	{
		pos.x -= moveSpeed * time;
	}

}

void Enemy2::FrameWrok()
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

void Enemy2::NowState(EnemyState state)
{
	this->state = state;

	if (isLeft)
	{
		switch (this->state)
		{
		case EnemyState::IDLE:
			img = ImageManager::GetSingleton()->FindImage("enemy2_IDLE");
			frameY = 0;
			break;
		case EnemyState::RUN:
			img = ImageManager::GetSingleton()->FindImage("enemy2_RUN");
			frameY = 0;
			break;
		case EnemyState::HIT:
			img = ImageManager::GetSingleton()->FindImage("enemy2_DIE");
			frameY = 0;
			break;
		}
	}
	else
	{
		switch (this->state)
		{
		case EnemyState::IDLE:
			img = ImageManager::GetSingleton()->FindImage("enemy2_IDLE");
			frameY = 1;
			break;
		case EnemyState::RUN:
			img = ImageManager::GetSingleton()->FindImage("enemy2_RUN");
			frameY = 1;
			break;
		case EnemyState::HIT:
			img = ImageManager::GetSingleton()->FindImage("enemy2_DIE");
			frameY = 1;
			break;
		}
	}
	
}

void Enemy2::RandomLeft()
{
	randomTime += TimerManager::GetSingleton()->GetElapsedTime();
	
	if (randomTime >= maxRandomTime)
	{
		int random = rand() % 2;

		isLeft = (bool)random;

		randomTime = 0;
	}
}


void Enemy2::Gravity()
{
	if (isLanding == false)
	{
		pos.y += gravity;
	}

}

void Enemy2::TileCollisionIndex()
{
	int index = 0;
	int tempX, tempY;
	for (int i = -1; i <= 1; i++)		// yÃà
	{
		for (int j = -1; j <= 1; j++)	// xÃà
		{

			tempX = ((((int)(pos.x + 0.5f)) + INGAMETILESIZE / 2) / (INGAMETILESIZE)+j);
			tempY = ((((((int)(pos.y + 0.5f)) + INGAMETILESIZE / 2) / INGAMETILESIZE) + i));

			//tempX = ((((int)(pos.x + 0.5f) + 32) + INGAMETILESIZE / 2) / (INGAMETILESIZE)+j);
			//tempY = ((((((int)(pos.y + 0.5f) + 32) + INGAMETILESIZE / 2) / INGAMETILESIZE) + i) * TILE_X);

			//tempX = (((((int)pos.y + 0.5f) + INGAMETILESIZE / 2) / INGAMETILESIZE) + i) * TILE_X;
			//tempY = ((int)pos.x + 0.5f) / (INGAMETILESIZE)+j;

			tileCollisionIndex[index] = ((((((int)(pos.y + 0.5f)) + INGAMETILESIZE / 2) / INGAMETILESIZE) + i) * TILE_X) +
				((((int)(pos.x + 0.5f)) + INGAMETILESIZE / 2) / (INGAMETILESIZE)+j);;
			index++;
		}
	}
}
