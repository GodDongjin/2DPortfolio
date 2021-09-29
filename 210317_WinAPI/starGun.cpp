#include "starGun.h"
#include "Image.h"
#include "Player.h"
#include "MissileManager.h"

HRESULT starGun::Init(Player* player)
{
	img = ImageManager::GetSingleton()->FindImage("starGun");
	maxAmmo = ImageManager::GetSingleton()->FindImage("infinite");
	nowAmmo = ImageManager::GetSingleton()->FindImage("infinite");
	UI = ImageManager::GetSingleton()->FindImage("division");
	gun = ImageManager::GetSingleton()->FindImage("gunKind");

	this->player = player;

	angle = 0;
	delteTime = 0;
	weaponChoice = WeaponChoice::starGun;

	missiile = new MissileManager();
	missiile->Init(this);

	return S_OK;
}

void starGun::Release()
{
	//SAFE_RELEASE(missiile);
}

void starGun::Update()
{
	worldPos = this->pos;
	missiile->Update();

	CameraObject::UpdatePosition();
}

void starGun::Render(HDC hdc)
{
	missiile->Render(hdc);
	img->FrameRender(hdc, screenPos.x, screenPos.y, frameX, 0, false, 3);

	maxAmmo->Render(hdc, 125, 75);
	nowAmmo->Render(hdc, 125, 50);
	UI->Render(hdc, 80, 75);
	gun->FrameRender(hdc, 0, 40, 0, 0);
}

void starGun::Fire()
{
	
	missiile->Fire(this->pos, this->angle, bulletFrameX);
	
}

void starGun::SetPos(FPOINT pos)
{
	if (player->GetSee() == SEE::LEFT)
	{
		switch (player->GetState())
		{
		case STATE::IDLE: case STATE::RUN:
		case STATE::JUMP_DOWN: case STATE::JUMP_UP:
			this->pos.x = pos.x - 5;
			this->pos.y = pos.y + 20;
			bulletFrameX = 0;
			frameX = 0;
			angle = 180;
			break;
		case STATE::DOWUN:
			this->pos.x = pos.x;
			this->pos.y = pos.y;
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
			this->pos.x = pos.x + 30;
			this->pos.y = pos.y + 20;
			bulletFrameX = 2;
			frameX = 1;
			angle = 0;
			break;
		case STATE::DOWUN:
			this->pos.x = pos.x + 25;
			this->pos.y = pos.y + 20;
			bulletFrameX = 3;
			frameX = 5;
			angle = -90;
			break;
		case STATE::UP:
			this->pos.x = pos.x + 26;
			this->pos.y = pos.y;
			bulletFrameX = 1;
			frameX = 3;
			angle = 90;
		}
	}
	
	
}
