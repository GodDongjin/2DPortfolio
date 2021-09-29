#include "CollisionManager.h"
#include "Missile.h"
#include "CommonFunction.h"
#include "EffectManager.h"
#include "Image.h"
#include "Enemy.h"
#include "Player.h"
#include "Boss.h"
#include "Camera.h"
#include "BossMissile.h"

HRESULT CollisionManager::Init()
{
	deltaX = 0;
	deltaY = 0;
	length = 0;
	return S_OK;
}

void CollisionManager::Release()
{

}

void CollisionManager::MissileTileRectCollision()
{
	for (int i = 0; i < vMissiles.size(); i++)
	{
		for (int j = 0; j < vTiles.size(); j++)
		{
			if (RectInRect(vMissiles[i]->GetMissileRect(), vTiles[j]->rcTile))
			{
				if (vTiles[j]->tileType == TILETPYE::Wall)
				{
					if (vMissiles[i]->GetMissileKind() == Missile::MISSLEKIND::STAR)
						EffectManager::GetSingleton()->AddEffect("starGunCollisionEffect", vMissiles[i]->GetPos(), 4, 0.08);
					else if (vMissiles[i]->GetMissileKind() == Missile::MISSLEKIND::MISSILE)
					{
						EffectManager::GetSingleton()->AddEffect("missileGunCollisionEffect", vMissiles[i]->GetPos(), 4, 0.8);
					}
					vMissiles[i]->SetIsFired(false);
					vMissiles.erase(vMissiles.begin() + i);
					break;
				}
			}
		}
	}
}

void CollisionManager::MissilePixleCollsion()
{
	for (int i = 0; i < vMissiles.size(); i++)
	{
		COLORREF colorY;
		int Ry;
		int Gy;
		int By;
		float currPosY = vMissiles[i]->GetPos().y;
		float posY = 0;
	
	
		// 픽셀 충돌 확인
		for (int j = currPosY - 10; j < currPosY + 10; j++)
		{
			colorY = GetPixel(tilePixelMap->GetMemDC(), vMissiles[i]->GetPos().x, j);
	
			Ry = GetRValue(colorY);
			Gy = GetGValue(colorY);
			By = GetBValue(colorY);
	
			if ((Ry == 255 && Gy == 0 && By == 0))
			{
				//위치 고정
				if (vMissiles[i]->GetMissileKind() == Missile::MISSLEKIND::STAR)
					EffectManager::GetSingleton()->AddEffect("starGunCollisionEffect", vMissiles[i]->GetPos(), 4, 0.08);
				else if (vMissiles[i]->GetMissileKind() == Missile::MISSLEKIND::MISSILE)
				{
					EffectManager::GetSingleton()->AddEffect("missileGunCollisionEffect", vMissiles[i]->GetPos(), 4, 0.8);
				}
				vMissiles[i]->SetIsFired(false);
				vMissiles.erase(vMissiles.begin() + i);
				
				break;
	
			}
		}
	}

	
}

void CollisionManager::EnemyTileRectCollision()
{
	int collisionIndex;
	for (int i = 0; i < vEnemys.size(); i++)
	{
		//collisionIndex = vEnemys[i]->GetTileCollisionIndex(7);
		if (vTiles[vEnemys[i]->GetTileCollisionIndex(7)]->tileType == TILETPYE::Wall)
		{
			if (RectInRect(vTiles[vEnemys[i]->GetTileCollisionIndex(7)]->rcTile, vEnemys[i]->GetCollsionBox()))
			{
				vEnemys[i]->SetIsLanding(true);
				
				vEnemys[i]->SetPosY(vTiles[vEnemys[i]->GetTileCollisionIndex(7)]->rcTile.top - vEnemys[i]->GetImage()->GetFrameHeight());
			}
		
		}
		else
		{
			vEnemys[i]->SetIsLanding(false);
		}
	
		
		if (vTiles[vEnemys[i]->GetTileCollisionIndex(5)]->tileType == TILETPYE::Wall)
		{
			if (RectInRect(vTiles[vEnemys[i]->GetTileCollisionIndex(5)]->rcTile, vEnemys[i]->GetCollsionBox()))
			{
				vEnemys[i]->SetIsRightCollison(true);
			}
		}
		else
		{
			vEnemys[i]->SetIsRightCollison(false);
		}
		
		
		
		if (vTiles[vEnemys[i]->GetTileCollisionIndex(3)]->tileType == TILETPYE::Wall)
		{
			if (RectInRect(vTiles[vEnemys[i]->GetTileCollisionIndex(3)]->rcTile, vEnemys[i]->GetCollsionBox()))
			{
				vEnemys[i]->SetIsLeftCollison(true);
			}
		}
		else
		{
			vEnemys[i]->SetIsLeftCollison(false);
		}
	}
}

void CollisionManager::EnemyOutLookCollision()
{
	for (int i = 0; i < vEnemys.size(); i++)
	{
		deltaX = vEnemys[i]->GetPos().x - player->GetPos().x;
		deltaY = vEnemys[i]->GetPos().y - player->GetPos().y;
		length = sqrt(deltaX * deltaX + deltaY * deltaY);


		if (length < vEnemys[i]->GetOutLookDistance())
		{
			if (player->GetPos().x < vEnemys[i]->GetPos().x)
			{
				vEnemys[i]->SetIsLeft(true);
			}

			if (player->GetPos().x > vEnemys[i]->GetPos().x) 
			{
				vEnemys[i]->SetIsLeft(false);
			}

			if (!vEnemys[i]->GetIsMove())
			{
				vEnemys[i]->SetIsMove(true);
			}
		}
		else
		{
			vEnemys[i]->SetIsMove(false);
		}

		
	}

}

void CollisionManager::EnemyMissileCollision()
{

	for (int i = 0; i < vEnemys.size(); i++)
	{
		for (int j = 0; j < vMissiles.size(); j++)
		{
			if (RectInRect(vEnemys[i]->GetHitBox(), vMissiles[j]->GetMissileRect()))
			{
				if (vMissiles[j]->GetMissileKind() == Missile::MISSLEKIND::STAR)
					EffectManager::GetSingleton()->AddEffect("starGunEffect", vMissiles[j]->GetPos(), 4, 0.08);
				else if (vMissiles[j]->GetMissileKind() == Missile::MISSLEKIND::MISSILE)
				{
					EffectManager::GetSingleton()->AddEffect("missileGunCollisionEffect", vMissiles[j]->GetPos(), 4, 0.8);
				}
				vEnemys[i]->SetHp(vEnemys[i]->GetHp() - vMissiles[j]->GetDamege());
				vMissiles[j]->SetIsFired(false);
				
				break;
			}
		}
	}
}

void CollisionManager::EnemyPixleCollsion()
{
	for (int i = 0; i < vEnemys.size(); i++)
	{
		COLORREF colorY;
		int Ry;
		int Gy;
		int By;
		float currPosY = vEnemys[i]->GetPos().y + (vEnemys[i]->GetImage()->GetFrameHeight() / 2);
 		float posY = 0;


		// 픽셀 충돌 확인
		for (int j = currPosY - 10; j < currPosY + 10; j++)
		{
			colorY = GetPixel(tilePixelMap->GetMemDC(), vEnemys[i]->GetPos().x, j);

			Ry = GetRValue(colorY);
			Gy = GetGValue(colorY);
			By = GetBValue(colorY);

			if ((Ry == 255 && Gy == 0 && By == 0))
			{
				vEnemys[i]->SetIsPixleCollison(true);
				vEnemys[i]->SetPosY(j - (vEnemys[i]->GetImage()->GetFrameHeight()) + 6);
				return;

			}
			else
			{
				vEnemys[i]->SetIsPixleCollison(false);
			}
		}
	}
}

void CollisionManager::BossTileRectCollision()
{
	if (vTiles[boss->GetTileCollisionIndex(7)]->tileType == TILETPYE::Wall)
	{
		if (RectInRect(vTiles[boss->GetTileCollisionIndex(7)]->rcTile, boss->GetCollsionBox()))
		{
			boss->SetIsLanding(true);
			boss->SetPosY(vTiles[boss->GetTileCollisionIndex(7)]->rcTile.top - boss->GetImage()->GetFrameHeight());
		}
	}
	else
	{
		boss->SetIsLanding(false);
	}
	if (vTiles[boss->GetTileCollisionIndex(3)]->tileType == TILETPYE::Wall)
	{
		if (RectInRect(vTiles[boss->GetTileCollisionIndex(3)]->rcTile, boss->GetCollsionBox()))
		{
			boss->SetIsLeftCollison(true);
		}
	}
	else
	{
		boss->SetIsLeftCollison(false);
	}
	if (vTiles[boss->GetTileCollisionIndex(5)]->tileType == TILETPYE::Wall)
	{
		if (RectInRect(vTiles[boss->GetTileCollisionIndex(5)]->rcTile, boss->GetCollsionBox()))
		{
			boss->SetIsRightCollison(true);
		}
	}
	else
	{
		boss->SetIsRightCollison(false);
	}
	
}

void CollisionManager::BossMissileCollision()
{
	for (int i = 0; i < vMissiles.size(); i++)
	{
		int bossHp = boss->GetHp();
		if (RectInRect(boss->GetHitBox(), vMissiles[i]->GetMissileRect()))
		{
			if (vMissiles[i]->GetMissileKind() == Missile::MISSLEKIND::STAR)
				EffectManager::GetSingleton()->AddEffect("starGunEffect", vMissiles[i]->GetPos(), 4, 0.08);
			else if (vMissiles[i]->GetMissileKind() == Missile::MISSLEKIND::MISSILE)
			{
				EffectManager::GetSingleton()->AddEffect("missileGunCollisionEffect", vMissiles[i]->GetPos(), 4, 0.8);
			}
			boss->SetHp(bossHp - vMissiles[i]->GetDamege());
			vMissiles[i]->SetIsFired(false);
			
			break;
		}
		
	}
}

void CollisionManager::BossMissileTileRectCollision()
{
	for (int i = 0; i < vBossMissile.size(); i++)
	{
		for (int j = 0; j < vTiles.size(); j++)
		{
			if (RectInRect(vBossMissile[i]->GetMissileRect(), vTiles[j]->rcTile))
			{
				if (vTiles[j]->tileType == TILETPYE::Wall)
				{
					//EffectManager::GetSingleton()->AddEffect("starGunEffect", vBossMissile[i]->GetPos(), 4, 0.08);
					vBossMissile[i]->SetIsFired(false);
					vBossMissile.erase(vBossMissile.begin() + i);
					break;
				}
			}
		}
	}
}

void CollisionManager::PlayerEnemyCollision()
{
	int playerHp = player->GetHp();

	for (int i = 0; i < vEnemys.size(); i++)
	{
		if (RectInRect(player->GetHitBox(), vEnemys[i]->GetHitBox()) && player->GetIsHit() == false)
		{
			player->SetIsHit(true);
			player->SetHp(playerHp - vEnemys[i]->GetDamege());
		}
	}
}

void CollisionManager::PlayerBossCollision()
{
	int playerHp = player->GetHp();
	
	if (RectInRect(player->GetHitBox(), boss->GetAttckBox()) && player->GetIsHit() == false)
	{
		player->SetIsHit(true);
		player->SetHp(playerHp - boss->GetDamege());
	}
}


void CollisionManager::BossMissilePlayerCollision()
{
	int playerHp = player->GetHp();
	for (int i = 0; i < vBossMissile.size(); i++)
	{
		if (RectInRect(player->GetHitBox(), vBossMissile[i]->GetMissileRect()) && player->GetIsHit() == false)
		{
			player->SetIsHit(true);
			player->SetHp(playerHp - vBossMissile[i]->GetDamege());
			vBossMissile[i]->SetIsFired(false);
			vBossMissile.erase(vBossMissile.begin() + i);
			break;
		}
	}

}

void CollisionManager::TileRander(HDC hdc)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < vEnemys.size(); j++)
		{
			Rectangle(hdc, vTiles[vEnemys[j]->GetTileCollisionIndex(i)]->rcTile.left + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x,
				vTiles[vEnemys[j]->GetTileCollisionIndex(i)]->rcTile.top + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y,
				vTiles[vEnemys[j]->GetTileCollisionIndex(i)]->rcTile.right + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x,
				vTiles[vEnemys[j]->GetTileCollisionIndex(i)]->rcTile.bottom + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y);
		}
		
	}
}
