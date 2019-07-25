#include "FireEffect.h"
#include <iostream>


int main(int argc, char* argv[])
{
    FireEffect fireEffect;
    while (!fireEffect.IsOver())
    {
        fireEffect.ProcessInput();
        fireEffect.Update();
        fireEffect.Render();
        fireEffect.Delay();
    }

    return 0;
}
