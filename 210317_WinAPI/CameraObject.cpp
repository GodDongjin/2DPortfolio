#include "CameraObject.h"
#include "Camera.h"

void CameraObject::UpdatePosition()
{
	cameraPos = Camera::GetSingleton()->GetPos();
	
	screenPos.x = worldPos.x + (WINSIZE_X / 2) - cameraPos.x;
	screenPos.y = worldPos.y + (WINSIZE_Y / 2) - cameraPos.y;

	for(int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			tileScreenPos[i][j].x = tileWorldPos[i][j].x + (WINSIZE_X / 2) - cameraPos.x;
			tileScreenPos[i][j].y = tileWorldPos[i][j].y + (WINSIZE_Y / 2) - cameraPos.y;
		}
	}
}
