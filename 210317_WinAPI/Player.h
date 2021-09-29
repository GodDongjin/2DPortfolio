#pragma once
#include "CameraObject.h"

class Image;
class TileMap;
class Weapon;

enum STATE
{
	IDLE,
	UP,
	DOWUN,
	RUN,
	OBJECT_COLLISION,
	JUMP_UP,
	JUMP_DOWN
};

enum SEE
{
	LEFT,
	RIGHT,
};

class Player : public CameraObject
{
private:
	Image* img;
	FPOINT pos;
	FPOINT jumpStartPos;
	STATE state;
	SEE see;
	//bool isCollision;

	RECT collisionBox;
	RECT hitBox;

	int playerIdxX[9];
	int playerIdxY[9];
	int nowWeapon;
	int air;
	int hp;

	float moveSpeed;
	float frame;
	float frameTime;
	float maxFrame;
	float time;
	float gravity;
	float jumpPower;
	float jumpTime;
	float jumpHeight;
	float jumpPrevHeight;
	float stayTime;
	float airTime;

	float stateObjectTime;

	float hitDelayTime;

	Image* pixelMap;

	bool isJump;
	bool collisionDoor;
	bool isCheking;
	bool isLeft;
	bool isLanding;
	bool isMove;
	bool isPixelCollison;
	bool isWater;
	bool isAlive;
	bool isHit;

	vector<Weapon*> vWeapon;

	TileMap* tileMap;

	char szText[128];

	int hpNum[3];
	int airNum[3];

	Image* hpState;
	Image* hpBar;
	Image* Lv;
	Image* airState;

	Image* hpNumBer1;
	Image* hpNumBer2;
	Image* hpNumBer3;

	Image* airNumBer1;
	Image* airNumBer2;
	Image* airNumBer3;
public:
	HRESULT Init(FPOINT pos, TileMap* tileMap);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void playerState(STATE state);
	void changeState();
	void frameWrok();
	void jump();
	void FrameReset();
	void Gravity();
	void Water();

	void Times();

	void RectCollision();
	void PixelCollision();
	void BottomPixelCollision();
	void DoorPixelCollision();
	void WaterPixelCollision();

	void HitDelay();

	void Die();

	void UiInit();
	void UiRender(HDC hdc);
	void NumBerIndex();

	STATE GetState() { return this->state; }
	SEE GetSee() { return this->see; }
	FPOINT GetPos() { return this->pos; }
	Image* GetImage() { return this->img; }
	Image* GetTileMap() { return this->pixelMap; }
	bool GetCollisionDoor() { return this->collisionDoor; }
	bool GetIsLeft() { return this->isLeft; }

	bool GetIsHit() { return this->isHit; }
	void SetIsHit(bool isHit) { this->isHit = isHit; }

	void SetPosY(float posY) { this->pos.y = posY; }
	void SetPosX(float posX) { this->pos.x = posX; }
	void SetIsJump(bool isJump) { this->isJump = isJump; }
	void SetPixelMap(Image* pixelMap) { this->pixelMap = pixelMap; }

	//void SetJump(float jumpPower) { this->jumpPower = jumpPower; } 

	RECT GetCollisionRect() { return this->collisionBox; }
	RECT GetHitBox() { return this->hitBox; }
	void SetIsCollision(int collisionBoxLeft, int collisionBoxRight, int collisionBoxTop, int collisionBoxBottom) { this->collisionBox.left = collisionBoxLeft, this->collisionBox.right = collisionBoxRight,
		this->collisionBox.top = collisionBoxTop; this->collisionBox.bottom = collisionBoxBottom; }

	void SetHp(int hp) { this->hp = hp; }
	int GetHp() { return this->hp; }
};

