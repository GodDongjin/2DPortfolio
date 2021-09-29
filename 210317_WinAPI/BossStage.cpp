#include "BossStage.h"
#include "Image.h"
#include "Camera.h"
#include "Player.h"
#include "TileMap.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include "GameData.h"
#include "Boss.h"
#include "EndingCredit.h"

HRESULT BossStage::Init()
{
	backGround = ImageManager::GetSingleton()->FindImage("¹è°æ");

	SceneManager::GetSingleton()->AddScene("end", new EndingCredit());

	Camera::GetSingleton()->SetManMinPos(700, 700, 800, 700);
	EffectManager::GetSingleton()->Init();

	srand(time(NULL));

	pixelMap = new Image();
	pixelMap->Init(TILE_X * INGAMETILESIZE, TILE_Y * INGAMETILESIZE);

	tileMap = new TileMap();
	tileMap->Init(2);
	tileMap->SetPixelMap(&pixelMap);

	player = new Player();
	player->Init(tileMap->GetPlayerPos(), tileMap);
	player->SetPixelMap(pixelMap);
	CollisionManager::GetSingleton()->AddPlayer(player);

	boss = new Boss();
	boss->Init(tileMap->GetPlayerPos().x + 200, tileMap->GetPlayerPos().y -  100);
	CollisionManager::GetSingleton()->AddBoss(boss);
	


	CollisionManager::GetSingleton()->AddTilePixleMap(pixelMap);

	mapPos.x = 0;
	mapPos.y = 0;

	return S_OK;
}

void BossStage::Release()
{
	SAFE_RELEASE(player);
	SAFE_RELEASE(tileMap);
	//CollisionManager::GetSingleton()->Release();

}

void BossStage::Update()
{
	EffectManager::GetSingleton()->Update();

	player->Update();
	tileMap->Update();
	boss->Update();

	
	CollisionManager::GetSingleton()->BossMissileCollision();
	CollisionManager::GetSingleton()->BossMissileTileRectCollision();
	CollisionManager::GetSingleton()->PlayerBossCollision();
	CollisionManager::GetSingleton()->BossMissilePlayerCollision();
	CollisionManager::GetSingleton()->MissileTileRectCollision();
	CollisionManager::GetSingleton()->MissilePixleCollsion();
	

	


	if (boss->GetBossDie() == true && player->GetCollisionDoor() == true)
	{
		SceneManager::GetSingleton()->ChangeScene("end");
	}

}

void BossStage::Render(HDC hdc)
{
	int screenPosX = mapPos.x + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x;
	int screenPosY = mapPos.y + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y;
	backGround->Render(hdc, screenPosX, screenPosY);

	tileMap->Render(hdc);
	//pixelMap->Render(hdc, mapPos.x + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x,
	//	mapPos.y +(WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y);

	player->Render(hdc);
	boss->Render(hdc);
	EffectManager::GetSingleton()->Render(hdc);
}
