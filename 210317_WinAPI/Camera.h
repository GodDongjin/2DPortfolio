#pragma once
#include "config.h"
#include "Singleton.h"

class Camera :public Singleton<Camera>
{
private:
	FPOINT cameraPos;
	FPOINT targetPos;
	FPOINT maxPos;
	FPOINT minPos;
public:

	void SetManMinPos(int minX, int minY, int maxX, int maxY);
	FPOINT GetPos();
	void SetPos(FPOINT pos) { this->targetPos = pos; }

	void AddTargetPos(FPOINT targetPos);

	void CameraMoveUpdate(int state, RECT playerRc);

};

