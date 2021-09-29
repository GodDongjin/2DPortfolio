#pragma once
#include "Singleton.h"

class Player;

class GameData : public Singleton<GameData>
{
private:
	
	Player* player;

public:
	void SetPlayer(Player* player) { this->player = player; }
	Player* GetPlayer() { return this->player; }
};

