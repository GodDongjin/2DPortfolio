#include "EndingCredit.h"
#include "Image.h"

HRESULT EndingCredit::Init()
{
	backGround = ImageManager::GetSingleton()->FindImage("endingBack");
	endingCredit = ImageManager::GetSingleton()->FindImage("ending");

	frame = 0;
	frameTime = 0;

	return S_OK;
}

void EndingCredit::Release()
{
}

void EndingCredit::Update()
{

	frameTime += TimerManager::GetSingleton()->GetElapsedTime();

	if (frameTime > 1.5)
	{
		frame++;
		if (frame >= 16)
		{
			frame = 0;
		}
		frameTime = 0;
	}
}

void EndingCredit::Render(HDC hdc)
{
	backGround->Render(hdc, 0, 0);
	endingCredit->FrameRender(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, frame, 0, true);
}
