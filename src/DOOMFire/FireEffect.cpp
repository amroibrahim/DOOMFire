#include "FireEffect.h"
#include <iostream>

FireEffect::FireEffect()
{
    int bpp;
    uint32_t Rmask;
    uint32_t Gmask;
    uint32_t Bmask;
    uint32_t Amask;

    //Initialize SDL
    m_iScreenWidth = iWidth;
    m_iScreenHeight = iHeight;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL failed to initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    m_pWindow = SDL_CreateWindow("DOOM Fire Effect", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_iScreenWidth, m_iScreenHeight, SDL_WINDOW_SHOWN);

    if (m_pWindow)
    {
       m_pWindowSurface = SDL_GetWindowSurface(m_pWindow);
    }

    // Create 8-bit screen buffer
    m_pScreenBuffer = SDL_CreateRGBSurface(0, m_iScreenWidth, m_iScreenHeight, 8, 0, 0, 0, 0);
    SDL_FillRect(m_pScreenBuffer, NULL, 0);

    InitColorPalette();

    SDL_SetPaletteColors(m_pScreenBuffer->format->palette, m_pPalette, 0, iColorCount);

    InitScreenBuffer();
}

void FireEffect::InitScreenBuffer()
{
    uint8_t *pPixels = (uint8_t *)m_pScreenBuffer->pixels;

    for (int x = 0; x < m_iScreenWidth; ++x)
    {
        pPixels[m_iScreenWidth * (m_iScreenHeight - 1) + x] = iColorCount - 1;
    }
}

void FireEffect::InitColorPalette()
{
    int Index = 0;
    m_pPalette = new SDL_Color[iColorCount];

    m_pPalette[Index++] = { 0x00, 0x00, 0x00 };
    m_pPalette[Index++] = { 0x00, 0x00, 0x00 };
    m_pPalette[Index++] = { 0x07, 0x07, 0x07 };
    m_pPalette[Index++] = { 0x1F, 0x07, 0x07 };
    m_pPalette[Index++] = { 0x2F, 0x0F, 0x07 };
    m_pPalette[Index++] = { 0x47, 0x0F, 0x07 };
    m_pPalette[Index++] = { 0x57, 0x17, 0x07 };
    m_pPalette[Index++] = { 0x67, 0x1F, 0x07 };
    m_pPalette[Index++] = { 0x77, 0x1F, 0x07 };
    m_pPalette[Index++] = { 0x8F, 0x27, 0x07 };
    m_pPalette[Index++] = { 0x9F, 0x2F, 0x07 };
    m_pPalette[Index++] = { 0xAF, 0x3F, 0x07 };
    m_pPalette[Index++] = { 0xBF, 0x47, 0x07 };
    m_pPalette[Index++] = { 0xC7, 0x47, 0x07 };
    m_pPalette[Index++] = { 0xDF, 0x4F, 0x07 };
    m_pPalette[Index++] = { 0xDF, 0x57, 0x07 };
    m_pPalette[Index++] = { 0xDF, 0x57, 0x07 };
    m_pPalette[Index++] = { 0xD7, 0x5F, 0x07 };
    m_pPalette[Index++] = { 0xD7, 0x5F, 0x07 };
    m_pPalette[Index++] = { 0xD7, 0x67, 0x0F };
    m_pPalette[Index++] = { 0xCF, 0x6F, 0x0F };
    m_pPalette[Index++] = { 0xCF, 0x77, 0x0F };
    m_pPalette[Index++] = { 0xCF, 0x7F, 0x0F };
    m_pPalette[Index++] = { 0xCF, 0x87, 0x17 };
    m_pPalette[Index++] = { 0xC7, 0x87, 0x17 };
    m_pPalette[Index++] = { 0xC7, 0x8F, 0x17 };
    m_pPalette[Index++] = { 0xC7, 0x97, 0x1F };
    m_pPalette[Index++] = { 0xBF, 0x9F, 0x1F };
    m_pPalette[Index++] = { 0xBF, 0x9F, 0x1F };
    m_pPalette[Index++] = { 0xBF, 0xA7, 0x27 };
    m_pPalette[Index++] = { 0xBF, 0xA7, 0x27 };
    m_pPalette[Index++] = { 0xBF, 0xAF, 0x2F };
    m_pPalette[Index++] = { 0xB7, 0xAF, 0x2F };
    m_pPalette[Index++] = { 0xB7, 0xB7, 0x2F };
    m_pPalette[Index++] = { 0xB7, 0xB7, 0x37 };
    m_pPalette[Index++] = { 0xCF, 0xCF, 0x6F };
    m_pPalette[Index++] = { 0xDF, 0xDF, 0x9F };
    m_pPalette[Index++] = { 0xEF, 0xEF, 0xC7 };
    m_pPalette[Index++] = { 0xFF, 0xFF, 0xFF };
}

void FireEffect::Clean()
{
    SDL_FreeSurface(m_pScreenBuffer);
    m_pScreenBuffer = nullptr;

    SDL_FreeSurface(m_pWindowSurface);
    m_pWindowSurface = nullptr;

    SDL_DestroyWindow(m_pWindow);
    m_pWindow = nullptr;

    SDL_Quit();
}

FireEffect::~FireEffect()
{
}

void FireEffect::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Quit();
            break;

        default:
            break;
        }
    }
}

void FireEffect::Update()
{
    int RandomeNumber = 0;
    
    uint8_t *pPixels = (uint8_t *)m_pScreenBuffer->pixels;
    for (int y = 1; y < m_iScreenHeight; ++y)
    {
        for (int x = 0; x < m_iScreenWidth; ++x)
        {
            if (0 < pPixels[m_iScreenWidth * y + x] && pPixels[m_iScreenWidth * y + x] < iColorCount)
            {
                RandomeNumber = rand() % 3;
                pPixels[m_iScreenWidth * (y-1) + x] = pPixels[m_iScreenWidth * y + x] - (RandomeNumber & 1);
            }
        }
    }
}

bool FireEffect::IsOver()
{
    return m_bIsOver;
}

void FireEffect::Delay()
{
    SDL_Delay(GetTimePerFrame());
}

void FireEffect::Render()
{
    SDL_BlitSurface(m_pScreenBuffer, nullptr, m_pWindowSurface, nullptr);
    SDL_UpdateWindowSurface(m_pWindow);
}

void  FireEffect::Quit()
{
    m_bIsOver = true;
}

int  FireEffect::GetTimePerFrame()
{
    return iTimePerFrame;
}
