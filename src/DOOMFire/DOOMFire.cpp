#include "FireEffect.h"
#include <iostream>


int main(int argc, char* argv[])
{
    FireEffect *pfireEffect = new FireEffect();
    while (!pfireEffect->IsOver())
    {
        pfireEffect->ProcessInput();
        pfireEffect->Update();
        pfireEffect->Render();
        //pfireEffect->Delay();
    }

    pfireEffect->Clean();

    delete pfireEffect;

    return 0;
}
