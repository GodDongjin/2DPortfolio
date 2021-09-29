#pragma once
#pragma once
#include "CameraObject.h"

class Image;

class Effect : public CameraObject
{
private:

	Image* img;
	FPOINT pos;
	bool isActive;
	float currFrame;
	int maxFrame;
	float currTime;
	float frameTime;
	//추가
	string name;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	//추가 생성 set, get 함수
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline void SetIsActive(bool isActive) { this->isActive = isActive; }
	inline void SetName(string name) { img = ImageManager::GetSingleton()->FindImage(name); }
	inline bool GetIsActive() { return this->isActive; }
	inline void SetMaxFrame(float maxFrame) { this->maxFrame = maxFrame; }
	inline void SetFrameTime(float frameTime) { this->frameTime = frameTime; }
	inline void SetCurrFrame(float currFrame) { this->currFrame = currFrame; }
};
