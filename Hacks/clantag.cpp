#include "clantag.h"
#include "main.h"
#include "../Utils/utils.h"
#include <iostream>

C_Misc* misc = new C_Misc();
std::string gaytag = "killers.cc";
void C_Misc::clan_tag()
{
    if(!vars.misc.clantag)
        return;
    
    /*int m_iRand = rand() % 4 + 1;
        if (m_iRand == 1) {
            SetClanTag("i kill jews", "i kill jews");
        }
        if (m_iRand == 2) {
            SetClanTag("jews are killed by me", "jews are killed by me");
        }
        if (m_iRand == 3) {
            SetClanTag("jews are the only race that i kill", "jews are the only race that i kill");
        }
        if (m_iRand == 4) {
            SetClanTag("i kill jews for fun", "i kill jews for fun");
        }*/
    static std::string cur_clantag = "        killers.cc";
    static int old_time;
    
    static int i = 0;
    
    if (pEngine->IsInGame()) {
        if (i > 32)
        {
            marquee(cur_clantag);
            SetClanTag(cur_clantag.c_str(), cur_clantag.c_str());
            i = 0;
        }
        else
        {
            i++;
        }
    }
}
