#pragma once
#include "CameraObject.h"

class object : public CameraObject
{
private:
	RECT rc;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~object() {};
};

