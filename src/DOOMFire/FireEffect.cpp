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
    m_iBufferWidth = iWidth;
    m_iBufferHight = iHeight;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL failed to initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    m_pWindow = SDL_CreateWindow("DOOM Fire Effect", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_iBufferWidth, m_iBufferHight, SDL_WINDOW_SHOWN);

    if (m_pWindow)
    {
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    }

    uint32_t PixelFormat = SDL_GetWindowPixelFormat(m_pWindow);

    // Create 8-bit screen buffer
    m_pScreenBuffer = SDL_CreateRGBSurface(0, m_iBufferWidth, m_iBufferHight, 8, 0, 0, 0, 0);
    SDL_FillRect(m_pScreenBuffer, NULL, 0);

    SDL_PixelFormatEnumToMasks(PixelFormat, &bpp, &Rmask, &Gmask, &Bmask, &Amask);
    m_pRGBBuffer = SDL_CreateRGBSurface(0, m_iBufferWidth, m_iBufferHight, 32, Rmask, Gmask, Bmask, Amask);
    SDL_FillRect(m_pRGBBuffer, NULL, 0);

    m_pTexture = SDL_CreateTexture (m_pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_iBufferWidth, m_iBufferHight);

    InitColorLookup();

    m_pFrameBuffer = new uint8_t* [m_iBufferHight];
    for (int y = 0; y < m_iBufferHight; y++)
    {
        m_pFrameBuffer[y] = new uint8_t[m_iBufferWidth];
    }

    for (int x = 0; x < m_iBufferWidth; x++)
    {
        for (int y = 0; y < m_iBufferHight; y++)
        {
            m_pFrameBuffer[y][x] = 0;
        }
    }

    for (int i = 0; i < m_iBufferWidth; ++i)
    {
        m_pFrameBuffer[m_iBufferHight - 1][i] = iColorCount - 1;
    }
}

void FireEffect::InitColorLookup()
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
    SDL_FreeSurface(m_pRGBBuffer);

    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

FireEffect::~FireEffect()
{
    m_pScreenBuffer = nullptr;
    m_pRGBBuffer = nullptr;
    m_pRenderer = nullptr;
    m_pWindow = nullptr;
    
    
    
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

void FireEffect::Render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0xff);
    SDL_RenderClear(m_pRenderer);

    Render(m_pRenderer);

    SDL_RenderPresent(m_pRenderer);
}

void FireEffect::Update()
{
    int RandomeNumber = 0;

    for (int y = 1; y < m_iBufferHight; ++y)
    {
        for (int x = 0; x < m_iBufferWidth; ++x)
        {
            if (0 < m_pFrameBuffer[y][x] && m_pFrameBuffer[y][x] <= iColorCount)
            {
                RandomeNumber = rand() % 3;
                m_pFrameBuffer[y - 1][x] = m_pFrameBuffer[y][x] - (RandomeNumber & 1);
                //if ( -1 < (x - RandomeNumber) && (x - RandomeNumber) < m_iBufferWidth)
                //    m_FrameBuffer[y - 1][x - RandomeNumber] = m_FrameBuffer[y][x] - (RandomeNumber & 1);
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

void FireEffect::Render(SDL_Renderer* pRenderer)
{
    int Pitch;
    uint8_t *Pixels;
    uint32_t PixelPosition;
    SDL_LockTexture(m_pTexture, NULL, (void **)&Pixels, &Pitch);
    
    for (int y = 0; y < m_iBufferHight; ++y)
    {
        for (int x = 0; x < m_iBufferWidth; ++x)
        {
            PixelPosition = (y * (Pitch / sizeof(uint32_t)) + x) * sizeof(uint32_t);

            Pixels[PixelPosition++] = m_pPalette[m_pFrameBuffer[y][x]].b;
            Pixels[PixelPosition++] = m_pPalette[m_pFrameBuffer[y][x]].g; 
            Pixels[PixelPosition++] = m_pPalette[m_pFrameBuffer[y][x]].r; 
            Pixels[PixelPosition] = 0xff;
        }
    }

    SDL_UnlockTexture(m_pTexture);
    SDL_RenderCopy(pRenderer, m_pTexture, nullptr, nullptr);
}

void  FireEffect::Quit()
{
    m_bIsOver = true;
}

int  FireEffect::GetTimePerFrame()
{
    return iTimePerFrame;
}
