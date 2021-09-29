#include "MissileGunMissile.h"
#include "Weapon.h"
#include "CommonFunction.h"
#include "Camera.h"
#include "Image.h"
#include "CollisionManager.h"

HRESULT MissileGunMissile::Init(Weapon* owner)
{
	img = ImageManager::GetSingleton()->FindImage("missileGunMissile");

	missileKind = MISSLEKIND::MISSILE;

	pos = { -100, -100 };
	moveSpeed = 600;
	angle = 0;
	damage = 20;
	isFired = false;
	frameX = 0;

	return S_OK;
}

void MissileGunMissile::Release()
{
	//SAFE_RELEASE(owner);
}

void MissileGunMissile::Update()
{
	worldPos.x = pos.x;
	worldPos.y = pos.y;

	if (isFired)
	{
		float deltaTime = TimerManager::GetSingleton()->GetElapsedTime();
		time += TimerManager::GetSingleton()->GetElapsedTime();
		pos.x += (cosf(angle) * moveSpeed * deltaTime);
		pos.y -= (sinf(angle) * moveSpeed * deltaTime);

		if (frameX == 0 || frameX == 2)
		{
			collisionBox = GetRect(pos.x, pos.y + 5, 30, 15);
		}
		if (frameX == 1 || frameX == 3 )
		{
			collisionBox = GetRect(pos.x + 5 , pos.y, 15, 30);
		}

		CameraObject::UpdatePosition();

		//if (time > 0.3f)
		//{
		//	isFired = false;
		//	CollisionManager::GetSingleton()->MissileRelese(this);
		//}
	}
	if (!isFired)
	{
		time = 0;
		collisionBox = GetRect(10000, 10000, 20, 5);
		CollisionManager::GetSingleton()->MissileRelese(this);
	}

}

void MissileGunMissile::Render(HDC hdc)
{
	if (isFired)
	{
		if (frameX == 0)
		{
			img->FrameRender(hdc, screenPos.x - 15, screenPos.y, frameX, 0);
		}
		if (frameX == 2)
		{
			img->FrameRender(hdc, screenPos.x + 15, screenPos.y, frameX, 0);
		}

		if (frameX == 1)
		{
			img->FrameRender(hdc, screenPos.x + 5, screenPos.y - 15, frameX, 0);
		}
		if (frameX == 3)
		{
			img->FrameRender(hdc, screenPos.x, screenPos.y, frameX, 0);
		}

		//Rectangle(hdc, collisionBox.left + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x, collisionBox.top + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y,
		//	collisionBox.right + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x, collisionBox.bottom + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y);

	}
}

void MissileGunMissile::SetIsFired(bool isFired)
{
	this->isFired = isFired;
}
