#include "MisiileGun.h"
#include "MissileManager.h"
#include "Image.h"
#include "Player.h"

HRESULT MisiileGun::Init(Player* player)
{
	img = ImageManager::GetSingleton()->FindImage("missileGun");

	maxAmmo1 = ImageManager::GetSingleton()->FindImage("NumBer");
	maxAmmo2 = ImageManager::GetSingleton()->FindImage("NumBer");

	nowAmmo1 = ImageManager::GetSingleton()->FindImage("NumBer");
	nowAmmo2 = ImageManager::GetSingleton()->FindImage("NumBer");

	UI = ImageManager::GetSingleton()->FindImage("division");
	 
	gun = ImageManager::GetSingleton()->FindImage("gunKind");

	this->player = player;

	angle = 0;
	delteTime = 0;
	weaponChoice = WeaponChoice::MissileGun;

	missiile = new MissileManager();
	missiile->Init(this);

	nowMissileCount = 10;
	maxMissileCount = 10;

    return S_OK;
}

void MisiileGun::Release()
{
	//SAFE_RELEASE(missiile);
}

void MisiileGun::Update()
{
	worldPos = this->pos;
	missiile->Update();
	NumBerIndex();
	CameraObject::UpdatePosition();


	if (KeyManager::GetSingleton()->IsOnceKeyDown('H'))
	{
		if (nowMissileCount < maxMissileCount)
		{
			nowMissileCount++;
		}
		
	}

}

void MisiileGun::Render(HDC hdc)
{
	missiile->Render(hdc);
	img->FrameRender(hdc, screenPos.x, screenPos.y, frameX, 0, false, 3);

	maxAmmo1->FrameRender(hdc, 170, 75, maxCount[0], 0, false, 10);
	maxAmmo2->FrameRender(hdc, 140, 75, maxCount[1], 0, false, 10);

	nowAmmo1->FrameRender(hdc, 170, 50, nowCount[0], 0, false, 10);
	nowAmmo2->FrameRender(hdc, 140, 50, nowCount[1], 0, false, 10);

	UI->Render(hdc, 80, 75);

	gun->FrameRender(hdc, 0, 40, 1, 0);
}

void MisiileGun::NumBerIndex()
{
	for (int i = 0; i < 2; i++)
	{
		int num = pow(10, i);

		nowCount[i] = (nowMissileCount / num) % 10;
	}

	for (int i = 0; i < 2; i++)
	{
		int num = pow(10, i);

		maxCount[i] = (maxMissileCount / num) % 10;
	}
}

void MisiileGun::Fire()
{
	if (nowMissileCount > 0)
	{
		missiile->Fire(this->pos, this->angle, bulletFrameX);
		nowMissileCount--;
	}
}

void MisiileGun::SetPos(FPOINT pos)
{
	if (player->GetSee() == SEE::LEFT)
	{
		switch (player->GetState())
		{
		case STATE::IDLE: case STATE::RUN:
		case STATE::JUMP_DOWN: case STATE::JUMP_UP:
			this->pos.x = pos.x;
			this->pos.y = pos.y + 10;
			bulletFrameX = 0;
			frameX = 0;
			angle = 180;
			break;
		case STATE::DOWUN:
			this->pos.x = pos.x - 8;
			this->pos.y = pos.y + 10;
			bulletFrameX = 3;
			frameX = 4;
			angle = -90;
			break;
		case STATE::UP:
			this->pos.x = pos.x;
			this->pos.y = pos.y;
			bulletFrameX = 1;
			frameX = 2;
			angle = 90;
		}
	}

	if (player->GetSee() != SEE::LEFT)
	{
		switch (player->GetState())
		{
		case STATE::IDLE: case STATE::RUN:
		case STATE::JUMP_DOWN: case STATE::JUMP_UP:
			this->pos.x = pos.x ;
			this->pos.y = pos.y + 10;
			bulletFrameX = 2;
			frameX = 1;
			angle = 0;
			break;
		case STATE::DOWUN:
			this->pos.x = pos.x + 15;
			this->pos.y = pos.y + 10;
			bulletFrameX = 3;
			frameX = 5;
			angle = -90;
			break;
		case STATE::UP:
			this->pos.x = pos.x + 8;
			this->pos.y = pos.y;
			bulletFrameX = 1;
			frameX = 3;
			angle = 90;
		}
	}




}
