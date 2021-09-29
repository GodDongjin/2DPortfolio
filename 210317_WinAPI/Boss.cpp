#include "Boss.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "BossMissileManager.h"

HRESULT Boss::Init(float posX, float posY)
{
	img = ImageManager::GetSingleton()->FindImage("Boss_Fire");
	hpBarBack = ImageManager::GetSingleton()->FindImage("BossBackBar");
	hpBar = ImageManager::GetSingleton()->FindImage("BossHpBar");
	BossHp = ImageManager::GetSingleton()->FindImage("BossHp");

	missile = new BossMissileManager();
	missile->Init(this);

	see = SEE::LEFT;
	pattern = PATTERN::ILDE;

	damege = 4;
	fireCount = 0;

	this->pos.x = posX;
	this->pos.y = posY;

	moveSpeed = 200;
	gravity = 9.81f;
	jumpPower = 50;

	frameX = 0;
	maxFrame = 1;
	frameMaxTime = 0.2f;

	moveTime = 0;
	runTime = 0;
	jumpTime = 0;
	stayTime = 0;
	fierTime = 0;

	angle = 0;

	isAlive = true;
	isLanding = false;
	isMove = false;
	isJump = false;
	isDirectionChange = false;
	isFire = false;
	isDie = false;

	runCount = 0;
	jumpCount = 0;

	hp = 1000;

	collsionBox = GetRect(pos.x, pos.y, img->GetFrameWidth(), img->GetFrameHeight());
	hitBox = GetRect(pos.x + 30, pos.y + 30, 70, 70);
	attckBox = GetRect(pos.x + 30, pos.y + 30, 70, 70);
	return S_OK;
}

void Boss::Release()
{
	missile->Release();
}

void Boss::Update()
{
	
	worldPos = pos;

	if (isAlive)
	{
		collsionBox = GetRect(pos.x, pos.y, img->GetFrameWidth(), img->GetFrameHeight());
		hitBox = GetRect(pos.x + 30, pos.y + 30, 70, 70);
		attckBox = GetRect(pos.x + 30, pos.y + 30, 70, 70);
		stayTime += TimerManager::GetSingleton()->GetElapsedTime();
		moveTime = TimerManager::GetSingleton()->GetElapsedTime();

		if (stayTime < 1)
		{
			pattern = PATTERN::ILDE;
		}

		if (stayTime >= 1)
		{
			if (!isMove)
			{
				frameX = 0;
				runCount++;
				isMove = true;
			}
		}

		if (runCount >= 2 && !isDirectionChange)
		{
			isDirectionChange = true;
			ChangeDirection();
		}

		if (isLeftCollsion)
		{
			pos.x += moveSpeed * moveTime;
		}
		if (isRightCollsion)
		{
			pos.x -= moveSpeed * moveTime;
		}

		if (isLanding && isJump && isMove)
		{
			if (hp > 500)
			{
				jumpDaltaTime = 0;
				isMove = false;
				isJump = false;
				jumpHeight = 0;
				stayTime = 0;
				runTime = 0;
				frameX = 0;
			}

			if (hp <= 500)
			{
				if (jumpCount <= 2)
				{
					jumpDaltaTime = 0;
					isMove = false;
					isJump = false;
					jumpHeight = 0;
					stayTime = 0;
					runTime = 0;
					frameX = 0;
				}
				if (jumpCount > 2)
				{
					jumpDaltaTime = 0;
					isMove = false;
					isJump = false;
					jumpCount = 0;
					isFire = true;
					jumpHeight = 0;
					frameX = 0;
					pattern = PATTERN::SHOOT;
				}
			}

		}

		Move();
		Jump();
		Fire();
		State();
		FrameWrok();
		Gravity();
		TileCollisionIndex();
		
		CollisionManager::GetSingleton()->BossTileRectCollision();
		

 		if (hp <= 0)
		{
			isAlive = false;
		}

	}
	
	if (!isAlive)
	{
		DieFrameWrok();
	}
	
	missile->Update();
	
	 CameraObject::UpdatePosition();

}

void Boss::Render(HDC hdc)
{
	

	missile->Render(hdc);
	img->FrameRender(hdc, screenPos.x, screenPos.y, frameX, frameY);
	//Rectangle(hdc, hitBox.left + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x, hitBox.top + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y,
	//	hitBox.right + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x, hitBox.bottom + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y);

	//wsprintf(szText, "hp: %d", hp);
	//TextOut(hdc, screenPos.x, screenPos.y, szText, strlen(szText));

	hpBarBack->Render(hdc, 100, WINSIZE_Y - 50);
	BossHp->Render(hdc, 120, WINSIZE_Y - 43);
	hpBar->UiBarRender(hdc, 300, WINSIZE_Y - 43, false, 1000, hp);
}

void Boss::FrameWrok()
{
	frameTime += TimerManager::GetSingleton()->GetElapsedTime();

	if (frameTime > frameMaxTime)
	{
		frameX++;
		if (frameX > maxFrame)
		{
			frameX = 0;
		}
		frameTime = 0;
	}
}

void Boss::State()
{
	if (see == SEE::LEFT)
	{
		switch (pattern)
		{
		case Boss::PATTERN::RUN:
			img = ImageManager::GetSingleton()->FindImage("Boss_Run");
			maxFrame = 1;
			frameY = 0;
			break;
		case Boss::PATTERN::JUMP:
			img = ImageManager::GetSingleton()->FindImage("Boss_Jump");
			maxFrame = 2;
			frameY = 0;
			frameMaxTime = 0.4f;
			break;
		case Boss::PATTERN::SHOOT:
			img = ImageManager::GetSingleton()->FindImage("Boss_Fire");
			maxFrame = 1;
			frameY = 0;
			break;
		case Boss::PATTERN::ILDE:
			img = ImageManager::GetSingleton()->FindImage("Boss_Idle");
			maxFrame = 1;
			frameY = 0;
			break;
		case Boss::PATTERN::DIE:
			img = ImageManager::GetSingleton()->FindImage("Boss_Die");
			frameY = 0;
			break;

		}
	}

	if (see == SEE::RIGHT)
	{
		switch (pattern)
		{
		case Boss::PATTERN::RUN:
			img = ImageManager::GetSingleton()->FindImage("Boss_Run");
			maxFrame = 1;
			frameY = 1;
			break;
		case Boss::PATTERN::JUMP:
			img = ImageManager::GetSingleton()->FindImage("Boss_Jump");
			maxFrame = 2;
			frameY = 1;
			frameMaxTime = 0.4f;
			break;
		case Boss::PATTERN::SHOOT:
			img = ImageManager::GetSingleton()->FindImage("Boss_Fire");
			maxFrame = 1;
			frameY = 1;
			break;
		case Boss::PATTERN::ILDE:
			img = ImageManager::GetSingleton()->FindImage("Boss_Idle");
			maxFrame = 1;
			frameY = 1;
			break;
		case Boss::PATTERN::DIE:
			img = ImageManager::GetSingleton()->FindImage("Boss_Die");
			frameY = 1;
			break;
		}
	}

}

void Boss::Move()
{
#pragma region Test

	//if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	//{
	//	pos.x += moveSpeed * moveTime;
	//	see = SEE::RIGHT;
	//	//patter
	//}
	//
	//if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	//{
	//	pos.x -= moveSpeed * moveTime;
	//	see = SEE::LEFT;
	//	//state = STATE::RUN;
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown('V'))
	//{
	//	if (!isJump)
	//	{
	//		frameX = 0;
	//		isJump = true;
	//		jumpStartPos = pos;
	//	}
	//	
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	//{
	//	if (see == SEE::LEFT)
	//	{
	//		angle = rand() % -90 + 135;
	//	}
	//
	//	else if (see == SEE::RIGHT)
	//	{
	//		angle = 0;
	//
	//		angle = rand() % 90 + (-45);
	//	}
	//
	//	missile->Fire(pos, angle);
	//}
	
	
	
#pragma endregion Test

#pragma region Real
	if (isMove)
	{
		runTime += TimerManager::GetSingleton()->GetElapsedTime();
	
		if (runTime >= 1.0f)
		{
			if (!isJump && !isFire)
			{
				frameX = 0;
				isJump = true;
				jumpCount++;
				jumpStartPos = pos; 
			}
			//else if (hp <= 50)
			//{
			//	pattern = PATTERN::SHOOT;
			//	Fire();
			//}
			
		}
	
		if (pattern != PATTERN::SHOOT)
		{
			if (see == SEE::LEFT)
			{
				pos.x -= moveSpeed * moveTime;
			}
			else if (see == SEE::RIGHT)
			{
				pos.x += moveSpeed * moveTime;
			}
		}
	
	
	
	}
#pragma endregion Real
}

void Boss::Jump()
{
	if (isJump == true)
	{
		pattern = PATTERN::JUMP;
		isLanding = false;

		jumpHeight = (jumpDaltaTime * jumpDaltaTime * (-gravity) / 2.0f) + (jumpDaltaTime * jumpPower);
		
		pos.y = jumpStartPos.y - jumpHeight;
		
		jumpDaltaTime += TimerManager::GetSingleton()->GetElapsedTime() * 10;

		jumpPrevHeight = jumpHeight;
	}

	
	
}

void Boss::TileCollisionIndex()
{
	int index = 0;
	int tempX, tempY;

	for (int i = -1; i <= 1; i++)		// yÃà
	{
		for (int j = -1; j <= 1; j++)	// xÃà
		{
			tempX = ((((int)(pos.x + 0.5f) + 32) + INGAMETILESIZE / 2) / (INGAMETILESIZE) + j);
			tempY = ((((((int)(pos.y + 0.5f) + 32) + INGAMETILESIZE / 2) / INGAMETILESIZE) + i) * TILE_X);

			

			tileCollisionIndex[index] = tempX + tempY;
			index++;
		}
	}
}

void Boss::ChangeDirection()
{
	if (see == SEE::LEFT) { see = SEE::RIGHT; runCount = 0; isDirectionChange = false; }
	else if (see == SEE::RIGHT) { see = SEE::LEFT; runCount = 0; isDirectionChange = false; }
}


void Boss::Gravity()
{
	if (isLanding == false && isJump == false)
	{
		pos.y += gravity;
	}

}

void Boss::Fire()
{
	if (isFire == true)
	{
		fierTime += TimerManager::GetSingleton()->GetElapsedTime();	
		fireDelay += TimerManager::GetSingleton()->GetElapsedTime();

		if (fireDelay >= 0.2f)
		{
			if (see == SEE::LEFT)
			{
				angle = rand() % -90 + 135;
				missile->Fire({ pos.x + 30, pos.y + 30 }, angle);
			}

			else if (see == SEE::RIGHT)
			{

				angle = rand() % 90 + (-45);
				missile->Fire({ pos.x + 60, pos.y + 30 }, angle);
			}

			//missile->AddMsiile();
			
			fireDelay = 0.0f;
		}

		if (fierTime > 2)
		{
			fierTime = 0;
			stayTime = 0;
			runTime = 0;
			frameX = 0;
			fierTime = 0;
			jumpCount = 0;
			runCount = 0;
			isFire = false;
		}
	}

}

void Boss::DieFrameWrok()
{
	if (!isAlive)
	{
		img = ImageManager::GetSingleton()->FindImage("Boss_Die");

		if (see == SEE::LEFT)
		{
			frameY = 0;
		}
		else if (see == SEE::RIGHT)
		{
			frameY = 1;
		}
		
		//pattern = PATTERN::DIE;

		DieDelay += TimerManager::GetSingleton()->GetElapsedTime();
		DieTime += TimerManager::GetSingleton()->GetElapsedTime();

		if (DieTime <= 1.0f)
		{
			if (DieDelay >= 0.2f)
			{
				if (frameX == 0)
				{
					frameX = 1;
					DieDelay = 0;
					return;
				}
				 if (frameX == 1)
				{
					frameX = 0;
					DieDelay = 0;
					return;
				}
			}
		}
		
		else if(DieTime > 1)
		{
			//frameX = 1;

			frameTime += TimerManager::GetSingleton()->GetElapsedTime();

			if (frameTime > 0.5)
			{
				frameX++;
				if (frameX >= 3)
				{
					frameX = 3;
					isDie = true;
				}
				frameTime = 0;
			}
		}

	}

}
