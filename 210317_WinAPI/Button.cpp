#include "Button.h"
#include "Image.h"
#include "TilemapTool.h"

/*
	�ǽ�1. ��ư �̹����� ���̺�, �ε忡 �°� ����
	�ǽ�2. ���������� ������ �� �ִ� ��ư�� �߰��� ����
	�ǽ�3. �߰��� ��ư(�������� ��ȯ)�� ���� �����ϵ��� �ڵ� ����
*/

HRESULT Button::Init(const char* fileName, int posX, int posY, int key /* ��ư ��� */)
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

			// ��ư ��� ���� : ���̺�, �ε�
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
