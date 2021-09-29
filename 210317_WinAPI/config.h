// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <map>
#include <vector>
#include <list>
#include <time.h>
#include <algorithm>
#include <functional>
#include <random>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

#define WINSIZE_X	1400
#define WINSIZE_Y	900
#define TILEMAPTOOLSIZE_X	1400
#define TILEMAPTOOLSIZE_Y	900
#define ASTARSIZE_X	1620
#define ASTARSIZE_Y	900


#define PI			3.141592f
#define DegToRad(x)	((x) * PI / 180.0f)
#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); delete p; p = nullptr; } }

#define SAMPLE_TILE_X	6
#define SAMPLE_TILE_Y	15

#define OBJECT_TILE_X 2
#define OBJECT_TILE_Y 1

#define NOTCOLLSION_TILE_X 18
#define NOTCOLLSION_TILE_Y 2

#define SAMPLE_TILESIZE		32
#define TILESIZE			48
#define INGAMETILESIZE		48 

// 메인 그리기 공간 정보
#define	TILE_X			50
#define	TILE_Y			35

#define CAMERASIZE_X	0
#define CAMERASIZE_Y	0

#define WORLDSIZEX 3000
#define WORLDSIZEY 2000

enum TILETPYE { None, Wall, Door, PlayerSpwon};

enum class EnemyState
{
	IDLE,
	RUN,
	HIT,
	JUMP,
	JUMP_DOWN,
	LANDING
};

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

typedef struct tagTile
{
	FPOINT pos;
	RECT rcTile;
	int frameX;
	int frameY;
	TILETPYE tileType;
} TILE_INFO;

typedef struct collisionTile
{
	POINT pos;
	RECT rcTile;
	int frameX;
	int frameY;
} COLLISION_TILE_INFO;

typedef struct objectTile
{
	POINT pos;
	RECT rcTile;
	int frameX;
	int frameY;
} OBJECT_TILE_INFO;

typedef struct notCollsionTile
{
	POINT pos;
	RECT rcTile;
	int frameX;
	int frameY;
} NOT_OBJECT_TILE_INFO;


extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;