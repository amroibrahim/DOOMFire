#pragma once

#include <vector>
#include <SDL.h>

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

    std::vector<std::vector<int>> m_FrameBuffer;
    std::vector<SDL_Color> m_ColorVec;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    int m_iBufferWidth;
    int m_iBufferHight;
    bool m_bIsOver;
};
