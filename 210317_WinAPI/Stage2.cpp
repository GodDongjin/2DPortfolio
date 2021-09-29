#include "Stage2.h"
#include "Image.h"
#include "Camera.h"
#include "Player.h"
#include "TileMap.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include "GameData.h"
#include "BossStage.h"

HRESULT Stage2::Init()
{
	backGround = ImageManager::GetSingleton()->FindImage("배경");
	SceneManager::GetSingleton()->AddScene("보스", new BossStage());
	EffectManager::GetSingleton()->Init();
	Camera::GetSingleton()->SetManMinPos(700, 0, 1700, 1180);

	srand(time(NULL));

	pixelMap = new Image();
	pixelMap->Init(TILE_X * INGAMETILESIZE, TILE_Y * INGAMETILESIZE);

	tileMap = new TileMap();
	tileMap->Init(1);
	tileMap->SetPixelMap(&pixelMap);

	player = new Player();
	player->Init(tileMap->GetPlayerPos(), tileMap);
	player->SetPixelMap(pixelMap);
	CollisionManager::GetSingleton()->AddPlayer(player);

	enemyManager = new EnemyManager();
	enemyManager->SetEnemy1Count(2);
	enemyManager->SetEnemy2Count(5);
	enemyManager->SetPos(tileMap->GetVE_pos());
	enemyManager->Init();

	

	CollisionManager::GetSingleton()->AddTilePixleMap(pixelMap);

	mapPos.x = 0;
	mapPos.y = 0;

	return S_OK;
}

void Stage2::Release()
{
	SAFE_RELEASE(player);
	SAFE_RELEASE(tileMap);
	SAFE_RELEASE(enemyManager);

}

void Stage2::Update()
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
		SceneManager::GetSingleton()->ChangeScene("보스");
	}


}

void Stage2::Render(HDC hdc)
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
