#pragma once
#include "CameraObject.h"

class Image;
class BossMissileManager;


class Boss : public CameraObject
{
public:
	enum class PATTERN
	{
		ILDE,
		RUN,
		JUMP,
		SHOOT,
		DIE
	};

	enum class SEE
	{
		LEFT,
		RIGHT
	};

private:
	Image* img;
	Image* hpBar;
	Image* hpBarBack;
	Image* BossHp;


	BossMissileManager* missile;

	FPOINT pos;
	FPOINT jumpStartPos;
	
	PATTERN pattern;
	SEE see;

	RECT hitBox;
	RECT collsionBox;
	RECT attckBox;

	int tileCollisionIndex[9];
	int damege;
	int fireCount;
	
	int hp;
	float moveSpeed;
	
	int currFrameX;
	float frameX;
	float frameY;
	float frameTime;
	float frameMaxTime;
	float maxFrame;

	float gravity;
	float jumpPower;
	float jumpDaltaTime;
	float jumpHeight;
	float jumpPrevHeight;

	float moveTime;
	float runTime;
	float jumpTime;
	float stayTime;
	float fierTime;
	float fireDelay;

	float DieTime;
	float DieDelay;

	float angle;

	int runCount;
	int jumpCount;

	bool isAlive;
	bool isLanding;
	bool isMove;
	bool isLeft;
	bool isJump;
	bool isDirectionChange;
	bool isLeftCollsion;
	bool isRightCollsion;
	bool isFire;
	bool isDie;


	char szText[128];

public:
	HRESULT Init(float posX, float posY);
	void Release();
	void Update();
	void Render(HDC hdc);

	void FrameWrok();
	void State();
	void Move();
	void Jump();
	void TileCollisionIndex();
	void ChangeDirection();
	void Gravity();
	void Fire();
	void DieFrameWrok();

	RECT GetCollsionBox() { return this->collsionBox; }
	RECT GetHitBox() { return this->hitBox; }
	RECT GetAttckBox() { return this->attckBox; }

	int GetTileCollisionIndex(int index) { return this->tileCollisionIndex[index]; }

	inline void SetIsLeftCollison(bool isLeftCollsion) { this->isLeftCollsion = isLeftCollsion; }
	inline void SetIsRightCollison(bool isRightCollsion) { this->isRightCollsion = isRightCollsion; }
	inline void SetIsLanding(bool isLanding) { this->isLanding = isLanding; };

	inline void SetPosX(float posX) { this->pos.x = posX; }
	inline void SetPosY(float posY) { this->pos.y = posY; }

	inline void SetIsJump(bool isJump) { this->isJump = isJump; }
	inline bool GetIsJump() { return this->isJump; }

	inline void SetHp(int hp) { this->hp = hp; }
	inline int GetHp() { return this->hp; }

	inline Image* GetImage() { return img; }

	inline int GetDamege() { return this->damege; }

	inline bool GetBossDie() { return this->isDie; }
};

