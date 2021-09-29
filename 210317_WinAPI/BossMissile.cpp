#include "BossMissile.h"
#include "Boss.h"
#include "CommonFunction.h"
#include "Camera.h"
#include "Image.h"
#include "CollisionManager.h"

HRESULT BossMissile::Init(Boss* owner)
{
	img = ImageManager::GetSingleton()->FindImage("BossMissile");

	pos = { -100, -100 };
	moveSpeed = 300;
	angle = 0;
	damage = 4;
	isFired = false;
	frameX = 0;
	frameTime = 0;
	return S_OK;
}

void BossMissile::Release()
{
	//SAFE_RELEASE(owner);
}

void BossMissile::Update()
{
	worldPos.x = pos.x;
	worldPos.y = pos.y;

	if (isFired)
	{
		float deltaTime = TimerManager::GetSingleton()->GetElapsedTime();
		time += TimerManager::GetSingleton()->GetElapsedTime();
		pos.x += (cosf(angle) * moveSpeed * deltaTime);
		pos.y -= (sinf(angle) * moveSpeed * deltaTime);

		CameraObject::UpdatePosition();
		collisionBox = GetRect(pos.x, pos.y + 5, 40, 40);
		//if (time > 0.5f)
		//{
		//	isFired = false;
		//	//CollisionManager::GetSingleton()->MissileRelese(this);
		//}

		FrameWrok();
	}
	if (!isFired)
	{
		time = 0;
		collisionBox = GetRect(10000, 10000, 20, 5);
		//CollisionManager::GetSingleton()->boss(this);
	}

}

void BossMissile::Render(HDC hdc)
{
	if (isFired)
	{
		//Rectangle(hdc, collisionBox.left + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x, collisionBox.top + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y,
		//	collisionBox.right + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x, collisionBox.bottom + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y);
		img->FrameRender(hdc, screenPos.x, screenPos.y, frameX, 0);

	}
}

void BossMissile::SetIsFired(bool isFired)
{
	this->isFired = isFired;
}

void BossMissile::FrameWrok()
{
	frameTime += TimerManager::GetSingleton()->GetElapsedTime();

	if (frameTime > 0.4f)
	{
		frameX++;
		if (frameX > 3)
		{
			frameX = 0;
		}
		frameTime = 0;
	}
}
