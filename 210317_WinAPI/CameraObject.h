#pragma once
#include "GameNode.h"

class CameraObject : public GameNode
{
protected:

	FPOINT screenPos;
	FPOINT worldPos; 
	FPOINT cameraPos;
	FPOINT tileWorldPos[TILE_Y][TILE_X];
	FPOINT tileScreenPos[TILE_Y][TILE_X];

	int state;


public:
	void UpdatePosition();
	void SetPlayerState(int state) { this->state = state; }
};

