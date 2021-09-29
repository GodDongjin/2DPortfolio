#include "Player.h"
#include "Camera.h"
#include "Image.h"
#include "TileMap.h"
#include "starGun.h"
#include "MisiileGun.h"
#include "CommonFunction.h"
#include "CollisionManager.h"

HRESULT Player::Init(FPOINT pos, TileMap* tileMap)
{
	img = ImageManager::GetSingleton()->FindImage("LEFT_IDLE");
	UiInit();
	state = STATE::IDLE;
	see = SEE::LEFT;

	this->pos.x = pos.x;
	this->pos.y = pos.y;
		
	nowWeapon = 0;
	moveSpeed = 200.0f;
	frame = 0;
	frameTime = 0;
	maxFrame = 0;
	time = 0;
	gravity = 9.81;
	jumpPower = 50;
	stayTime = 0;
	air = 100;
	airTime = 0;

	hp = 20;

	isHit = false;

	jumpHeight = 0;

	isJump = false;
	isAlive = true;

	jumpTime = 0;

	this->tileMap = tileMap;

	collisionBox = GetRect(pos.x, pos.y, img->GetFrameWidth(), img->GetFrameHeight());
	hitBox = GetRect(pos.x, pos.y, img->GetFrameWidth(), img->GetFrameHeight());

	vWeapon.push_back(new starGun());
	vWeapon[0]->Init(this);

	vWeapon.push_back(new MisiileGun());
	vWeapon[1]->Init(this);

	collisionDoor = false;
	isCheking = false;
	isLeft = false;
	isLanding = false;
	isMove = true;
	isPixelCollison = false;
	isWater = false;


	
	return S_OK;
}

void Player::Release()
{
	for (int i = 0; i < vWeapon.size(); i++)
	{
		SAFE_RELEASE(vWeapon[i]);
	}
}

void Player::Update()
{
	if (isAlive)
	{
		Times();
		PixelCollision();
		worldPos.x = pos.x;
		worldPos.y = pos.y;

		vWeapon[nowWeapon]->Update();
		vWeapon[nowWeapon]->SetPos(pos);

		playerState(this->state);
		Move();
		changeState();
		frameWrok();
		Gravity();
		if(isJump)
			jump();
		Water();

		collisionBox = GetRect(pos.x, pos.y, img->GetFrameWidth(), img->GetFrameHeight());
		hitBox = GetRect(pos.x, pos.y, img->GetFrameWidth(), img->GetFrameHeight());

		Camera::GetSingleton()->AddTargetPos(worldPos);
		CollisionManager::GetSingleton()->AddPlayer(this);
		CameraObject::UpdatePosition();

		Die();
		HitDelay();
		NumBerIndex();
	}
	
}

void Player::Render(HDC hdc)
{
	if (isAlive)
	{
		//for (int i = 0; i < TILE_X * TILE_Y; i++)
			//{
			//	Rectangle(hdc, (tileMap->GetTileRect(i).left), tileMap->GetTileRect(i).top, 
			//		tileMap->GetTileRect(i).right, tileMap->GetTileRect(i).bottom);
			//}
			//for (int i = 0; i < 9; i++)
			//{
			//	Rectangle(hdc, tileMap->GetTileRect(playerIdX[i]).left + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x,
			//		tileMap->GetTileRect(playerIdX[i]).top + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y,
			//		tileMap->GetTileRect(playerIdX[i]).right + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x, 
			//		tileMap->GetTileRect(playerIdX[i]).bottom + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y);
			//}

			//Rectangle(hdc, tileMap->GetTileRect(playerIdX[7]).left + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x,
			//	tileMap->GetTileRect(playerIdX[7]).top + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y,
			//	tileMap->GetTileRect(playerIdX[7]).right + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x,
			//	tileMap->GetTileRect(playerIdX[7]).bottom + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y);
		if (state != STATE::OBJECT_COLLISION)
		{
			vWeapon[nowWeapon]->Render(hdc);
		}
		//Rectangle(hdc, collisionBox.left, collisionBox.top, collisionBox.right, collisionBox.bottom);
		img->FrameRender(hdc, screenPos.x, screenPos.y, frame, 0, false, 2);

		UiRender(hdc);

		//wsprintf(szText, "hp: %d", hp);
		//TextOut(hdc, screenPos.x, screenPos.y, szText, strlen(szText));

		//Rectangle(hdc, collisionBox.left + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x, collisionBox.top + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y,
		//	collisionBox.right + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x, collisionBox.bottom + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y);

		//Rectangle(hdc,
		//	tileMap->GetTileRect(playerIdX[6]).left, tileMap->GetTileRect(playerIdX[6]).top,
		//	tileMap->GetTileRect(playerIdX[6]).right, tileMap->GetTileRect(playerIdX[6]).bottom);
	}
	

}

void Player::Move()
{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			pos.x += moveSpeed * time;
			see = SEE::RIGHT;
			state = STATE::RUN;
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			pos.x -= moveSpeed * time;
			see = SEE::LEFT;
			state = STATE::RUN;
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
		{
			state = STATE::UP;
		}

		if (isJump == true)
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
			{
				state = STATE::DOWUN;
			}
		}
		if (state != STATE::DOWUN && isJump == false)
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
			{
				state = STATE::OBJECT_COLLISION;
			}
		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT) || KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT) ||
			KeyManager::GetSingleton()->IsOnceKeyUp(VK_UP) || state != STATE::OBJECT_COLLISION && KeyManager::GetSingleton()->IsOnceKeyUp(VK_DOWN))
		{
			state = STATE::IDLE;
		}
}

void Player::playerState(STATE state)
{
	this->state = state;
	if (see == SEE::LEFT)
	{
		switch (this->state)
		{
		case IDLE:
			img = ImageManager::GetSingleton()->FindImage("LEFT_IDLE");
			maxFrame = 0;
			//isJump = false;
			break;
		case UP:
			img = ImageManager::GetSingleton()->FindImage("LEFT_UP");
			break;
		case RUN:
			img = ImageManager::GetSingleton()->FindImage("LEFT_RUN");
			maxFrame = 1;
			break;
		case DOWUN:
			img = ImageManager::GetSingleton()->FindImage("LEFT_DOWUN");
			break;
		case OBJECT_COLLISION:
			img = ImageManager::GetSingleton()->FindImage("LEFT_OBJECT_COLLISION");
			break;
		}
	}
	if (see == SEE::RIGHT)
	{
		switch (this->state)
		{
		case IDLE:
			img = ImageManager::GetSingleton()->FindImage("RIGHT_IDLE");
			maxFrame = 0;
			//isJump = false;
			break;
		case UP:
			img = ImageManager::GetSingleton()->FindImage("RIGHT_UP");
			break;
		case RUN:
			img = ImageManager::GetSingleton()->FindImage("RIGHT_RUN");
			maxFrame = 1;
			break;
		case DOWUN:
			img = ImageManager::GetSingleton()->FindImage("RIGHT_DOWUN");
			break;
		case OBJECT_COLLISION:
			img = ImageManager::GetSingleton()->FindImage("RIGHT_OBJECT_COLLISION");
			break;
		}
	}
}

void Player::changeState()
{
	
	if (KeyManager::GetSingleton()->IsOnceKeyDown('X') && state != STATE::OBJECT_COLLISION)
	{
		vWeapon[nowWeapon]->Fire();
	}
	
	if (KeyManager::GetSingleton()->IsOnceKeyDown('Z') && !isJump && state != STATE::JUMP_DOWN && state != STATE::JUMP_UP)
	{
		
		frame = 0;
		isJump = true;
		state = STATE::JUMP_UP;
		jumpStartPos = pos;
	
	}
	
	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
	{
		if (nowWeapon <= vWeapon.size() - 1)
		{
			nowWeapon++;
		}
		if (nowWeapon > vWeapon.size() - 1)
		{
			nowWeapon = 0;
		}
	}
	
	
	if (KeyManager::GetSingleton()->IsOnceKeyDown('E'))
	{
		if (nowWeapon >= 0)
		{
			nowWeapon--;
		}
		if (nowWeapon < 0)
		{
			nowWeapon = vWeapon.size() - 1;
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))
	{
		hp--;
	}
}

void Player::frameWrok()
{
	

	if (frameTime > 0.2f)
	{
		frame++;
		if (frame > maxFrame)
		{
			frame = 0;
		}
		frameTime = 0;
	}
}

void Player::jump()
{
	if (isJump == true)
	{
		isLanding = false;
		
		jumpHeight = (jumpTime * jumpTime * (-gravity) / 2.0f ) + (jumpTime * jumpPower);
		
		pos.y = jumpStartPos.y - jumpHeight;		

		jumpTime += TimerManager::GetSingleton()->GetElapsedTime() * 10;

		if (jumpHeight < jumpPrevHeight)
		{
			if (state != STATE::DOWUN)
			{
				state = STATE::JUMP_DOWN;
			}
		}

		//if (jumpHeight < 0)
		//{
		//	jumpTime = 0;
		//	state = STATE::IDLE;
		//	isJump = false;
		//}

		jumpPrevHeight = jumpHeight;			
	}
	
}

//나중에 해보자
void Player::FrameReset()
{
	frame = 0;
	frameTime =0;
}

void Player::Gravity()
{
	if (isLanding == false && isJump == false)
	{
		pos.y += gravity;
	}
}

void Player::Water()
{
	if (isWater)
	{
		airTime += TimerManager::GetSingleton()->GetElapsedTime();
		
		if (airTime > 0.2f)
		{
			air--;
			airTime = 0;
		}
		
		//jumpPower = 20;
		
	}
	else
	{
		air = 100;
		airTime = 0;
		// jumpPower = 50;
	}
}

void Player::Times()
{
	time = TimerManager::GetSingleton()->GetElapsedTime();
	frameTime += TimerManager::GetSingleton()->GetElapsedTime();
	if (isJump == true)
	{
		
	}
	if (isJump == true && isWater == true)
	{
		jumpTime += TimerManager::GetSingleton()->GetElapsedTime() * 2;
	}
		
	if (state == STATE::OBJECT_COLLISION)
		stateObjectTime += TimerManager::GetSingleton()->GetElapsedTime();
}

void Player::PixelCollision()
{
	
	RectCollision();
	
	BottomPixelCollision();
	DoorPixelCollision();
	WaterPixelCollision();
}

void Player::RectCollision()
{
	int index = 0;
	

	// 플레이어의 현재 위치 인덱스 계산
	// 플레이어 주위 8방향 타일을 계산
	
	for (int i = -1; i <= 1; i++)		// y축
	{
		for (int j = -1; j <= 1; j++)	// x축
		{
			
				playerIdxX[index] = ((int)pos.x + TILESIZE / 2) / (TILESIZE) + j;
				playerIdxY[index] = ((((int)pos.y) + TILESIZE / 2) / TILESIZE) + i;
				//playerIdX[index] = ((((((int)pos.y)+ TILESIZE / 2) / TILESIZE) + i) * TILE_X) + 
				//	(((int)pos.x + TILESIZE / 2) / (TILESIZE) + j);

			index++;
		}
	}

	if (see == SEE::LEFT)
	{
		if (tileMap->GetTileType(playerIdxX[3],playerIdxY[3]) == TILETPYE::Wall)
		{
			if (RectInRect(tileMap->GetTileRect(playerIdxX[3], playerIdxY[3]), collisionBox))
			{
				pos.x += moveSpeed * time;
			}
		}

		
	}
	if (see == SEE::RIGHT)
	{
		if (tileMap->GetTileType(playerIdxX[5], playerIdxY[5]) == TILETPYE::Wall)
		{
			if (RectInRect(tileMap->GetTileRect(playerIdxX[5], playerIdxY[5]), collisionBox))
			{
				pos.x -= moveSpeed * time;
			}
		}
	}

	if (tileMap->GetTileType(playerIdxX[1], playerIdxY[1]) == TILETPYE::Wall)
	{
		if (RectInRect(tileMap->GetTileRect(playerIdxX[1], playerIdxY[1]), collisionBox))
		{
			jumpTime = 0;
			isJump = false;
			state = STATE::JUMP_DOWN;
		}
	}
		if (tileMap->GetTileType(playerIdxX[7], playerIdxY[7]) == TILETPYE::Wall)
		{
			if (RectInRect(tileMap->GetTileRect(playerIdxX[7], playerIdxY[7]), collisionBox))
			{
				// y축 방향 0, +1 에서 충돌이 발생되면 바닥이랑 닿았다.
				isLanding = true;
				//y축 위치값 보정

				if (state == STATE::JUMP_DOWN || state == STATE::DOWUN)
				{
					isJump = false;
					jumpTime = 0;
					state = STATE::IDLE;
				}
				pos.y = tileMap->GetTileRect(playerIdxX[7], playerIdxY[7]).top - img->GetFrameWidth();
			}
		}
		else
		{
			isLanding = false;
		}
	
	
}



void Player::BottomPixelCollision()
{
	COLORREF colorY;
	int Ry;
	int Gy;
	int By;
	float currPosY = pos.y + img->GetFrameHeight();
	float posY = 0;


	// 픽셀 충돌 확인
	for (int i = currPosY - 10; i < currPosY + 10; i++)
	{
		colorY = GetPixel(pixelMap->GetMemDC(), pos.x, i);

		Ry = GetRValue(colorY);
		Gy = GetGValue(colorY);
		By = GetBValue(colorY);

		if ((Ry == 255 && Gy == 0 && By == 0))
		{
			//위치 고정
			
			isPixelCollison = true;
			isLanding = true;
			if (state == STATE::JUMP_DOWN || state == STATE::DOWUN)
			{
				isJump = false;
				jumpTime = 0;
				state = STATE::IDLE;
			}
			pos.y = i - (img->GetFrameHeight()) + 5;
			return;

		}
		else
			isPixelCollison = false;
	}

}


void Player::DoorPixelCollision()
{

	COLORREF colorX;
	int Rx;
	int Gx;
	int Bx;
	float currPosX = pos.x + img->GetFrameWidth() / 2;
	float posX = 0;
	//float currPosX = player->GetPos().x + player->GetImage()->GetFrameWidth();
	// 픽셀 충돌 확인
	for (int i = currPosX - 3; i < currPosX + 3; i++)
	{
		colorX = GetPixel(pixelMap->GetMemDC(), i, pos.y);

		Rx = GetRValue(colorX);
		Gx = GetGValue(colorX);
		Bx = GetBValue(colorX);

		if ((Rx == 0 && Gx == 255 && Bx == 0) && state == STATE::OBJECT_COLLISION)
		{
			collisionDoor = true;
			return;
		}
		else
			collisionDoor = false;
	}

}

void Player::WaterPixelCollision()
{

	COLORREF colorY;
	int Ry;
	int Gy;
	int By;
	float currPosY = pos.y + img->GetFrameHeight();
	float posY = 0;


	// 픽셀 충돌 확인
	for (int i = currPosY - 10; i < currPosY + 10; i++)
	{
		colorY = GetPixel(pixelMap->GetMemDC(), pos.x, i);

		Ry = GetRValue(colorY);
		Gy = GetGValue(colorY);
		By = GetBValue(colorY);

		if ((Ry == 0 && Gy == 0 && By == 255))
		{
			//위치 고정
			isWater = true;
			if(isJump == false)
				jumpPower = 30;
			return;

		}
		else
		{
			isWater = false;
			jumpPower = 50;
		}
			
		
	}
}

void Player::HitDelay()
{
	if (isHit)
	{
		hitDelayTime += TimerManager::GetSingleton()->GetElapsedTime();

		if (hitDelayTime > 2)
		{
			hitDelayTime = 0;
			isHit = false;
		}
	}
}

void Player::Die()
{
	if (air <= 0)
	{
		isAlive = false;
	}
}

void Player::UiInit()
{
	hpState = ImageManager::GetSingleton()->FindImage("hp");
	hpBar = ImageManager::GetSingleton()->FindImage("hpBar");
	Lv = ImageManager::GetSingleton()->FindImage("LV");
	airState = ImageManager::GetSingleton()->FindImage("air");

	hpNumBer1 = ImageManager::GetSingleton()->FindImage("NumBer");
	hpNumBer2 = ImageManager::GetSingleton()->FindImage("NumBer");
	hpNumBer3 = ImageManager::GetSingleton()->FindImage("NumBer");

	airNumBer1 = ImageManager::GetSingleton()->FindImage("NumBer");
	airNumBer2 = ImageManager::GetSingleton()->FindImage("NumBer");
	airNumBer3 = ImageManager::GetSingleton()->FindImage("NumBer");

}

void Player::UiRender(HDC hdc)
{
	hpBar->Render(hdc, 0, 100); 
	hpState->UiBarRender(hdc, 72, 105, false, 43, hp);

	hpNumBer1->FrameRender(hdc, 50, 105, hpNum[0], 0);
	hpNumBer2->FrameRender(hdc, 35, 105, hpNum[1], 0);
	hpNumBer3->FrameRender(hdc, 20, 105, hpNum[2], 0);

	

	if (isWater)
	{
		airState->Render(hdc, (WINSIZE_X / 2) - 150, WINSIZE_Y / 2, true);

		airNumBer1->FrameRender(hdc, (WINSIZE_X / 2) + 50, WINSIZE_Y / 2 - 20, airNum[0], 0, false, 24);
		airNumBer2->FrameRender(hdc, (WINSIZE_X / 2) + 10, WINSIZE_Y / 2 - 20, airNum[1], 0, false, 24);
		airNumBer3->FrameRender(hdc, (WINSIZE_X / 2) - 30, WINSIZE_Y / 2 - 20, airNum[2], 0, false, 24);

	}

	
}

void Player::NumBerIndex()
{
	for (int i = 0; i < 3; i++)
	{
		int num = pow(10, i);

		hpNum[i] = (hp / num) % 10;
	}

	for (int i = 0; i < 3; i++)
	{
		int num = pow(10, i);

		airNum[i] = (air / num) % 10;
	}

 }
