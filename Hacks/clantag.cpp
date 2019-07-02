#include "clantag.h"
#include "main.h"

C_Misc* misc = new C_Misc();
void C_Misc::clan_tag()
{
    if(!vars.misc.clantag)
        return;

    static int ticks = 0; ticks++;
    
    if(ticks > 0 && ticks < 15)
    {
        SetClanTag("             ", "nagahook.cc");
    }
    else if(ticks > 30 && ticks < 45)
    {
        SetClanTag("            n", "nagahook.cc");
    }
    else if(ticks > 60 && ticks < 75)
    {
        SetClanTag("           ni", "nagahook.cc");
    }
    else if(ticks > 90 && ticks < 105)
    {
        SetClanTag("          nig", "nagahook.cc");
    }
    else if(ticks > 120 && ticks < 135)
    {
        SetClanTag("        nigg", "nagahook.cc");
    }
    else if(ticks > 150 && ticks < 165)
    {
        SetClanTag("        nigge", "nagahook.cc");
    }
    else if(ticks > 180 && ticks < 195)
    {
        SetClanTag("       nigger", "nagahook.cc");
    }
    else if(ticks > 210 && ticks < 225)
    {
        SetClanTag("      nigger.", "nagahook.cc");
    }
    else if(ticks > 240 && ticks < 255)
    {
        SetClanTag("     nigger.c", "nagahook.cc");
    }
    else if(ticks > 270 && ticks < 285)
    {
        SetClanTag("    nigger.cc", "nagahook.cc");
    }
    else if(ticks > 300 && ticks < 315)
    {
        SetClanTag("   nigger.cc", "nagahook.cc");
    }
    else if(ticks > 330 && ticks < 345)
    {
        SetClanTag("  nagahook.c", "nagahook.cc");
    }
    else if(ticks > 360 && ticks < 375)
    {
        SetClanTag(" nagahook.", "nagahook.cc");
    }
    else if(ticks > 390 && ticks < 405)
    {
        SetClanTag("nagahook", "nagahook.cc");
    }
    else if(ticks > 420 && ticks < 435)
    {
        SetClanTag("nagahoo ", "nagahook.cc");
    }
    else if(ticks > 450 && ticks < 465)
    {
        SetClanTag("nagaho  ", "nagahook.cc");
    }
    else if(ticks > 450 && ticks < 495)
    {
        SetClanTag("nagah   ", "nagahook.cc");
    }
    else if(ticks > 480 && ticks < 525)
    {
        SetClanTag("naga    ", "nagahook.cc");
    }
    else if(ticks > 510 && ticks < 555)
    {
        SetClanTag("nag     ", "nagahook.cc");
    }
    else if(ticks > 540 && ticks < 585)
    {
        SetClanTag("na      ", "nagahook.cc");
    }
    else if(ticks > 570 && ticks < 615)
    {
        SetClanTag("n       ", "nagahook.cc");
    }
    else if(ticks > 600 && ticks < 645)
    {
        SetClanTag("ni        ", "nagahook.cc");
    }
    else if(ticks > 630 && ticks < 675)
    {
        SetClanTag("nig         ", "nagahook.cc");
    }
    else if(ticks > 660 && ticks < 705)
    {
        SetClanTag("nigg          ", "nagahook.cc");
    }
    else if(ticks > 690 && ticks < 735)
    {
        SetClanTag("nigge           ", "nagahook.cc");
    }
    else if(ticks > 720 && ticks < 765)
    {
        SetClanTag("nigger            ", "nagahook.cc");
    }
    
    if (ticks >= 765)
        ticks = 0;
}
