#pragma once

#include <array>
#include <SDL.h>

#define iWidth 320 * 2
#define iHeight 200 * 2
#define iColorCount 39
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
    virtual void InitColorLookup();

    uint8_t **m_pFrameBuffer;
    SDL_Color* m_pColorLookup;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture;

    int m_iBufferWidth;
    int m_iBufferHight;
    bool m_bIsOver;
};
