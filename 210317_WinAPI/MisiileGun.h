#pragma once
#include "Weapon.h"

class MisiileGun : public Weapon
{
private:
	Image* maxAmmo1;
	Image* maxAmmo2;

	Image* nowAmmo1;
	Image* nowAmmo2;

	int nowMissileCount;
	int nowCount[2];

	int maxMissileCount;
	int maxCount[2];
public:
	HRESULT Init(Player* player);
	void Release();
	void Update();
	void Render(HDC hdc);
	void NumBerIndex();

	void Fire();
	void SetPos(FPOINT pos);
};

