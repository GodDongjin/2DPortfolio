#pragma once
#include "Missile.h"

class StarGunMissile : public Missile
{
private:


public:
	HRESULT Init(Weapon* owner);
	void Release();
	void Update();
	void Render(HDC hdc);
	void SetIsFired(bool isFired);
	void LeftPixelCollision();
};

