#include "BattleScene.h"
#include "Image.h"
#include "Camera.h"
#include "Player.h"
#include "TileMap.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include "Stage2.h"
#include "GameData.h"

HRESULT BattleScene::Init()
{
	backGround = ImageManager::GetSingleton()->FindImage("배경");
	SceneManager::GetSingleton()->AddScene("스테이지2", new Stage2());
	EffectManager::GetSingleton()->Init();
	Camera::GetSingleton()->SetManMinPos(700, 0, 1700, 1180);
	srand(time(NULL));

	pixelMap = new Image();
	pixelMap->Init(TILE_X * INGAMETILESIZE, TILE_Y * INGAMETILESIZE);

	tileMap = new TileMap();
	tileMap->Init(0);
	tileMap->SetPixelMap(&pixelMap);

	player = new Player();
	player->Init(tileMap->GetPlayerPos(), tileMap);
	player->SetPixelMap(pixelMap);
	CollisionManager::GetSingleton()->AddPlayer(player);

	enemyManager = new EnemyManager();
	enemyManager->SetEnemy1Count(3);
	enemyManager->SetEnemy2Count(5);
	enemyManager->SetPos(tileMap->GetVE_pos());
	enemyManager->Init(); 

	CollisionManager::GetSingleton()->AddTilePixleMap(pixelMap);

	mapPos.x = 0;
	mapPos.y = 0;
	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(player);
	SAFE_RELEASE(tileMap);
	//CollisionManager::GetSingleton()->Release()
	SAFE_RELEASE(enemyManager);


}

void BattleScene::Update()
{
	EffectManager::GetSingleton()->Update();

	player->Update();
	tileMap->Update();
	enemyManager->Update();

	
	
	CollisionManager::GetSingleton()->EnemyMissileCollision();
	CollisionManager::GetSingleton()->PlayerEnemyCollision();
	CollisionManager::GetSingleton()->EnemyPixleCollsion();
	//CollisionManager::GetSingleton()->EnemyTileRectCollision();
	CollisionManager::GetSingleton()->EnemyOutLookCollision();
	CollisionManager::GetSingleton()->EnemyTileRectCollision();
	CollisionManager::GetSingleton()->MissileTileRectCollision();
	CollisionManager::GetSingleton()->MissilePixleCollsion();

	


	if (player->GetCollisionDoor() == true)
	{
		GameData::GetSingleton()->SetPlayer(this->player);
		SceneManager::GetSingleton()->ChangeScene("스테이지2");
	}
}

void BattleScene::Render(HDC hdc)
{
	int screenPosX = mapPos.x + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x;
	int screenPosY = mapPos.y + (WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y;
	backGround->Render(hdc, screenPosX, screenPosY);

	tileMap->Render(hdc);
	//pixelMap->Render(hdc, mapPos.x + (WINSIZE_X / 2) - Camera::GetSingleton()->GetPos().x,
	//	mapPos.y +(WINSIZE_Y / 2) - Camera::GetSingleton()->GetPos().y);

	player->Render(hdc);
	enemyManager->Render(hdc);
	EffectManager::GetSingleton()->Render(hdc);
}



