#include "EffectManager.h"
#include "Effect.h"

HRESULT EffectManager::Init()
{
	vEffect.resize(10);
	for (int i = 0; i < vEffect.size(); i++)
	{
		vEffect[i] = new Effect();
		vEffect[i]->Init();
	}
	return S_OK;
}

void EffectManager::Release()
{
	for (int i = 0; i < vEffect.size(); i++)
	{
		SAFE_RELEASE(vEffect[i]);
	}
}

void EffectManager::Update()
{
	for (int i = 0; i < vEffect.size(); i++)
	{
		vEffect[i]->Update();
	}
}

void EffectManager::Render(HDC hdc)
{
	for (int i = 0; i < vEffect.size(); i++)
	{
		vEffect[i]->Render(hdc);
	}
}

void EffectManager::AddEffect(string name, FPOINT pos, int maxFrame, float frameTime)
{
	for (int i = 0; i < vEffect.size(); i++)
	{
		if (vEffect[i]->GetIsActive() == false)
		{
			vEffect.push_back(new Effect());

			vEffect[i]->SetPos(pos);
			vEffect[i]->SetName(name);
			vEffect[i]->SetIsActive(true);
			vEffect[i]->SetMaxFrame(maxFrame);
			vEffect[i]->SetFrameTime(frameTime);
			vEffect[i]->SetCurrFrame(0);
			break;
		}
	}
}


