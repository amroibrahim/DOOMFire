#include "FireEffect.h"
#include <iostream>


FireEffect::FireEffect()
{
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

    InitColorVec();

    for (int i = 0; i < m_iBufferWidth; ++i)
    {
        m_FrameBuffer[m_iBufferHight - 1][i] = m_ColorVec.size() - 1;
    }
}

void FireEffect::InitColorVec()
{
    m_ColorVec[0] = { 0x07, 0x07, 0x07 };
    m_ColorVec[1] = { 0x1F, 0x07, 0x07 };
    m_ColorVec[2] = { 0x2F, 0x0F, 0x07 };
    m_ColorVec[3] = { 0x47, 0x0F, 0x07 };
    m_ColorVec[4] = { 0x57, 0x17, 0x07 };
    m_ColorVec[5] = { 0x67, 0x1F, 0x07 };
    m_ColorVec[6] = { 0x77, 0x1F, 0x07 };
    m_ColorVec[7] = { 0x8F, 0x27, 0x07 };
    m_ColorVec[8] = { 0x9F, 0x2F, 0x07 };
    m_ColorVec[9] = { 0xAF, 0x3F, 0x07 };
    m_ColorVec[10] = { 0xBF, 0x47, 0x07 };
    m_ColorVec[11] = { 0xC7, 0x47, 0x07 };
    m_ColorVec[12] = { 0xDF, 0x4F, 0x07 };
    m_ColorVec[13] = { 0xDF, 0x57, 0x07 };
    m_ColorVec[14] = { 0xDF, 0x57, 0x07 };
    m_ColorVec[15] = { 0xD7, 0x5F, 0x07 };
    m_ColorVec[16] = { 0xD7, 0x5F, 0x07 };
    m_ColorVec[17] = { 0xD7, 0x67, 0x0F };
    m_ColorVec[18] = { 0xCF, 0x6F, 0x0F };
    m_ColorVec[19] = { 0xCF, 0x77, 0x0F };
    m_ColorVec[20] = { 0xCF, 0x7F, 0x0F };
    m_ColorVec[21] = { 0xCF, 0x87, 0x17 };
    m_ColorVec[22] = { 0xC7, 0x87, 0x17 };
    m_ColorVec[23] = { 0xC7, 0x8F, 0x17 };
    m_ColorVec[24] = { 0xC7, 0x97, 0x1F };
    m_ColorVec[25] = { 0xBF, 0x9F, 0x1F };
    m_ColorVec[26] = { 0xBF, 0x9F, 0x1F };
    m_ColorVec[27] = { 0xBF, 0xA7, 0x27 };
    m_ColorVec[28] = { 0xBF, 0xA7, 0x27 };
    m_ColorVec[29] = { 0xBF, 0xAF, 0x2F };
    m_ColorVec[30] = { 0xB7, 0xAF, 0x2F };
    m_ColorVec[31] = { 0xB7, 0xB7, 0x2F };
    m_ColorVec[32] = { 0xB7, 0xB7, 0x37 };
    m_ColorVec[33] = { 0xCF, 0xCF, 0x6F };
    m_ColorVec[34] = { 0xDF, 0xDF, 0x9F };
    m_ColorVec[35] = { 0xEF, 0xEF, 0xC7 };
    m_ColorVec[36] = { 0xFF, 0xFF, 0xFF };
}

void FireEffect::Clean()
{
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

FireEffect::~FireEffect()
{
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
    for (int x = 0; x < m_iBufferWidth; x++)
    {
        for (int y = 1; y < m_iBufferHight; y++)
        {
            int RandomeNumber = rand() % 3;

            if (0 < m_FrameBuffer[y][x] && m_FrameBuffer[y][x] < m_ColorVec.size())
            {
                m_FrameBuffer[y - 1][x] = m_FrameBuffer[y][x] - (RandomeNumber & 1);
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
    for (int y = 0; y < m_iBufferHight; ++y)
    {
        for (int x = 0; x < m_iBufferWidth; ++x)
        {
            if (m_FrameBuffer[y][x])
            {
                SDL_SetRenderDrawColor(pRenderer, m_ColorVec[m_FrameBuffer[y][x]].r, m_ColorVec[m_FrameBuffer[y][x]].g, m_ColorVec[m_FrameBuffer[y][x]].b, 0xff);
                SDL_RenderDrawPoint(pRenderer, x, y);
            }
        }
    }
}

void  FireEffect::Quit()
{
    m_bIsOver = true;
}

int  FireEffect::GetTimePerFrame()
{
    return iTimePerFrame;
}
