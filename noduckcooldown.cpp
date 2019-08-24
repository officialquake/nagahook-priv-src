#include "main.h"
#include "noduckcooldown.hpp"



CDuck* duck = new CDuck();

void CDuck::DuckCool(CUserCmd* cmd)
{
    if (!vars.misc.noduckcooldown)
        return;
    
    if (cmd->buttons & IN_DUCK)
    {
        static bool counter = false;
        static int counters = 0;
        if (counters == 9)
        {
            counters = 0;
            counter = !counter;
        }
        counters++;
        if (counter)
        {
            cmd->buttons |= IN_DUCK;
            CreateMove::sendPacket = true;
        }
        else
            cmd->buttons &= ~IN_DUCK;
    }

}
