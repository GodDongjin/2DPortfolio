#include "BossMissileManager.h"
#include "MissileManager.h"
#include "CollisionManager.h"
#include "BossMissile.h"
#include "MissileGunMissile.h"
#include "EffectManager.h"

HRESULT BossMissileManager::Init(Boss* owner)
{
    this->owner = owner;
    vMissiles.resize(10);

    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i] = new BossMissile();
        vMissiles[i]->Init(this->owner);
    }

    return S_OK;
}

void BossMissileManager::Release()
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        SAFE_RELEASE(vMissiles[i]);
    }
}

void BossMissileManager::Update()
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->Update();


    }

}

void BossMissileManager::Render(HDC hdc)
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->Render(hdc);
    }
}

void BossMissileManager::AddMsiile()
{
    vMissiles.push_back(new BossMissile());
    vMissiles[vMissiles.size() - 1]->Init(owner);
    CollisionManager::GetSingleton()->AddBossMissile(vMissiles[vMissiles.size() - 1]);
}

void BossMissileManager::Fire(FPOINT pos, float angle)
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        if (vMissiles[i]->GetIsFired() == false)
        {
            CollisionManager::GetSingleton()->AddBossMissile(vMissiles[i]);
            vMissiles[i]->SetIsFired(true);
            vMissiles[i]->SetAngle(DegToRad(angle));
            vMissiles[i]->SetPos(pos);
            break;
        }
    }
   
}
