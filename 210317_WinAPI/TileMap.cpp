#include "TileMap.h"
#include "CommonFunction.h"
#include "Camera.h"
#include "Image.h"
#include "TilemapTool.h"
#include "CollisionManager.h"

HRESULT TileMap::Init(int num)
{
	this->stageNum = num;
	
	Load(this->stageNum);
	pixelLoad(this->stageNum);

	if (stageNum == 0)
	{
		tileImg = ImageManager::GetSingleton()->FindImage("INGAME_STAGE1_TILE");

		collisionTileImg = ImageManager::GetSingleton()->FindImage("INGAME_STAGE1_PIXEL_TILE");
	}

	if (stageNum == 1)
	{
		tileImg = ImageManager::GetSingleton()->FindImage("INGAME_STAGE2_TILE");

		collisionTileImg = ImageManager::GetSingleton()->FindImage("INGAME_STAGE2_PIXEL_TILE");
	}

	if (stageNum == 2)
	{
		tileImg = ImageManager::GetSingleton()->FindImage("INGAME_STAGE2_TILE");

		collisionTileImg = ImageManager::GetSingleton()->FindImage("INGAME_STAGE2_PIXEL_TILE");
	}

	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			tileInfo[i][j].pos.x = j * INGAMETILESIZE;
			tileInfo[i][j].pos.y = i * INGAMETILESIZE;
			tileInfo[i][j].rcTile = GetRect(tileInfo[i][j].pos.x, tileInfo[i][j].pos.y,
				INGAMETILESIZE, INGAMETILESIZE);
			
			
			
			collisionTileInfo[i][j].pos.x = j * INGAMETILESIZE;
			collisionTileInfo[i][j].pos.y = i * INGAMETILESIZE;
			collisionTileInfo[i][j].rcTile = 
				GetRect(collisionTileInfo[i][j].pos.x, collisionTileInfo[i][j].pos.y,
				INGAMETILESIZE, INGAMETILESIZE);

			//Camera::GetSingleton()->Init(tileInfo[0][0].pos.x - INGAMETILESIZE, tileInfo[0][0].pos.y,
			//	tileInfo[i][j].pos.x, tileInfo[i][j].pos.y);

			if (tileInfo[i][j].tileType == TILETPYE::PlayerSpwon)
			{
				playerPos.x = tileInfo[i][j].pos.x;
				playerPos.y = tileInfo[i][j].pos.y;

				tileInfo[i][j].frameX = 0;
				tileInfo[i][j].frameY = 0;
			}

			CollisionManager::GetSingleton()->AddTile(&tileInfo[i][j]);
			
		}
	}

	return S_OK;
}

void TileMap::Release()
{
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			CollisionManager::GetSingleton()->TileRelese(&tileInfo[i][j]);
		}
	}
}

void TileMap::Update()
{
	


	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			tileWorldPos[i][j].x = tileInfo[i][j].pos.x;
			tileWorldPos[i][j].y = tileInfo[i][j].pos.y;

			tileInfo[i][j].rcTile = GetRect(tileInfo[i][j].pos.x, tileInfo[i][j].pos.y, 
				INGAMETILESIZE, INGAMETILESIZE);
		}
		
		
	}

	CameraObject::UpdatePosition();
}

void TileMap::Render(HDC hdc)
{
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			//if (tileInfo[i].tileType == TILETPYE::PlayerSpwon)
		//{
		//	tileInfo[i].frameX = 0;
		//	tileInfo[i].frameY = 0;
		//}
		//Rectangle(hdc, tileInfo[i].rcTile.left, tileInfo[i].rcTile.top, tileInfo[i].rcTile.right, tileInfo[i].rcTile.bottom);
			tileImg->FrameRender(hdc,
				tileScreenPos[i][j].x, tileScreenPos[i][j].y,
				tileInfo[i][j].frameX,
				tileInfo[i][j].frameY, false);

			//wsprintf(szText, "x: %d", i);
			//TextOut(hdc, tileScreenPos[i][j].x + 5, tileScreenPos[i][j].y + 5, szText, strlen(szText));

			//collisionTileImg->FrameRender(hdc,
			//	tileWorldPos[i].x, tileWorldPos[i].y,
			//	collisionTileInfo[i].frameX,
			//	collisionTileInfo[i].frameY, false);
		}
	}
}


void TileMap::Load(int stageNum)
{
	string fileName = "Save/saveMapData";  // 1.map";
	fileName += to_string(stageNum) + ".map";

	DWORD readBytes;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0,
		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	/*void**/
	if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
		&readBytes, NULL))
	{
		for(int i = 0; i < TILE_Y; i++)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				if (tileInfo[i][j].tileType == TILETPYE::None)
				{
					vE_pos.push_back(tileInfo[i][j].pos);
				}
			}
		}
	}
	else
	{
		MessageBox(g_hWnd, "저장파일 로드 실패", "실패", MB_OK);
	}

	CloseHandle(hFile);
}

void TileMap::pixelLoad(int stageNum)
{
	string fileName = "Save/savePixelMapData";  // 1.map";
	fileName += to_string(stageNum) + ".map";

	DWORD readBytes;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0,
		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	/*void**/
	if (ReadFile(hFile, collisionTileInfo, sizeof(COLLISION_TILE_INFO) * TILE_X * TILE_Y,
		&readBytes, NULL))
	{

	}

	CloseHandle(hFile);
}

void TileMap::SetPixelMap(Image** pixelmap)
{
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			collisionTileImg->FrameRender((*pixelmap)->GetMemDC(),
				collisionTileInfo[i][j].pos.x, collisionTileInfo[i][j].pos.y,
				collisionTileInfo[i][j].frameX,
				collisionTileInfo[i][j].frameY, false);
		}
	
	}
}