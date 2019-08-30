#include "main.h"
#include <deque>
void DrawOtherESP();
void DrawPlayerESP();

void DrawAngles(C_BaseEntity* local);
void DrawSpread(C_BaseEntity* local);
void pwnmymenu();
void EmitSound(int iEntIndex, const char *pSample);

namespace ESP{
    void CollectFootstep(int iEntIndex, const char *pSample);
    void DrawSounds();
    void EmitSound(int iEntIndex, const char *pSample);
}
