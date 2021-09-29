#include "Camera.h"

void Camera::SetManMinPos(int minX, int minY, int maxX, int maxY)
{
	minPos.x = minX;
	minPos.y = minY;
	maxPos.x = maxX;
	maxPos.y = maxY;

}

FPOINT Camera::GetPos()
{
	return this->cameraPos;
}

void Camera::AddTargetPos(FPOINT targetPos)
{
	if (targetPos.x < minPos.x) { targetPos.x = minPos.x; }
	if (targetPos.x > maxPos.x) { targetPos.x = maxPos.x; }
	if (targetPos.y < minPos.y) { targetPos.y = minPos.y; }
	if (targetPos.y > maxPos.y) { targetPos.y = maxPos.y; }

	cameraPos.x = targetPos.x;// *TimerManager::GetSingleton()->GetElapsedTime();
	cameraPos.y = targetPos.y;

}

void Camera::CameraMoveUpdate(int state, RECT playerRc)
{
	

}
