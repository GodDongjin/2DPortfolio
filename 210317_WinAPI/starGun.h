#pragma once
#include "Weapon.h"
#include "Image.h"

class starGun : public Weapon
{
private:
	Image* maxAmmo;
	Image* nowAmmo;

public:
	HRESULT Init(Player* player);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire();

	void SetPos(FPOINT pos);
};

