#include "MissileManager.h"
#include "CollisionManager.h"
#include "StarGunMissile.h"
#include "MissileGunMissile.h"
#include "Weapon.h"
#include "EffectManager.h"

HRESULT MissileManager::Init(Weapon* owner)
{
    this->owner = owner;
    vMissiles.resize(10);
    
    if (this->owner->GetWeapon() == 0)
    {
        for (int i = 0; i < vMissiles.size(); i++)
        {
            vMissiles[i] = new StarGunMissile();
            vMissiles[i]->Init(owner);
        }
    }
    else if (this->owner->GetWeapon() == 1)
    {
        for (int i = 0; i < vMissiles.size(); i++)
        {
            vMissiles[i] = new MissileGunMissile();
            vMissiles[i]->Init(owner);
        }
    }
    
   

    return S_OK;
}

void MissileManager::Release()
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        SAFE_RELEASE(vMissiles[i]);
    }
}

void MissileManager::Update()
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->Update();
    }

}

void MissileManager::Render(HDC hdc)
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->Render(hdc);
    }
}

void MissileManager::Fire(FPOINT pos, float angle, float frameX)
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        if (vMissiles[i]->GetIsFired() == false)
        {
            //EffectManager::GetSingleton()->AddEffect("starGunEffect", pos, 4, 0.08);
            CollisionManager::GetSingleton()->AddMissile(vMissiles[i]);
            vMissiles[i]->SetIsFired(true);
            vMissiles[i]->SetAngle(DegToRad(angle));
            vMissiles[i]->SetPos(pos);
            vMissiles[i]->SetFrameX(frameX);
            vMissiles[i]->SetTileMap(tileImg);
            break;
        }
    }
}
