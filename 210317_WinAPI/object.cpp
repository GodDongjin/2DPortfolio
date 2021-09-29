#include "object.h"
#include "CommonFunction.h"

HRESULT object::Init()
{

	//worldPos.x = WINSIZE_X / 2;
	//worldPos.y = WINSIZE_Y / 2;
	//pos.x = worldPos.x;
	//pos.y = worldPos.y;
	////
	
	//
	//
	//
	//rc = GetRect(worldPos.x, worldPos.y, 50, 50);

	return S_OK;
}

void object::Release()
{
}

void object::Update()
{

	

	CameraObject::UpdatePosition();
}

void object::Render(HDC hdc)
{
	//RenderRect(hdc, pos.x, pos.y, 100, 100);
	//RenderRect(hdc, worldPos.x, worldPos.y, 50, 50);
}
