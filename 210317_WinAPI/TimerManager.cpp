#include "TimerManager.h"
#include "Timer.h"

HRESULT TimerManager::Init()
{
    timer = new Timer();
    timer->Init();

    return S_OK;
}

void TimerManager::Release()
{
    SAFE_DELETE(timer);
}

void TimerManager::Update()
{
    if (timer)
    {
        timer->Tick();
    }
}

void TimerManager::Render(HDC hdc)
{
    if (timer)
    {
        wsprintf(szText, "FPS : %d", timer->GetFPS());
        TextOut(hdc, WINSIZE_X - 150, 20, szText, strlen(szText));
        wsprintf(szText, " %d", TimerManager::GetSingleton()->GetCurrTime());
        TextOut(hdc, WINSIZE_X - 150, 40, szText, strlen(szText));
    }
}

float TimerManager::GetElapsedTime()
{
    //return 0.033f;
    return timer->GetElapsedTime();
}

float TimerManager::GetCurrTime()
{
    return timer->GetCurrTime();
}

int TimerManager::GetClockTime()
{
    return timer->GetClockTime();
}
