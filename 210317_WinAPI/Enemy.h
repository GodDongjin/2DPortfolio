#pragma once
#include "CameraObject.h"

// TODO : 업캐스팅, 다운캐스팅 설명
class Image;
class MissileManager;

class Enemy : public CameraObject
{
protected:
	Image* img;
	FPOINT pos;
	string name;
	FPOINT jumpStartPos;
	
	RECT hitBox;
	RECT collsionBox;
	RECT outLook;

	EnemyState state;

	float jumpTime;
	float jumpHeight;
	float jumpPower;
	float jumpPrevHeight;

	int tileCollisionIndex[9];
	int damege;
	int currFrameX;
	int hp;
	float moveSpeed;
	float angle;
	int fireCount;

	float frameX;
	float frameY;
	float frameTime;
	float maxFrame;

	float moveTime;
	float gravity;
	float outLookDistance;


	float randomTime;
	float maxRandomTime;

	bool isAlive;
	bool isLanding;
	bool isMove;
	bool isLeft;
	bool isJump;

	bool isPixleCollsion;
	bool isLeftCollsion;
	bool isRightCollsion;
public:
	virtual HRESULT Init(float posX = 0, float posY = 0);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Move() = 0;
	virtual void FrameWrok() = 0;
	virtual void TileCollisionIndex() = 0;
	virtual void Gravity() = 0;

	// get, set
	inline void SetState(EnemyState state) { this->state = state; }
	inline EnemyState GetState() { return state; }

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline void SetPosX(float posX) { this->pos.x = posX; }
	inline void SetPosY(float posY) { this->pos.y = posY; }
	inline FPOINT GetPos() { return this->pos; }

	inline void SetHp(int hp) { this->hp = hp; }
	inline int GetHp() { return this->hp; }

	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }
	inline void SetIsLeft(bool isLeft) { this->isLeft = isLeft; }

	inline void SetIsLanding(bool isLanding) { this->isLanding = isLanding; };
	inline void SetIsMove(bool isMove) { this->isMove = isMove; }
	inline bool GetIsMove() { return this->isMove; }
	inline Image* GetImage() { return img; }

	inline RECT GetOutLookRect() { return this->outLook; }
	inline RECT GetHitBox() { return this->hitBox; }
	inline RECT GetCollsionBox() { return this->collsionBox; }
	inline int GetTileCollisionIndex(int index) { return this->tileCollisionIndex[index]; }

	inline float GetOutLookDistance() { return this->outLookDistance; }

	inline bool GetIsJump() { return this->isJump; }
	inline void SetIsJump(bool isJump) { this->isJump = isJump; }

	inline void SetIsLeftCollison(bool isLeftCollsion) { this->isLeftCollsion = isLeftCollsion; }
	inline void SetIsRightCollison(bool isRightCollsion) { this->isRightCollsion = isRightCollsion; }
	inline void SetIsPixleCollison(bool isPixleCollsion) { this->isPixleCollsion = isPixleCollsion; }

	inline bool GetIsPixelCollision() { return this->isPixleCollsion; }

	inline int GetDamege() { return this->damege; }

};

