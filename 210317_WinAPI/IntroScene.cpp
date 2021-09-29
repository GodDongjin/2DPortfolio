#include "IntroScene.h"
#include "Image.h"
#include "ImageManager.h"
#include "TilemapTool.h"
#include "BattleScene.h"
#include "TimerManager.h"
#include "BossStage.h"

HRESULT IntroScene::Init()
{
	introBackGround = ImageManager::GetSingleton()->FindImage("인트로배경");

	SceneManager::GetSingleton()->AddScene("타일맵툴", new TilemapTool());
	SceneManager::GetSingleton()->AddScene("배틀", new BattleScene());
	//SceneManager::GetSingleton()->AddScene("배틀", new BossStage());

	choise = ImageManager::GetSingleton()->AddImage("INTRO_RIGHT_RUN", "Image/caveStory/Player/RIGHT_RUN.bmp",
		64, 32, 2, 1, true, RGB(255, 0, 255));

	pos.x = WINSIZE_X / 2 - 180;
	pos.y = WINSIZE_Y / 2 + 85;

	count = 0;

	return S_OK;
}

void IntroScene::Release()
{
	
}

void IntroScene::Update()
{
	if (count < 4)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
		{
			pos.y += 50;
			count++;
		}
	}
	if (count > 0)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
		{
			pos.y -= 50;
			count--;
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		if (count == 0)
		{
			SceneManager::GetSingleton()->ChangeScene("배틀");
		}
		if (count == 1)
		{
			SceneManager::GetSingleton()->ChangeScene("타일맵툴");
		}
	}
	


	time += TimerManager::GetSingleton()->GetElapsedTime();

	if (time > 0.2f)
	{
		frame++;
		if (frame > 1)
		{
			frame = 0;
		}
		time = 0;
	}
}

void IntroScene::Render(HDC hdc)
{
	introBackGround->Render(hdc);
	choise->FrameRender(hdc, pos.x, pos.y, frame, 0);
}
