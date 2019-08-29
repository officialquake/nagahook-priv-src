#include "main.h"
#include "noduckcooldown.hpp"



CDuck* duck = new CDuck();

void CDuck::DuckCool(CUserCmd* cmd)
{
    if (!vars.misc.noduckcooldown)
        return;

    cmd->buttons |= IN_BULLRUSH;
}
 
