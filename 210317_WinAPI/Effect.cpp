#include "Effect.h"
#include "Image.h"
#include "EffectManager.h"

HRESULT Effect::Init()
{
	isActive = false;
	currFrame = 0;
	maxFrame = 0;

	frameTime = 0;
	return S_OK;
}

void Effect::Release()
{
}

void Effect::Update()
{
	worldPos = pos;
	currTime += TimerManager::GetSingleton()->GetElapsedTime();
	if (isActive)
	{
		if (currTime >= frameTime)
		{
			currFrame++;
			if (currFrame >= maxFrame)
			{
				currFrame = 0;	
				isActive = false;
				EffectManager::GetSingleton()->ReleaseEffect(this);
			}
			currTime = 0;
		}
	}
	CameraObject::UpdatePosition();
}

void Effect::Render(HDC hdc)
{
	if (isActive)
	{
		img->FrameRender(hdc,screenPos.x, screenPos.y, currFrame, 0, true);
	}
}
