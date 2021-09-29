#include "Missile.h"
#include "Weapon.h"

HRESULT Missile::Init(Weapon* owner)
{
	

    return S_OK;
}

void Missile::Release()
{

}

void Missile::Update()
{
	
}

void Missile::Render(HDC hdc)
{
	
}


void Missile::SetIsFired(bool isFired)
{
	this->isFired = isFired;
	pos.x = owner->GetPos().x;
	pos.y = owner->GetPos().y;
}
