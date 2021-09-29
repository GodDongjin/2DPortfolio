#include "Button.h"
#include "Image.h"
#include "TilemapTool.h"

/*
	실습1. 버튼 이미지를 세이브, 로드에 맞게 수정
	실습2. 스테이지를 지정할 수 있는 버튼을 추가로 생성
	실습3. 추가된 버튼(스테이지 전환)이 정상 동작하도록 코드 구현
*/

HRESULT Button::Init(const char* fileName, int posX, int posY, int key /* 버튼 기능 */)
{
	state = (ButtonState)key;

	switch (state)
	{
	case ButtonState::STAGE1:
		nowButton = ImageManager::GetSingleton()->FindImage(fileName);
		frame = 0;
		
		break;
	case ButtonState::STAGE2:
		nowButton = ImageManager::GetSingleton()->FindImage(fileName);
		frame = 1;
		
		break;
	case ButtonState::STAGE3:
		nowButton = ImageManager::GetSingleton()->FindImage(fileName);
		frame = 2;
		
		break;
	case ButtonState::STAGE4:
		nowButton = ImageManager::GetSingleton()->FindImage(fileName);
		frame = 3;
		
		break;
	case ButtonState::STAGE5:
		nowButton = ImageManager::GetSingleton()->FindImage(fileName);
		frame = 4;
		
		break;
	case ButtonState::STAGE6:
		nowButton = ImageManager::GetSingleton()->FindImage(fileName);
		frame = 5;
		
		break;
	case ButtonState::SAVE:
		nowButton = ImageManager::GetSingleton()->FindImage(fileName);
		frame = 0;
		
		break;
	}
	

	pos.x = posX;
	pos.y = posY;

	rc.left = pos.x - nowButton->GetFrameWidth() / 2;
	rc.top = pos.y - nowButton->GetFrameHeight() / 2;
	rc.right = rc.left + nowButton->GetFrameWidth();
	rc.bottom = rc.top + nowButton->GetFrameHeight();

	func = nullptr;// TilemapTool::Save;

	return S_OK;
}

HRESULT Button::Init()
{
	return E_NOTIMPL;
}

void Button::Release()
{
}

void Button::Update()
{
	if (PtInRect(&rc, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			state = ButtonState::DOWN;
		}
		else if (state == ButtonState::DOWN &&
			KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			state = ButtonState::UP;

			// 버튼 기능 수행 : 세이브, 로드
			func(func_arg);
			func2(func_arg2);
		}
	}
	else
	{
		state = ButtonState::NONE;
	}
}

void Button::Render(HDC hdc)
{
	switch (state)
	{
	case ButtonState::NONE:
	case ButtonState::UP:
		nowButton->FrameRender(hdc, pos.x, pos.y, frame, 0, true);
		break;
	case ButtonState::DOWN:
		nowButton->FrameRender(hdc, pos.x, pos.y, frame, 1, true);
		break;
	}
}
