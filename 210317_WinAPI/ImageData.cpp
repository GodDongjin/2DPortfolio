#include "ImageData.h"
#include "ImageManager.h"

void ImageData::ImageInit()
{
	//배경 이미지
	ImageManager::GetSingleton()->AddImage("배경", "Image/caveStory/backGround/backGround.bmp", 3000, 2677);
	ImageManager::GetSingleton()->AddImage("인트로배경", "Image/caveStory/intro/intro.bmp", WINSIZE_X, WINSIZE_Y);

	//타일 이미지
	ImageManager::GetSingleton()->AddImage("STAGE1_TILE", "Image/caveStory/Tile/Stage1.bmp", 192, 480,
		6, 15, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("STAGE1_PIXEL_TILE", "Image/caveStory/Tile/Stage1CollsionTile.bmp", 192, 480,
		6, 15, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("STAGE2_TILE", "Image/caveStory/Tile/Stage2.bmp", 192, 352,
		6, 11, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("STAGE2_PIXEL_TILE", "Image/caveStory/Tile/Stage2Pixel.bmp", 192, 352,
		6, 11, true, RGB(0, 0, 0));
	
	//인게임 타일 이미지
	ImageManager::GetSingleton()->AddImage("INGAME_STAGE1_TILE", "Image/caveStory/Tile/Stage1.bmp", 192 * 1.5f, 480 * 1.5f,
		6, 15, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("INGAME_STAGE1_PIXEL_TILE", "Image/caveStory/Tile/Stage1CollsionTile.bmp", 192 * 1.5f, 480 * 1.5f,
		6, 15, true, RGB(0, 0, 0));

	ImageManager::GetSingleton()->AddImage("INGAME_STAGE2_TILE", "Image/caveStory/Tile/Stage2.bmp", 192 * 1.5f, 352 * 1.5f,
		6, 11, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("INGAME_STAGE2_PIXEL_TILE", "Image/caveStory/Tile/Stage2Pixel.bmp", 192 * 1.5f, 352 * 1.5f,
		6, 11, true, RGB(0, 0, 0));
	
	//캐릭터 이미지
	ImageManager::GetSingleton()->AddImage("RIGHT_RUN", "Image/caveStory/Player/RIGHT_RUN.bmp",
		128 / 1.5, 64 / 1.5, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("LEFT_JUMP", "Image/caveStory/Player/LEFT_JUMP.bmp",
		128 / 1.5, 64 / 1.5, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("LEFT_DOWUN", "Image/caveStory/Player/LEFT_DOWUN.bmp",
		64 / 1.5, 64 / 1.5, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("LEFT_OBJECT_COLLISION", "Image/caveStory/Player/LEFT_OBJECT_COLLISION.bmp",
		64 / 1.5, 64 / 1.5, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("LEFT_RUN", "Image/caveStory/Player/LEFT_RUN.bmp",
		128 / 1.5, 64 / 1.5, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("LEFT_IDLE", "Image/caveStory/Player/LEFT_IDLE.bmp",
		64 / 1.5, 64 / 1.5, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("LEFT_UP", "Image/caveStory/Player/LEFT_UP.bmp",
		64 / 1.5, 64 / 1.5, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("RIGHT_DOWUN", "Image/caveStory/Player/RIGHT_DOWUN.bmp",
		64 / 1.5, 64 / 1.5, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("RIGHT_IDLE", "Image/caveStory/Player/RIGHT_IDLE.bmp",
		64 / 1.5, 64 / 1.5, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("RIGHT_JUMP", "Image/caveStory/Player/RIGHT_JUMP.bmp",
		128 / 1.5, 64 / 1.5, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("RIGHT_OBJECT_COLLISION", "Image/caveStory/Player/RIGHT_OBJECT_COLLISION.bmp",
		64 / 1.5, 64 / 1.5, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("RIGHT_UP", "Image/caveStory/Player/RIGHT_UP.bmp",
		64 / 1.5, 64 / 1.5, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("UP_LEFT_JUMP", "Image/caveStory/Player/UP_LEFT_JUMP.bmp",
		64 / 1.5, 64 / 1.5, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("UP_LEFT_RUN", "Image/caveStory/Player/UP_LEFT_RUN.bmp",
		128 / 1.5, 64 / 1.5, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("UP_RIGHT_RUN", "Image/caveStory/Player/UP_RIGHT_RUN.bmp",
		128 / 1.5, 64 / 1.5, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("UP_RIGHT_JUMP", "Image/caveStory/Player/UP_RIGHT_JUMP.bmp",
		64 / 1.5, 64 / 1.5, 1, 1, true, RGB(255, 0, 255));

	//적 이미지
	ImageManager::GetSingleton()->AddImage("enemy1", "Image/caveStory/Enemy/enemy1.bmp",
		48 * 2.5, 32 * 2.5, 3, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("enemy2_IDLE", "Image/caveStory/Enemy/Enemy2/enemy2_IDLE.bmp", 48 * 2, 48 * 2, 2, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("enemy2_RUN", "Image/caveStory/Enemy/Enemy2/enemy2_RUN.bmp", 48 * 2, 48 * 2, 2, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("enemy2_DIE", "Image/caveStory/Enemy/Enemy2/enemy2_DIE.bmp", 24 * 2, 48 * 2, 1, 2, true, RGB(255, 0, 255));
	
	//보스 이미지
	ImageManager::GetSingleton()->AddImage("Boss_Run", "Image/caveStory/Boss/Boss_Run.bmp", 160 * 1.5, 144 * 1.5, 2, 2, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("Boss_Idle", "Image/caveStory/Boss/Boss_IDLE.bmp", 160 * 1.5, 144 * 1.5, 2, 2, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("Boss_Jump", "Image/caveStory/Boss/Boss_Jump.bmp", 240 * 1.5, 144 * 1.5, 3, 2, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("Boss_Fire", "Image/caveStory/Boss/Boss_Fire.bmp", 160 * 1.5, 144 * 1.5, 2, 2, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("Boss_Die", "Image/caveStory/Boss/Boss_Die.bmp", 320 * 1.5, 144 * 1.5, 4, 2, true, RGB(0, 0, 0));

	//무기 이미지
	ImageManager::GetSingleton()->AddImage("starGun", "Image/caveStory/wepown/starGun.bmp", 204 / 2, 34 / 2, 6, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("missileGun", "Image/CaveStory/wepown/misiileGun.bmp", 216, 30, 6, 1, true, RGB(255, 0, 255));
	//총알 이미지
	ImageManager::GetSingleton()->AddImage("starGunMissile", "Image/caveStory/bullte/nomalBullet.bmp", 128, 32, 4, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("missileGunMissile", "Image/caveStory/bullte/misiileBullet.bmp", 124, 32 , 4, 1, true, RGB(0, 0, 0));

	//보스 총알
	ImageManager::GetSingleton()->AddImage("BossMissile", "Image/caveStory/bullte/BossBullet.bmp",160, 40, 4, 1, true, RGB(255, 0, 255));

	//버튼 이미지
	ImageManager::GetSingleton()->AddImage("스테이지버튼", "Image/caveStory/button/button_stage.bmp", 337, 128, 6, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("세이브버튼", "Image/caveStory/button/button_save.bmp", 60, 128, 1, 2, true, RGB(255, 0, 255));

	//이팩트 이미지
	ImageManager::GetSingleton()->AddImage("starGunEffect", "Image/caveStory/Effect/starGunEffect.bmp", 64 * 2, 16 * 2, 4, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("starGunCollisionEffect", "Image/caveStory/Effect/StarGunCollisionEffect.bmp", 64 * 2, 16 * 2, 4, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("missileGunCollisionEffect", "Image/caveStory/Effect/MissileGunEffect.bmp", 128 * 2, 64 * 2, 2, 1, true, RGB(0, 0, 0));

	//UI
	ImageManager::GetSingleton()->AddImage("air", "Image/caveStory/UI/air.bmp", 66 * 3, 16 * 3, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("BossBackBar", "Image/caveStory/UI/BossBackBar.bmp", 480 * 2.4, 36, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("BossHpBar", "Image/caveStory/UI/BossHpBar.bmp", 462 * 2, 9 * 2, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("hp", "Image/caveStory/UI/hp.bmp", 39 * 3, 5 * 2, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("hpBar", "Image/caveStory/UI/hpBar.bmp", 64 * 3, 8 * 3, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("NumBer", "Image/caveStory/UI/NumBer.bmp", 160, 16, 10, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("LV", "Image/caveStory/UI/PlayerLV.bmp", 24, 13, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("BossHp", "Image/caveStory/UI/BossHpimg.bmp", 58 * 3, 14 * 2, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("division", "Image/caveStory/UI/ahffk.bmp", 16 * 2, 16 , true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("infinite", "Image/caveStory/UI/angks.bmp", 29 * 2, 16, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("gunKind", "Image/caveStory/UI/gunKind.bmp", 56 * 2.5, 28 * 2, 2, 1,true, RGB(0, 0, 0));

	//End
	ImageManager::GetSingleton()->AddImage("ending", "Image/caveStory/Credit/Credit.bmp", 5120, 480, 16, 1);
	ImageManager::GetSingleton()->AddImage("endingBack", "Image/caveStory/Credit/backGround.bmp", 1400, 900);

}
