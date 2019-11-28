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
    virtual void InitColorLookup();

    SDL_Color* m_pPalette;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture;

    SDL_Surface *m_pScreenBuffer;
    SDL_Surface *m_pRGBBuffer;

    int m_iScreenWidth;
    int m_iScreenHeight;
    int m_iPaletteColorCount;
    bool m_bIsOver;
};
