#pragma once
#include "CameraObject.h"

class Button;
class Image;

class TilemapTool : public CameraObject
{
private:
	static TILE_INFO tileInfo[TILE_Y][TILE_X];
	static COLLISION_TILE_INFO collisionTileInfo[TILE_Y][TILE_X];
	static int buttIndex;

	Image* backGround;
	FPOINT mapPos;

	// 샘플 타일 이미지
	Image* stage1Tile;
	Image* stage1CollisionTile;

	Image* stage2Tile;
	Image* stage2CollisionTile;

	Image* notCollsionSampleTile;
	Image* objectSampleTile;


	//NOT_OBJECT_TILE_INFO notCollsionSampleTileInfo[NOTCOLLSION_TILE_X * NOTCOLLSION_TILE_Y];
	TILE_INFO stage1SampleTileInfo[15][6];
	COLLISION_TILE_INFO stage1CollisionSampleTileInfo[15][6];

	TILE_INFO stage2SampleTileInfo[11][6];
	COLLISION_TILE_INFO stage2CollisionSampleTileInfo[11][6];

	OBJECT_TILE_INFO objectTileInfo[SAMPLE_TILE_Y][SAMPLE_TILE_X];

	RECT rcSample;
	RECT collisionRcSample;
	RECT rcTile;
	// 메인타일의 정보
	
	RECT rcMain;
	RECT collisionRcMain;
	RECT randerRc;

	POINT ptStartSelectedFrame;
	POINT ptEndSelectedFrame;
	POINT mainPos;
	POINT samplPos;

	//TILETPYE slectedTile;
	POINT selectedTile;

	FPOINT targetPos;
	// UI button
	Button* btnStage[6];
	Button* btnSave;

	int tileSize;
	int imgSize;

	int stage1_Sample_Tile_x;
	int stage1_Sample_Tile_y;
	int stage2_Sample_Tile_x;
	int stage2_Sample_Tile_y;


public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Stage1Init();
	void Stage2Init();
	//void Stage3Init();

	void Stage1Update();
	void Stage2Update();
	//void Stage3Update();

	static void Save(int stageNum);
	static void Load(int stageNum);
	static void pixelSave(int stageNum);
	static void pixelLoad(int stageNum);
	virtual ~TilemapTool() {};
};

