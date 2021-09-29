#include "StarGunMissile.h"
#include "CollisionManager.h"
#include "starGun.h"
#include "Image.h"
#include "Camera.h"
#include "CommonFunction.h"
#include "EffectManager.h"

HRESULT StarGunMissile::Init(Weapon* owner)
{
	img = ImageManager::GetSingleton()->FindImage("starGunMissile");

	missileKind = MISSLEKIND::STAR;


	pos = { -100, -100 };
	moveSpeed = 800.0f;
	angle = 0;
	damage = 10;
	isFired = false;
	frameX = 0;

	return S_OK;
}

void StarGunMissile::Release()
{
	//SAFE_RELEASE(owner);
}

void StarGunMissile::Update()
{
	worldPos.x = pos.x;
	worldPos.y = pos.y;
	
	if (isFired)
	{
		float deltaTime = TimerManager::GetSingleton()->GetElapsedTime();
		time += TimerManager::GetSingleton()->GetElapsedTime();
		pos.x +=  (cosf(angle) * moveSpeed * deltaTime);
		pos.y -=  (sinf(angle) * moveSpeed * deltaTime);


		if (frameX == 0 || frameX == 2)
		{
			collisionBox = GetRectToCenter(pos.x + 18, pos.y + 8, 30, 5);
	
		}
		if (frameX == 3 || frameX == 1)
		{
			collisionBox = GetRectToCenter(pos.x + 18, pos.y, 5, 30);
		}
		
		if (time > 0.3f)
		{
			isFired = false;
			CollisionManager::GetSingleton()->MissileRelese(this);
		}
		
		CameraObject::UpdatePosition();
		
	}
	if (!isFired)
	{
		time = 0;
		collisionBox = GetRect(10000, 10000, 20, 5);
		CollisionManager::GetSingleton()->MissileRelese(this);

	}
}

void StarGunMissile::Render(HDC hdc)
{
	if (isFired)
	{
		//Rectangle(hdc, collisionBox.left + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x, collisionBox.top + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y,
		//	collisionBox.right + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x, collisionBox.bottom + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y);
		if (frameX == 0 || frameX == 2)
		{
			img->FrameRender(hdc, screenPos.x - 8, screenPos.y - 8, frameX, 0);
		}
		if (frameX == 3 || frameX == 1)
		{
			img->FrameRender(hdc, screenPos.x - 4, screenPos.y, frameX, 0);
		}
	}
}

void StarGunMissile::SetIsFired(bool isFired)
{
	this->isFired = isFired;
}
