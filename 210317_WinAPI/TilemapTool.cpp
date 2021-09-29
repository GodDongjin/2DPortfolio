#include "TilemapTool.h"
#include "config.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"
#include "Camera.h"
#include "IntroScene.h"

TILE_INFO TilemapTool::tileInfo[TILE_Y][TILE_X];
COLLISION_TILE_INFO TilemapTool::collisionTileInfo[TILE_Y][TILE_X];
int TilemapTool::buttIndex = -1;

HRESULT TilemapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);
    backGround = ImageManager::GetSingleton()->FindImage("배경");
 
    stage1Tile = ImageManager::GetSingleton()->FindImage("STAGE1_TILE");
    stage1CollisionTile = ImageManager::GetSingleton()->FindImage("STAGE1_PIXEL_TILE");

    stage2Tile = ImageManager::GetSingleton()->FindImage("STAGE2_TILE");
    stage2CollisionTile = ImageManager::GetSingleton()->FindImage("STAGE2_PIXEL_TILE");


    // 메인 공간 렉트 설정
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            tileInfo[i][j].frameX = 0;
            tileInfo[i][j].frameY = 3;

            tileInfo[i][j].pos.x = j * TILESIZE;
            tileInfo[i][j].pos.y = i * TILESIZE;
            tileInfo[i][j].tileType = TILETPYE::Wall;
            tileInfo[i][j].rcTile = GetRect(tileInfo[i][j].pos.x, tileInfo[i][j].pos.y, TILESIZE, TILESIZE);
        }
    }
     
    // 샘플 공간 렉트 설정  충돌 샘플 공간 렉트 설정
 

    tileSize = TILESIZE;
    imgSize = 1;

    for (int i = 0; i < 6; i++)
    {
        btnStage[i] = new Button();
        btnStage[i]->Init("스테이지버튼", ((TILEMAPTOOLSIZE_X - (12 * SAMPLE_TILESIZE) + 56) + (56 * i)),
            (SAMPLE_TILE_Y * SAMPLE_TILESIZE) + SAMPLE_TILESIZE + 65,i + 1);
        btnStage[i]->SetFunc(Load, pixelLoad, i, i );
    }
    
    btnSave = new Button();
    btnSave->Init("세이브버튼", TILEMAPTOOLSIZE_X - 150, (SAMPLE_TILE_Y * SAMPLE_TILESIZE) + SAMPLE_TILESIZE, 7);
    btnSave->SetFunc(Save, pixelSave);
    
    randerRc = GetRect(0, 0, 780, 882);
    
    //카메라 중심 좌표
    targetPos.x = 500;
    targetPos.y = 0;
    
    //배경맵 좌표
    mapPos.x = 0;
    mapPos.y = 0;
    
    //월드전체 크기 
    Camera::GetSingleton()->SetManMinPos(0,0,backGround->GetWidth(), backGround->GetHeight());

    SceneManager::GetSingleton()->AddScene("인트로", new IntroScene());

    return S_OK;
}

void TilemapTool::Release()
{
    for (int i = 0; i < 6; i++)
    {
        SAFE_RELEASE(btnStage[i]);
    }
   // SAFE_RELEASE(btnLoad);
}

void TilemapTool::Update()
{   if(buttIndex == 0)
        Stage1Init();
    if(buttIndex == 1)
        Stage2Init();
    if (buttIndex == 2)
        Stage2Init();

    for (int i = 0; i < 6; i++)
    {
        if (btnStage[i])    btnStage[i]->Update(); 
    }
    if (btnSave)    btnSave->Update();
   

    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN)) { targetPos.y += 5; }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP)) { targetPos.y -= 5; }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)) { targetPos.x -= 5; }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) { targetPos.x += 5; }
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            tileInfo[i][j].rcTile.left = (tileSize * j) - Camera::GetSingleton()->GetPos().x;
            tileInfo[i][j].rcTile.top = (tileSize * i) - Camera::GetSingleton()->GetPos().y;
            tileInfo[i][j].rcTile.right =
                (tileInfo[i][j].rcTile.left + tileSize);
            tileInfo[i][j].rcTile.bottom =
                (tileInfo[i][j].rcTile.top + tileSize);
            
            collisionTileInfo[i][j].rcTile.left = (tileSize * j) - Camera::GetSingleton()->GetPos().x;
            collisionTileInfo[i][j].rcTile.top = (tileSize * i) - Camera::GetSingleton()->GetPos().y;
            collisionTileInfo[i][j].rcTile.right =
                (collisionTileInfo[i][j].rcTile.left + tileSize);
            collisionTileInfo[i][j].rcTile.bottom =
                (collisionTileInfo[i][j].rcTile.top + tileSize);
        }
    }
    
    // 메인 영역 계산
    rcMain.left = 0;
    rcMain.top = 0;
    rcMain.right = randerRc.right;
    rcMain.bottom = randerRc.bottom;

  if(buttIndex == 0)
  {
      Stage1Update();
  }
  if (buttIndex == 1)
  {
      Stage2Update();
  }
  if (buttIndex == 2)
  {
      Stage2Update();
  }

    // 오브젝트 영역 계산
    

    if (PtInRect(&rcMain, g_ptMouse))
    {
        // 마우스 왼쪽 버튼 클릭시 좌표 사용
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)
            || KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            for (int i = 0; i < TILE_Y; i++)
            {
                for (int j = 0; j < TILE_X; j++)
                {
                    if (tileInfo[i][j].rcTile.right > randerRc.left && tileInfo[i][j].rcTile.left < randerRc.right &&
                        tileInfo[i][j].rcTile.bottom > randerRc.top && tileInfo[i][j].rcTile.top < randerRc.bottom)
                    {
                        if (PtInRect(&(tileInfo[i][j].rcTile), g_ptMouse))
                        {
                            tileInfo[i][j].frameX = selectedTile.x;
                            tileInfo[i][j].frameY = selectedTile.y;

                            //(((((int)pos.y + TILESIZE / 2) / TILESIZE) + i) * TILE_X) + ((int)pos.x / (TILESIZE)+j)
                            if(buttIndex == 0)
                                tileInfo[i][j].tileType = stage1SampleTileInfo[selectedTile.y][selectedTile.x].tileType;
                            if(buttIndex == 1)
                                tileInfo[i][j].tileType = stage2SampleTileInfo[selectedTile.y][selectedTile.x].tileType;
                            if (buttIndex == 2)
                                tileInfo[i][j].tileType = stage2SampleTileInfo[selectedTile.y][selectedTile.x].tileType;

                            collisionTileInfo[i][j].frameX = selectedTile.x;
                            collisionTileInfo[i][j].frameY = selectedTile.y;
                            break;
                        }
                    }
                }
            }
        }
    }

    else if (PtInRect(&rcSample, g_ptMouse))
    {
        // 마우스 왼쪽 버튼 클릭시 좌표 사용
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            // 2) 마우스 좌표로 인덱스 계산
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            selectedTile.x = posX / 32;
            selectedTile.y = posY / 32;
        }
        
    }
    
    if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
    {
        for (int i = 0; i < TILE_Y; i++)
        {
            for (int j = 0; j < TILE_X; j++)
            {
                if (buttIndex == 0)
                {
                    tileInfo[i][j].frameX = 0;
                    tileInfo[i][j].frameY = 3;

                    collisionTileInfo[i][j].frameX = 0;
                    collisionTileInfo[i][j].frameY = 3;
                    tileInfo[i][j].tileType = TILETPYE::Wall;
                }

                if (buttIndex == 1)
                {
                    tileInfo[i][j].frameX = 1;
                    tileInfo[i][j].frameY = 0;

                    collisionTileInfo[i][j].frameX = 1;
                    collisionTileInfo[i][j].frameY = 0;
                    tileInfo[i][j].tileType = TILETPYE::Wall;
                }
                if (buttIndex == 2)
                {
                    tileInfo[i][j].frameX = 1;
                    tileInfo[i][j].frameY = 0;

                    collisionTileInfo[i][j].frameX = 1;
                    collisionTileInfo[i][j].frameY = 0;
                    tileInfo[i][j].tileType = TILETPYE::Wall;
                }
            }
        }
    }

    if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
    {
        for (int i = 0; i < TILE_Y; i++)
        {
            for (int j = 0; j < TILE_X; j++)
            {
                tileInfo[i][j].frameX = 0;
                tileInfo[i][j].frameY = 0;

                collisionTileInfo[i][j].frameX = 0;
                collisionTileInfo[i][j].frameY = 3;
                tileInfo[i][j].tileType = TILETPYE::None;
            }
        }
    }

    worldPos.x = targetPos.x;
    worldPos.y = targetPos.y;
    Camera::GetSingleton()->AddTargetPos(worldPos);
    CameraObject::UpdatePosition();

    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
    {
        SceneManager::GetSingleton()->ChangeScene("인트로");
    }
}

void TilemapTool::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0,
        TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    int screenPosX = mapPos.x - Camera::GetSingleton()->GetPos().x;
    int screenPosY = mapPos.y - Camera::GetSingleton()->GetPos().y;

    backGround->Render(hdc, screenPosX, screenPosY, false);
    // 샘플타일 전체
    
    if (buttIndex == 0)
    {
        stage1Tile->Render(hdc, TILEMAPTOOLSIZE_X - stage1Tile->GetWidth(), 0);
    }
    if (buttIndex == 1)
    {
        stage2Tile->Render(hdc, TILEMAPTOOLSIZE_X - stage2Tile->GetWidth(), 0);
    }
    if (buttIndex == 2)
    {
        stage2Tile->Render(hdc, TILEMAPTOOLSIZE_X - stage2Tile->GetWidth(), 0);
    }
    //objectSampleTile->Render(hdc, TILEMAPTOOLSIZE_X - objectSampleTile->GetWidth(), 500);
    

    // UI Button
    for (int i = 0; i < 6; i++)
    {
        if (btnStage[i])    btnStage[i]->Render(hdc);
    }
    if (btnSave)    btnSave->Render(hdc);

  

    // 메인영역 전체
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            //collisionTileInfo[i].hdc = hdc;
            if (tileInfo[i][j].rcTile.right > randerRc.left && tileInfo[i][j].rcTile.left < randerRc.right &&
                tileInfo[i][j].rcTile.bottom > randerRc.top && tileInfo[i][j].rcTile.top < randerRc.bottom)
            {
                if (buttIndex == 0)
                {
                    stage1Tile->FrameRender(hdc,
                        tileInfo[i][j].rcTile.left, tileInfo[i][j].rcTile.top,
                        tileInfo[i][j].frameX,
                        tileInfo[i][j].frameY, false, 16);

                    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_F1))
                    {

                        stage1CollisionTile->FrameRender(hdc,
                            collisionTileInfo[i][j].rcTile.left,
                            collisionTileInfo[i][j].rcTile.top, collisionTileInfo[i][j].frameX,
                            collisionTileInfo[i][j].frameY, false, 16);
                    }
                }

                if (buttIndex == 1)
                {
                    stage2Tile->FrameRender(hdc,
                        tileInfo[i][j].rcTile.left, tileInfo[i][j].rcTile.top,
                        tileInfo[i][j].frameX,
                        tileInfo[i][j].frameY, false, 16);

                    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_F1))
                    {

                        stage2CollisionTile->FrameRender(hdc,
                            collisionTileInfo[i][j].rcTile.left,
                            collisionTileInfo[i][j].rcTile.top, collisionTileInfo[i][j].frameX,
                            collisionTileInfo[i][j].frameY, false, 16);
                    }
                }

                if (buttIndex == 2)
                {
                    stage2Tile->FrameRender(hdc,
                        tileInfo[i][j].rcTile.left, tileInfo[i][j].rcTile.top,
                        tileInfo[i][j].frameX,
                        tileInfo[i][j].frameY, false, 16);

                    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_F1))
                    {

                        stage2CollisionTile->FrameRender(hdc,
                            collisionTileInfo[i][j].rcTile.left,
                            collisionTileInfo[i][j].rcTile.top, collisionTileInfo[i][j].frameX,
                            collisionTileInfo[i][j].frameY, false, 16);
                    }
                }
            }
        }
    }
    
    // 선택된 타일
    if (buttIndex == 0)
    {
        stage1Tile->FrameRender(hdc,
            TILEMAPTOOLSIZE_X - stage1Tile->GetWidth(),
            stage1Tile->GetHeight() + 64,
            selectedTile.x, selectedTile.y, false, 3);

        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            stage1CollisionTile->FrameRender(hdc,
                TILEMAPTOOLSIZE_X - stage1Tile->GetWidth(),
                stage1Tile->GetHeight() + 64,
                selectedTile.x, selectedTile.y, false, 3);
        }
    }
   
    if (buttIndex == 1)
    {
        stage2Tile->FrameRender(hdc,
            TILEMAPTOOLSIZE_X - stage2Tile->GetWidth(),
            stage2Tile->GetHeight() + 64,
            selectedTile.x, selectedTile.y, false, 3);

        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            stage1CollisionTile->FrameRender(hdc,
                TILEMAPTOOLSIZE_X - stage2Tile->GetWidth(),
                stage2Tile->GetHeight() + 64,
                selectedTile.x, selectedTile.y, false, 3);
        }
    }

    if (buttIndex == 2)
    {
        stage2Tile->FrameRender(hdc,
            TILEMAPTOOLSIZE_X - stage2Tile->GetWidth(),
            stage2Tile->GetHeight() + 64,
            selectedTile.x, selectedTile.y, false, 3);

        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            stage1CollisionTile->FrameRender(hdc,
                TILEMAPTOOLSIZE_X - stage2Tile->GetWidth(),
                stage2Tile->GetHeight() + 64,
                selectedTile.x, selectedTile.y, false, 3);
        }
    }
  

    
}

void TilemapTool::Stage1Init()
{
    stage1_Sample_Tile_x = 6;
    stage1_Sample_Tile_y = 15;

    for (int i = 0; i < stage1_Sample_Tile_y; i++)
    {
        for (int j = 0; j < stage1_Sample_Tile_x; j++)
        {
            stage1SampleTileInfo[i][j].frameX = j;
            stage1SampleTileInfo[i][j].frameY = i;

            stage1SampleTileInfo[i][j].pos.x = TILEMAPTOOLSIZE_X - stage1Tile->GetWidth() + (SAMPLE_TILESIZE * j);
            stage1SampleTileInfo[i][j].pos.y = SAMPLE_TILESIZE * i;

            stage1SampleTileInfo[i][j].rcTile =
                GetRect(stage1SampleTileInfo[i][j].pos.x, stage1SampleTileInfo[i][j].pos.y, SAMPLE_TILESIZE, SAMPLE_TILESIZE);


            stage1CollisionSampleTileInfo[i][j].frameX = j;
            stage1CollisionSampleTileInfo[i][j].frameY = i;

            stage1CollisionSampleTileInfo[i][j].pos.x = TILEMAPTOOLSIZE_X - stage1Tile->GetWidth() + (SAMPLE_TILESIZE * j);
            stage1CollisionSampleTileInfo[i][j].pos.y = SAMPLE_TILESIZE * i;
            stage1CollisionSampleTileInfo[i][j].rcTile =
                GetRect(stage1CollisionSampleTileInfo[i][j].pos.x, stage1CollisionSampleTileInfo[i][j].pos.y,
                    SAMPLE_TILESIZE, SAMPLE_TILESIZE);
        }
    }
    stage1SampleTileInfo[2][0].tileType = TILETPYE::Wall;
    stage1SampleTileInfo[2][1].tileType = TILETPYE::Wall;
    stage1SampleTileInfo[3][0].tileType = TILETPYE::Wall;
    stage1SampleTileInfo[3][1].tileType = TILETPYE::Wall;
    stage1SampleTileInfo[0][1].tileType = TILETPYE::Wall;
    stage1SampleTileInfo[14][5].tileType = TILETPYE::PlayerSpwon;
    stage1SampleTileInfo[6][4].tileType = TILETPYE::Door;
    stage1SampleTileInfo[5][4].tileType = TILETPYE::Door;
}

void TilemapTool::Stage2Init()
{
    stage2_Sample_Tile_x = 6;
    stage2_Sample_Tile_y = 11;

    for (int i = 0; i < stage2_Sample_Tile_y; i++)
    {
        for (int j = 0; j < stage2_Sample_Tile_x; j++)
        {
            stage2SampleTileInfo[i][j].frameX = j;
            stage2SampleTileInfo[i][j].frameY = i;

            stage2SampleTileInfo[i][j].pos.x = TILEMAPTOOLSIZE_X - stage2Tile->GetWidth() + (SAMPLE_TILESIZE * j);
            stage2SampleTileInfo[i][j].pos.y = SAMPLE_TILESIZE * i;

            stage2SampleTileInfo[i][j].rcTile =
                GetRect(stage2SampleTileInfo[i][j].pos.x, stage2SampleTileInfo[i][j].pos.y, SAMPLE_TILESIZE, SAMPLE_TILESIZE);


            stage2CollisionSampleTileInfo[i][j].frameX = j;
            stage2CollisionSampleTileInfo[i][j].frameY = i;

            stage2CollisionSampleTileInfo[i][j].pos.x = TILEMAPTOOLSIZE_X - stage2Tile->GetWidth() + (SAMPLE_TILESIZE * j);
            stage2CollisionSampleTileInfo[i][j].pos.y = SAMPLE_TILESIZE * i;
            stage2CollisionSampleTileInfo[i][j].rcTile =
                GetRect(stage2CollisionSampleTileInfo[i][j].pos.x, stage2CollisionSampleTileInfo[i][j].pos.y,
                    SAMPLE_TILESIZE, SAMPLE_TILESIZE);
        }
    }

    stage2SampleTileInfo[0][1].tileType = TILETPYE::Wall;
    stage2SampleTileInfo[0][2].tileType = TILETPYE::Wall;
    stage2SampleTileInfo[0][3].tileType = TILETPYE::Wall;
    stage2SampleTileInfo[0][4].tileType = TILETPYE::Wall;
    stage2SampleTileInfo[0][5].tileType = TILETPYE::Wall;
    
    stage2SampleTileInfo[9][0].tileType = TILETPYE::Door;
    stage2SampleTileInfo[10][0].tileType = TILETPYE::Door;
    
    stage2SampleTileInfo[10][5].tileType = TILETPYE::PlayerSpwon;
}

void TilemapTool::Stage1Update()
{
    // 샘플 영역 계산
    rcSample.left = TILEMAPTOOLSIZE_X - stage1Tile->GetWidth();
    rcSample.top = 0;
    rcSample.right = TILEMAPTOOLSIZE_X;
    rcSample.bottom = stage1Tile->GetHeight();

}

void TilemapTool::Stage2Update()
{
    rcSample.left = TILEMAPTOOLSIZE_X - stage2Tile->GetWidth();
    rcSample.top = 0;
    rcSample.right = TILEMAPTOOLSIZE_X;
    rcSample.bottom = stage2Tile->GetHeight();
}

void TilemapTool::Save(int stageNum)
{
    stageNum = buttIndex;

    string fileName = "Save/saveMapData";  // 1.map";
    fileName += to_string(stageNum) + ".map";

    DWORD writtenBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0,
        0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
        &writtenBytes, NULL);

    CloseHandle(hFile);
}

void TilemapTool::Load(int stageNum)
{
    buttIndex = stageNum;

    string fileName = "Save/saveMapData";  // 1.map";
    fileName += to_string(stageNum) + ".map";

    DWORD readBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0,
        0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
        &readBytes, NULL))
    {

    }
   

    CloseHandle(hFile);
}

void TilemapTool::pixelSave(int stageNum)
{
    stageNum = buttIndex;

    string fileName = "Save/savePixelMapData";  // 1.map";
    fileName += to_string(stageNum) + ".map";

    DWORD writtenBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0,
        0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    WriteFile(hFile, collisionTileInfo, sizeof(COLLISION_TILE_INFO) * TILE_X * TILE_Y,
        &writtenBytes, NULL);

    CloseHandle(hFile);
}

void TilemapTool::pixelLoad(int stageNum)
{
    buttIndex = stageNum;

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
