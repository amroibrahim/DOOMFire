#pragma once

#include <array>
#include <SDL.h>

#define iWidth 320 * 2
#define iHeight 200 * 2
#define iTimePerFrame 1000/60 

class FireEffect
{
public:
    FireEffect();
    virtual ~FireEffect();

    void ProcessInput();
    void Render();
    void Update();
    void Delay();
    void Quit();
    void Clean();

    bool IsOver();
    int GetTimePerFrame();

protected:
    virtual void Render(SDL_Renderer* pRenderer);
    virtual void InitColorVec();

    std::array<std::array<int, iWidth>, iHeight> m_FrameBuffer;
    std::array<SDL_Color, 38> m_ColorLookup;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    int m_iBufferWidth;
    int m_iBufferHight;
    bool m_bIsOver;
};
