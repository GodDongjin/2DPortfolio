#pragma once
#include "GameNode.h"

class Image;

class EndingCredit : public GameNode
{
private:
	Image* backGround;
	Image* endingCredit;

	float frame;
	float frameTime;


public:

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	~EndingCredit() {};
};

