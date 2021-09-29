#pragma once
#include "Singleton.h"
#include "config.h"

class Effect;

class EffectManager : public Singleton<EffectManager>
{
private:
	vector<Effect*> vEffect;


public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void AddEffect(string name, FPOINT pos, int maxFrame, float frameTime = 0.08f);

	void ReleaseEffect(Effect* effect) {
		for (int i = 0; i < vEffect.size(); i++)
		{
			if (vEffect[i] == effect)
			{
				vEffect.erase(find(vEffect.begin(), vEffect.end(), vEffect[i]));
			}
		}
	}
};
