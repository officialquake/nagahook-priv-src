
#include "antiafkkick.hpp"



CAfk* afk = new CAfk();

void CAfk::afkkick(CUserCmd* cmd)
{
    if (vars.visuals.antiafkkick && cmd->command_number % 2){
    cmd->buttons |= 1 << 26;
    }
    
}
