#pragma once
#include "GameNode.h"

class Image;

class IntroScene : public GameNode
{
private:
	Image* introBackGround;
	Image* choise;

	FPOINT pos;

	float frame;
	float time;

	int count;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	
	virtual ~IntroScene() {};

};

