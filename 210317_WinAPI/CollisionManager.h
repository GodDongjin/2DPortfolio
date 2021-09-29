#pragma once
#include "Singleton.h"
#include "config.h"

class Player;
class Enemy;
class Missile;
class TileMap;
class Image;
class Boss;
class BossMissile;

class CollisionManager : public Singleton <CollisionManager>
{
private:
	vector<Missile*> vMissiles;
	vector<TILE_INFO*> vTiles;
	vector<Enemy*> vEnemys;
	vector<BossMissile*> vBossMissile;

	Image* tilePixelMap;
	Player* player;
	Boss* boss;

	float deltaX;
	float deltaY;
	float length;
public:

	HRESULT Init();
	void Release();
	void AddTilePixleMap(Image* pixleMap) { this->tilePixelMap = pixleMap;};
	void AddMissile(Missile* missile) { vMissiles.push_back(missile); }
	void AddTile(TILE_INFO* tileInfo) { vTiles.push_back(tileInfo); }
	void AddEnemy(Enemy* enemy) { vEnemys.push_back(enemy); }
	void AddPlayer(Player* player) { this->player = player; }
	void AddBoss(Boss* boss) { this->boss = boss; }
	void AddBossMissile(BossMissile* bossMissile) { vBossMissile.push_back(bossMissile); }
	void MissileRelese(Missile* missile) 
	{
		for (int i = 0; i < vMissiles.size(); i++)
		{
			if (vMissiles[i] == missile)
			{
				vMissiles.erase(find(vMissiles.begin(), vMissiles.end(), vMissiles[i]));
			}
		}
	}

	void EnemyRelese(Enemy* enemy) {
		for (int i = 0; i < vEnemys.size(); i++)
		{
			if (vEnemys[i] == enemy)
			{
				vEnemys.erase(find(vEnemys.begin(), vEnemys.end(), vEnemys[i]));
			}
		}
	}

	void TileRelese(TILE_INFO* tileInfo) {
		for (int i = 0; i < vTiles.size(); i++)
		{
			if (vTiles[i] == tileInfo)
			{
				vTiles.erase(find(vTiles.begin(), vTiles.end(), vTiles[i]));
			}
		}
	}

	//void BossMissile(BossMissile* bossMissile)
	//{
	//	for (int i = 0; i < vBossMissile.size(); i++)
	//	{
	//		if (vBossMissile[i] == bossMissile)
	//		{
	//			vBossMissile.erase(find(vBossMissile.begin(), vBossMissile.end(), vBossMissile[i]));
	//		}
	//	}
	//}

	void MissileTileRectCollision();
	void MissilePixleCollsion();
	void EnemyTileRectCollision();
	void EnemyOutLookCollision();
	void EnemyMissileCollision();
	void EnemyPixleCollsion();
	void BossTileRectCollision();
	void BossMissileCollision();
	void BossMissileTileRectCollision();
	void PlayerEnemyCollision();
	void PlayerBossCollision();
	void BossMissilePlayerCollision();

	void TileRander(HDC hdc);
};

