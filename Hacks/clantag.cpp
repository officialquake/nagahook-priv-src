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
        SetClanTag("             ", "D E A D |  デッド");
    }
    else if(ticks > 30 && ticks < 45)
    {
        SetClanTag("            k", "D E A D |  デッド");
    }
    else if(ticks > 60 && ticks < 75)
    {
        SetClanTag("           ki", "D E A D |  デッド");
    }
    else if(ticks > 90 && ticks < 105)
    {
        SetClanTag("          kil", "D E A D |  デッド");
    }
    else if(ticks > 120 && ticks < 135)
    {
        SetClanTag("        kill", "D E A D |  デッド");
    }
    else if(ticks > 150 && ticks < 165)
    {
        SetClanTag("        kille", "D E A D |  デッド");
    }
    else if(ticks > 180 && ticks < 195)
    {
        SetClanTag("       killer", "D E A D |  デッド");
    }
    else if(ticks > 210 && ticks < 225)
    {
        SetClanTag("      killers", "D E A D |  デッド");
    }
    else if(ticks > 240 && ticks < 255)
    {
        SetClanTag("     killers.", "D E A D |  デッド");
    }
    else if(ticks > 270 && ticks < 285)
    {
        SetClanTag("    killers.c", "D E A D |  デッド");
    }
    else if(ticks > 300 && ticks < 315)
    {
        SetClanTag("   killers.cc", "D E A D |  デッド");
    }
    else if(ticks > 330 && ticks < 345)
    {
        SetClanTag("  killers.c", "D E A D |  デッド");
    }
    else if(ticks > 360 && ticks < 375)
    {
        SetClanTag(" killers.", "D E A D |  デッド");
    }
    else if(ticks > 390 && ticks < 405)
    {
        SetClanTag("killers", "D E A D |  デッド");
    }
    else if(ticks > 420 && ticks < 435)
    {
        SetClanTag("killer ", "D E A D |  デッド");
    }
    else if(ticks > 450 && ticks < 465)
    {
        SetClanTag("kille  ", "D E A D |  デッド");
    }
    else if(ticks > 450 && ticks < 495)
    {
        SetClanTag("kill   ", "D E A D |  デッド");
    }
    else if(ticks > 480 && ticks < 525)
    {
        SetClanTag("kil    ", "D E A D |  デッド");
    }
    else if(ticks > 510 && ticks < 555)
    {
        SetClanTag("ki     ", "D E A D |  デッド");
    }
    else if(ticks > 540 && ticks < 585)
    {
        SetClanTag("k      ", "D E A D |  デッド");
    }
    else if(ticks > 570 && ticks < 615)
    {
        SetClanTag("killers.cc       ", "D E A D |  デッド");
    }
    else if(ticks > 600 && ticks < 645)
    {
        SetClanTag("nigger.cc        ", "D E A D |  デッド");
    }
    else if(ticks > 630 && ticks < 675)
    {
        SetClanTag("killers.cc         ", "D E A D |  デッド");
    }
    else if(ticks > 660 && ticks < 705)
    {
        SetClanTag("nigger.cc          ", "D E A D |  デッド");
    }
    else if(ticks > 690 && ticks < 735)
    {
        SetClanTag("killers.cc           ", "D E A D |  デッド");
    }
    else if(ticks > 720 && ticks < 765)
    {
        SetClanTag("killers.cc            ", "D E A D |  デッド");
    }
    
    if (ticks >= 765)
        ticks = 0;
}
