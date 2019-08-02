//
//  Config.cpp
//  vHook
//

#include "../main.h"
#include "Config.h"
#include "skins.h"

using namespace std;

Config* config = new Config();
Config* skins_cfg = new Config();
Skins skin;

const char* ConfigName;
string user     = getenv("USER");
string dsk      = "/Users/" + user + "/Desktop/";
string fdr      = "/Users/" + user + "/Desktop/Nagahook";
string scout    = "/Users/" + user + "/Desktop/Nagahook/scout.ini";
string autos    = "/Users/" + user + "/Desktop/Nagahook/autos.ini";
string legit    = "/Users/" + user + "/Desktop/Nagahook/legit.ini";
string rage    = "/Users/" + user + "/Desktop/Nagahook/rage.ini";
string rifles    = "/Users/" + user + "/Desktop/Nagahook/rifles.ini";
string skins    = "/Users/" + user + "/Desktop/Nagahook/skins.ini";

bool GetBoolValue(bool Value)
{
    return Value;
}

int GetIntValue(int Value)
{
    return Value;
}

float GetFloatValue(float Value)
{
    return Value;
}

void Config::getConfig(int ConfigNo) {
    if(ConfigNo == 0) ConfigName = scout.c_str();
    else if (ConfigNo == 1) ConfigName = autos.c_str();
    else if (ConfigNo == 2) ConfigName = legit.c_str();
    else if (ConfigNo == 3) ConfigName = rage.c_str();
    else if (ConfigNo == 4) ConfigName = rifles.c_str();
}

bool fileExist(const char* path) {
    struct stat info;
    return stat(path, &info) == 0 && S_ISREG(info.st_mode);
}

void Config::LoadConfig() {
    
    cfg.SetUnicode(true);
    cfg.LoadFile(ConfigName);
    
    // Left Aimbot
    vars.aimbot.enabled     = cfgget_b("Aimbot", "Enabled");
    vars.aimbot.silent      = cfgget_b("Aimbot", "Silent");
    vars.aimbot.rcs         = cfgget_b("Aimbot", "RCS");
    vars.aimbot.rcsf        = cfgget_i("Aimbot", "RCSf");
    vars.aimbot.FovToPlayer = cfgget_i("Aimbot", "FOV");
    vars.aimbot.hitbox      = cfgget_i("Aimbot", "Bone");
    
    // Middle Aimbot
    vars.aimbot.autoscope      = cfgget_b("Aimbot", "Auto Scope");
    vars.aimbot.autopistol     = cfgget_b("Aimbot", "Auto Pistol");
    vars.aimbot.autocrouch     = cfgget_b("Aimbot", "Auto Crouch");
    vars.aimbot.hitscan     = cfgget_b("Aimbot", "Hitscan");
    vars.aimbot.autowall     = cfgget_b("Aimbot", "Auto Wall");
    vars.aimbot.mindmg     = cfgget_i("Aimbot", "Mindmg");
    vars.aimbot.Yawresolver     = cfgget_b("Aimbot", "Yaw Resolver");
    vars.aimbot.autoshoot     = cfgget_b("Aimbot", "Auto Shoot");
    vars.aimbot.trigger = cfgget_b("Aimbot", "Triggerbot");
    //vars.aimbot.autostop = cfgget_b("Aimbot", "Auto Stop");
    vars.misc.antiResolverFlip     = cfgget_b("Aimbot", "LBY Flip");
    
    
    
    //Right Aimbot
    vars.misc.antiaim  = (ButtonCode_t)cfgget_b("Aimbot", "AntiAim Enabled");
    vars.misc.thirdpersonmode     = cfgget_b("Aimbot", "Show Real Angles");
    vars.misc.fakeaa     = cfgget_b("Aimbot", "Fake aa");
    vars.misc.aaX     = cfgget_i("Misc", "aaX");
    //vars.aimbot.backtrack      = cfgget_i("Aimbot", "Backtrack");
    vars.aimbot.pointscale     = cfgget_i("Aimbot", "Pointscale");
    vars.misc.aaY     = cfgget_i("Misc", "aaY");
    vars.misc.FaaY     = cfgget_i("Misc", "FaaY");
    vars.misc.MaaY     = cfgget_i("Misc", "MaaY");
    vars.visuals.nosmoke     = cfgget_b("Misc", "No Smoke");
    vars.misc.noduckcooldown     = cfgget_b("Misc", "No Duck");
    vars.aimbot.fakewalk     = cfgget_b("Misc", "Fake Walk");
    vars.aimbot.fakewalktype     = cfgget_i("Misc", "FakeWalkT");
    vars.aimbot.backtrack = cfgget_b("Aimbot", "Backtrack");
    vars.aimbot.accuracyhithcance = cfgget_i("Aimbot", "ACHC");
    vars.aimbot.hitscantype = cfgget_i("Aimbot", "HT");
    vars.aimbot.freestand = cfgget_b("Aimbot", "FT");
    vars.aimbot.hitchance = cfgget_b("Aimbot", "Hitchance");
    vars.aimbot.jitter = cfgget_i("Aimbot", "Jitter");
    
    // Left Visuals
    vars.visuals.enabled    = cfgget_b("Visuals", "Enabled");
    vars.visuals.enemyonly  = cfgget_b("Visuals", "Enemy Only");
    vars.visuals.visonly       = cfgget_b("Visuals", "Vis Only");
    vars.visuals.box   = cfgget_b("Visuals", "Box");
    vars.visuals.name       = cfgget_b("Visuals", "Name ESP");
    vars.visuals.health       = cfgget_b("Visuals", "Health");
    vars.visuals.armour     = cfgget_b("Visuals", "Armour");
    vars.visuals.healthtext    = cfgget_b("Visuals", "Health Text");
    vars.visuals.skeleton       = cfgget_b("Visuals", "Skeleton");
    vars.visuals.snapline       = cfgget_b("Visuals", "Snap Line");
    vars.visuals.bombtimer       = cfgget_b("Visuals", "Bomb Timer");
    vars.visuals.scoped       = cfgget_b("Visuals", "Scoped");
    vars.visuals.rcrosshair       = cfgget_b("Visuals", "RC");
    vars.visuals.scrosshair       = cfgget_b("Visuals", "SC");
    vars.visuals.active       = cfgget_b("Visuals", "Weapon");
    vars.visuals.grenade       = cfgget_b("Visuals", "Grenade");
    //vars.mi       = cfgget_b("Visuals", "SC");
    
    
    
    // Middle Visuals
    vars.visuals.skinc = cfgget_b("Visuals", "Skin Changer");
    vars.visuals.defusing       = cfgget_b("Visuals", "Defusing");
    vars.visuals.rescuing       = cfgget_b("Visuals", "Rescuing");
    vars.visuals.antiaim_indicator = cfgget_b("Visuals", "AA Indicator");
    vars.visuals.indicatorAA_types = cfgget_i("Visuals", "AA Indicator Type");
    vars.visuals.antiaiminfos = cfgget_b("Visuals", "AA Info");
    vars.visuals.direction = cfgget_b("Visuals", "Direction");
    //vars.visuals.grenade = cfgget_b("Visuals", "Grenade ESP");
    
    // Right Visual
    vars.visuals.chams= cfgget_b("Visuals", "Player Chams");
    vars.visuals.aaline= cfgget_b("Visuals", "AA Line");
    vars.visuals.anglelinenames= cfgget_b("Visuals", "AA Line Names");
    
    vars.visuals.handchams       = cfgget_b("Visuals", "Hand Chams");
    vars.visuals.weaponchams       = cfgget_b("Visuals", "Weapon Chams");
    vars.visuals.playerchams_alpha       = cfgget_i("Visuals", "PCA");
    vars.visuals.handchams_alpha       = cfgget_i("Visuals", "HCA");
    vars.visuals.weaponchams_alpha       = cfgget_i("Visuals", "WCA");
    
    vars.visuals.playersType = cfgget_i("Visuals", "Players Type");
    vars.visuals.handsType       = cfgget_i("Visuals", "Hand Type");
    vars.visuals.weaponType       = cfgget_i("Visuals", "Weapon Type");
    vars.visuals.weapons       = cfgget_b("Visuals", "Dropped Weapons");
    
    vars.visuals.hitmarker       = cfgget_b("Visuals", "Hitmarkers");
    vars.visuals.hitmarkersounds       = cfgget_b("Visuals", "Hitmarkers Sounds");
    vars.visuals.hitsize       = cfgget_i("Visuals", "Hitmarker Size");
    vars.visuals.hitduration       = cfgget_i("Visuals", "Hitmarker Duration");
    vars.visuals.hitinnergap       = cfgget_i("Visuals", "Hitmarker Inner Gap");
    vars.visuals.allieshit       = cfgget_b("Visuals", "Hitmarkers Allies");
    vars.visuals.enemyhit       = cfgget_b("Visuals", "Hitmarkers Enemies");
    
    
    // Misc Left
    vars.misc.enabled = cfgget_b("Misc", "Enabled");
    vars.misc.antiuntrust = cfgget_b("Misc", "Antiunt");
    vars.misc.bhop          = cfgget_b("Misc", "Bhop");
    vars.misc.autostrafe          = cfgget_b("Misc", "Auto Strafe");
    vars.misc.cstrafe          = cfgget_b("Misc", "cStrafe");
    vars.misc.fov           = cfgget_i("Misc", "FOVf");
    vars.misc.tpoffset           = cfgget_i("Misc", "TPOff");
    vars.misc.fovt = cfgget_b("Misc", "FOV");
    vars.misc.watermark     = cfgget_b("Misc", "Watermark");
    vars.misc.norecoil      = cfgget_b("Misc", "No Recoil");
    vars.misc.novisual= cfgget_b("Misc", "No Visual Recoil");
    vars.misc.spammer = cfgget_b("Misc", "Chat Spam");
    vars.misc.moonwalk = cfgget_b("Misc", "Moonwalk");
    vars.misc.clantag = cfgget_b("Misc", "Clantag");
    vars.misc.spreadcrosshair = cfgget_b("Misc", "Spread");
    
    
    //Misc Right
    vars.misc.noflash       = cfgget_b("Misc", "No Flash Enable");
    vars.misc.flashalpha    = cfgget_i("Misc", "Flash Alpha");
    vars.misc.noscope = cfgget_b("Misc", "No Scope");
    vars.misc.fakelag = cfgget_b("Misc", "Fake Lag");
    vars.misc.fakelagfactor = cfgget_i("Misc", "FakeLagf");
    vars.misc.adaptive = cfgget_b("Misc", "Adaptive");
    // vars.misc.nightmode = cfgget_b("Misc", "Night Mode");
    vars.misc.asuswalls = cfgget_b("Misc", "Asus Walls");
    vars.misc.worldpaint = cfgget_b("Misc", "World Paint");
    vars.misc.antiscreenshot = cfgget_b("Misc", "Anti Screenshot");
    vars.misc.showspectators = cfgget_b("Misc", "Show Spectators");
    vars.misc.attargets = cfgget_b("Misc", "At Target");
    vars.misc.delta = cfgget_i("Aimbot", "Delta");
    vars.misc.Yoffset = cfgget_i("Aimbot", "Y Offset");
    vars.misc.turbojizzer = cfgget_b("Aimbot", "Turbo");
    vars.misc.backjizzer = cfgget_b("Aimbot", "Back");
    vars.misc.lby_spin = cfgget_b("Aimbot", "LBY Spin");
    vars.misc.tank = cfgget_b("Aimbot", "Tank");
    vars.misc.radar = cfgget_b("Aimbot", "Radar");
    //vars.aimbot.autocock = cfgget_b("Aimbot", "Auto Cock");
    vars.aimbot.baimhp = cfgget_b("Aimbot", "Baim");
    vars.aimbot.baimxhp = cfgget_i("Aimbot", "BaimxHP");
    vars.misc.asusalpha = cfgget_f("Misc", "ASUSA");
    
    
    //Colours
    /*vars.colors.pchamr      = cfgget_f("Colours", "pChamr");
     vars.colors.pchamg      = cfgget_f("Colours", "pChamg");
     vars.colors.pchamb      = cfgget_f("Colours", "pChamb");
     
     
     vars.colors.boxr        = cfgget_f("Colours", "boxr");
     vars.colors.boxg        = cfgget_f("Colours", "boxg");
     vars.colors.boxb        = cfgget_f("Colours", "boxb");
     
     vars.colors.pignr       = cfgget_f("Colours", "cignr");
     vars.colors.pigng       = cfgget_f("Colours", "cigng");
     vars.colors.pignb       = cfgget_f("Colours", "cignb");
     
     vars.colors.bignr       = cfgget_f("Colours", "bignr");
     vars.colors.bigng       = cfgget_f("Colours", "bigng");
     vars.colors.bignb       = cfgget_f("Colours", "bignb");
     */
    
}



void Config::SaveConfig() {
    
    
    if(!fileExist(dsk.c_str()))
        mkdir(dsk.c_str(), 0775);
    
    if(!fileExist(fdr.c_str()))
        mkdir(fdr.c_str(), 0775);
    
    
    //CSimpleIniA cfg;
    cfg.SetUnicode(true);
    
    // cfg.SetLongValue("Bindings", "Aimlock Key", GetFloatValue((int)vars.aimbot.aimKey));
    //cfg.SetLongValue("Bindings", "Trigger Key", GetFloatValue((int)vars.aimbot.triggerKey));
    
    // Left Aimbot
    cfg.SetBoolValue("Aimbot", "Enabled", GetBoolValue(vars.aimbot.enabled));
    cfg.SetBoolValue("Aimbot", "RCS", GetBoolValue(vars.aimbot.rcs));
    cfg.SetLongValue("Aimbot", "RCSf", GetIntValue(vars.aimbot.rcsf));
    cfg.SetLongValue("Aimbot", "FOV", GetIntValue(vars.aimbot.FovToPlayer));
    cfg.SetLongValue("Aimbot", "Bone", GetIntValue(vars.aimbot.hitbox));
    cfg.SetBoolValue("Aimbot", "Triggerbot", GetBoolValue(vars.aimbot.trigger));
    //cfg.SetBoolValue("Aimbot", "Auto Stop", GetBoolValue(vars.aimbot.autostop));
    cfg.SetBoolValue("Aimbot", "Silent", GetBoolValue(vars.aimbot.silent));
    cfg.SetBoolValue("Aimbot", "Auto Scope", GetBoolValue(vars.aimbot.autoscope));
    cfg.SetBoolValue("Aimbot", "Auto Shoot", GetBoolValue(vars.aimbot.autoshoot));
    cfg.SetBoolValue("Aimbot", "Auto Crouch", GetBoolValue(vars.aimbot.autocrouch));
    cfg.SetBoolValue("Aimbot", "Auto Pistol", GetBoolValue(vars.aimbot.autopistol));
    cfg.SetBoolValue("Aimbot", "Yaw Resolver", GetBoolValue(vars.aimbot.Yawresolver));
    cfg.SetBoolValue("Aimbot", "Auto Wall", GetBoolValue(vars.aimbot.autowall));
    cfg.SetBoolValue("Aimbot", "Hitscan", GetBoolValue(vars.aimbot.hitscan));
    cfg.SetLongValue("Aimbot", "Mindmg", GetIntValue(vars.aimbot.mindmg));
    cfg.SetBoolValue("Aimbot", "LBY Flip", GetBoolValue(vars.misc.antiResolverFlip));
    cfg.SetBoolValue("Aimbot", "LBY Spin", GetBoolValue(vars.misc.lby_spin));
    cfg.SetBoolValue("Aimbot", "Hitchance", GetBoolValue(vars.aimbot.hitchance));
    cfg.SetBoolValue("Aimbot", "AntiAim Enabled", GetBoolValue(vars.misc.antiaim));
    //cfg.SetBoolValue("Aimbot", "Auto Cock", GetBoolValue(vars.aimbot.autocock));
    
    cfg.SetBoolValue("Misc", "Fake Walk", GetBoolValue(vars.aimbot.fakewalk));
    cfg.SetLongValue("Misc", "FakeWalkT", GetIntValue(vars.aimbot.fakewalktype));
    cfg.SetBoolValue("Misc", "No Smoke", GetBoolValue(vars.visuals.nosmoke));
    cfg.SetBoolValue("Misc", "No Duck", GetBoolValue(vars.misc.noduckcooldown));
    //cfg.SetBoolValue("Aimbot", "Backtrack", GetBoolValue(vars.misc.backtrack));
    cfg.SetLongValue("Aimbot", "ACHC", GetIntValue(vars.aimbot.accuracyhithcance));
    cfg.SetLongValue("Aimbot", "HT", GetIntValue(vars.aimbot.hitscantype));
    
    // Visuals
    cfg.SetBoolValue("Visuals", "Enabled", GetBoolValue(vars.visuals.enabled));
    cfg.SetBoolValue("Visuals", "Box", GetBoolValue(vars.visuals.box));
    cfg.SetBoolValue("Visuals", "Name ESP", GetBoolValue(vars.visuals.name));
    cfg.SetBoolValue("Visuals", "Health", GetBoolValue(vars.visuals.health));
    cfg.SetBoolValue("Visuals", "Health text", GetBoolValue(vars.visuals.healthtext));
    cfg.SetBoolValue("Visuals", "Snap Line", GetBoolValue(vars.visuals.snapline));
    cfg.SetBoolValue("Visuals", "Hand Chams", GetBoolValue(vars.visuals.handchams));
    cfg.SetBoolValue("Visuals", "Weapon Chams", GetBoolValue(vars.visuals.weaponchams));
    cfg.SetBoolValue("Visuals", "Weapons", GetBoolValue(vars.visuals.weapons));
    cfg.SetBoolValue("Visuals", "Skeleton", GetBoolValue(vars.visuals.skeleton));
    cfg.SetBoolValue("Visuals", "Chams", GetBoolValue(vars.visuals.chams));
    cfg.SetBoolValue("Visuals", "Enemy Only", GetBoolValue(vars.visuals.enemyonly));
    cfg.SetBoolValue("Visuals", "Bomb Timer", GetBoolValue(vars.visuals.bombtimer));
    cfg.SetBoolValue("Visuals", "Scoped", GetBoolValue(vars.visuals.scoped));
    cfg.SetBoolValue("Visuals", "RC", GetBoolValue(vars.visuals.rcrosshair));
    cfg.SetBoolValue("Visuals", "SC", GetBoolValue(vars.visuals.scrosshair));
    cfg.SetBoolValue("Visuals", "Weapon", GetBoolValue(vars.visuals.active));
    cfg.SetBoolValue("Visuals", "Grenade", GetBoolValue(vars.visuals.grenade));
    cfg.SetBoolValue("Visuals", "Vis Only", GetBoolValue(vars.visuals.visonly));
    
    
    cfg.SetLongValue("Visuals", "Hand Type", GetIntValue(vars.visuals.handsType));
    cfg.SetLongValue("Visuals", "Players Type", GetIntValue(vars.visuals.playersType));
    cfg.SetLongValue("Visuals", "Weapon Type", GetIntValue(vars.visuals.weaponType));
    
    
    cfg.SetBoolValue("Visuals", "Player Chams", GetBoolValue(vars.visuals.chams));
    cfg.SetBoolValue("Visuals", "AA Line", GetBoolValue(vars.visuals.aaline));
    cfg.SetBoolValue("Visuals", "AA Line Names", GetBoolValue(vars.visuals.anglelinenames));
    cfg.SetBoolValue("Visuals", "Hand Chams", GetBoolValue(vars.visuals.handchams));
    cfg.SetBoolValue("Visuals", "Weapon Chams", GetBoolValue(vars.visuals.weaponchams));
    cfg.SetBoolValue("Visuals", "Dropped Weapons", GetBoolValue(vars.visuals.weapons));
    cfg.SetBoolValue("Visuals", "Defusing", GetBoolValue(vars.visuals.defusing));
    
    cfg.SetLongValue("Visuals", "PCA", GetIntValue(vars.visuals.playerchams_alpha));
    cfg.SetLongValue("Visuals", "HCA", GetIntValue(vars.visuals.handchams_alpha));
    cfg.SetLongValue("Visuals", "WCA", GetIntValue(vars.visuals.weaponchams_alpha));
    
    //cfg.SetBoolValue("Visuals", "Grenade ESP", GetBoolValue(vars.visuals.grenade));
    cfg.SetBoolValue("Visuals", "Direction", GetBoolValue(vars.visuals.direction));
    cfg.SetBoolValue("Visuals", "AA Info", GetBoolValue(vars.visuals.antiaiminfos));
    cfg.SetBoolValue("Visuals", "AA Indicator", GetBoolValue(vars.visuals.antiaim_indicator));
    cfg.SetLongValue("Visuals", "AA Indicator Type", GetIntValue(vars.visuals.indicatorAA_types));
    
    cfg.SetBoolValue("Visuals", "Hitmarkers", GetBoolValue(vars.visuals.hitmarker));
    cfg.SetBoolValue("Visuals", "Hitmarkers Sounds", GetBoolValue(vars.visuals.hitmarkersounds));
    cfg.SetLongValue("Visuals", "Hitmarker Size", GetIntValue(vars.visuals.hitsize));
    cfg.SetLongValue("Visuals", "Hitmarker Duration", GetIntValue(vars.visuals.hitduration));
    cfg.SetLongValue("Visuals", "Hitmarker Inner Gap", GetIntValue(vars.visuals.hitinnergap));
    cfg.SetBoolValue("Visuals", "Hitmarkers Allies", GetBoolValue(vars.visuals.allieshit));
    cfg.SetBoolValue("Visuals", "Hitmarkers Enemies", GetBoolValue(vars.visuals.enemyhit));
    // Misc
    cfg.SetBoolValue("Misc", "Enabled", GetBoolValue(vars.misc.enabled));
    cfg.SetBoolValue("Misc", "No Recoil", GetBoolValue(vars.misc.norecoil));
    cfg.SetBoolValue("Misc", "No Visual Recoil", GetBoolValue(vars.misc.novisual));
    cfg.SetBoolValue("Misc", "Bhop", GetBoolValue(vars.misc.bhop));
    cfg.SetBoolValue("Misc", "Auto Strafe", GetBoolValue(vars.misc.autostrafe));
    cfg.SetBoolValue("Misc", "cStrafe", GetBoolValue(vars.misc.cstrafe));
    cfg.SetBoolValue("Misc", "Airstuck", GetBoolValue(vars.misc.airstuck));
    cfg.SetBoolValue("Misc", "Show Rank", GetBoolValue(vars.misc.showrank));
    //cfg.SetBoolValue("Misc", "Asus", GetBoolValue(vars.misc.asuswalls));
    cfg.SetBoolValue("Misc", "No Flash Enable", GetBoolValue(vars.misc.noflash));
    cfg.SetLongValue("Misc", "Flash Alpha", GetIntValue(vars.misc.flashalpha));
    cfg.SetBoolValue("Misc", "Chat Spam", GetBoolValue(vars.misc.spammer));
    cfg.SetBoolValue("Misc", "Clantag", GetBoolValue(vars.misc.clantag));
    cfg.SetBoolValue("Visuals", "Skin Changer", GetBoolValue(vars.visuals.skinc));
    cfg.SetBoolValue("Misc", "Antiunt", GetBoolValue(vars.misc.antiuntrust));
    
    cfg.SetLongValue("Misc", "FOVf", GetIntValue(vars.misc.fov));
    cfg.SetLongValue("Misc", "TPOff", GetIntValue(vars.misc.tpoffset));
    cfg.SetBoolValue("Misc", "FOV", GetBoolValue(vars.misc.fovt));
    cfg.SetBoolValue("Misc", "Moonwalk", GetBoolValue(vars.misc.moonwalk));
    cfg.SetBoolValue("Misc", "Watermark", GetBoolValue(vars.misc.watermark));
    cfg.SetBoolValue("Misc", "No Scope", GetBoolValue(vars.misc.noscope));
    cfg.SetBoolValue("Misc", "Spread", GetBoolValue(vars.misc.spreadcrosshair));
    cfg.SetBoolValue("Misc", "Fake Lag", GetBoolValue(vars.misc.fakelag));
    cfg.SetLongValue("Misc", "FakeLagf", GetIntValue(vars.misc.fakelagfactor));
    cfg.SetBoolValue("Misc", "Adaptive", GetBoolValue(vars.misc.adaptive));
    // cfg.SetBoolValue("Misc", "Night Mode", GetBoolValue(vars.misc.nightmode));
    cfg.SetBoolValue("Misc", "Asus Walls", GetBoolValue(vars.misc.asuswalls));
    cfg.SetBoolValue("Misc", "World Paint", GetBoolValue(vars.misc.worldpaint));
    cfg.SetBoolValue("Misc", "Anti Screenshot", GetBoolValue(vars.misc.antiscreenshot));
    cfg.SetBoolValue("Misc", "Show Spectators", GetBoolValue(vars.misc.showspectators));
    cfg.SetLongValue("Aimbot", "Delta", GetIntValue(vars.misc.delta));
    cfg.SetLongValue("Aimbot", "Jitter", GetIntValue(vars.aimbot.jitter));
    cfg.SetLongValue("Aimbot", "Y Offset", GetIntValue(vars.misc.Yoffset));
    cfg.SetBoolValue("Aimbot", "Turbo", GetBoolValue(vars.misc.turbojizzer));
    cfg.SetBoolValue("Aimbot", "Back", GetBoolValue(vars.misc.backjizzer));
    cfg.SetBoolValue("Aimbot", "LBY", GetBoolValue(vars.misc.turbojizzer));
    cfg.SetBoolValue("Aimbot", "Tank", GetBoolValue(vars.misc.tank));
    cfg.SetBoolValue("Aimbot", "FT", GetBoolValue(vars.aimbot.freestand));
    cfg.SetBoolValue("Aimbot", "Backtrack", GetBoolValue(vars.aimbot.backtrack));
    cfg.SetBoolValue("Aimbot", "Radar", GetBoolValue(vars.misc.radar));
    cfg.SetBoolValue("Aimbot", "Baim", GetBoolValue(vars.aimbot.baimhp));
    cfg.SetLongValue("Aimbot", "Pointscale", GetIntValue(vars.aimbot.pointscale));
    cfg.SetLongValue("Aimbot", "BaimxHP", GetIntValue(vars.aimbot.baimxhp));
    cfg.SetDoubleValue("Aimbot", "ASUSA", GetFloatValue(vars.misc.asusalpha));
    
    
    
    //cfg.SetDoubleValue("Misc", "Airstuck Key", GetFloatValue((int)vars.misc.airstuck));
    
    
    //Colours
    /*
     cfg.SetDoubleValue("Colors", "pChamr", GetFloatValue(vars.colors.pchamr));
     cfg.SetDoubleValue("Colors", "pChamg", GetFloatValue(vars.colors.pchamg));
     cfg.SetDoubleValue("Colors", "pChamb", GetFloatValue(vars.colors.pchamb));
     
     cfg.SetDoubleValue("Colors", "boxr", GetFloatValue(vars.colors.boxr));
     cfg.SetDoubleValue("Colors", "boxg", GetFloatValue(vars.colors.boxg));
     cfg.SetDoubleValue("Colors", "boxb", GetFloatValue(vars.colors.boxb));
     
     cfg.SetDoubleValue("Colors", "cignr", GetFloatValue(vars.colors.pignr));
     cfg.SetDoubleValue("Colors", "cigng", GetFloatValue(vars.colors.pigng));
     cfg.SetDoubleValue("Colors", "cignb", GetFloatValue(vars.colors.pignb));
     
     cfg.SetDoubleValue("Colors", "bignr", GetFloatValue(vars.colors.bignr));
     cfg.SetDoubleValue("Colors", "bigng", GetFloatValue(vars.colors.bigng));
     cfg.SetDoubleValue("Colors", "bignb", GetFloatValue(vars.colors.bignb));
     */
    
    // AA
    cfg.SetBoolValue("Aimbot", "Show Real Angles", GetBoolValue(vars.misc.thirdpersonmode));
    cfg.SetBoolValue("Misc", "aa", GetBoolValue(vars.misc.antiaim));
    cfg.SetBoolValue("Misc", "At Target", GetBoolValue(vars.misc.attargets));
    cfg.SetBoolValue("Aimbot", "Fake aa", GetBoolValue(vars.misc.fakeaa));
    
    cfg.SetLongValue("Misc", "aaX", GetIntValue(vars.misc.aaX));
    cfg.SetLongValue("Misc", "aaY", GetIntValue(vars.misc.aaY));
    cfg.SetLongValue("Misc", "FaaY", GetIntValue(vars.misc.FaaY));
    cfg.SetLongValue("Misc", "MaaY", GetIntValue(vars.misc.aaY));
    
    
    
    
    
    
    cfg.SaveFile(ConfigName);
    
}

void Config::InitSkins() {
    
    if(fileExist(skins.c_str()))
        return;
    
    skins_cfg.SetUnicode(true);
    
    skins_cfg.SetDoubleValue("weapon_deagle", "id", GetFloatValue(skin.deagle));
    skins_cfg.SetDoubleValue("weapon_elite", "id", GetFloatValue(skin.dual));
    skins_cfg.SetDoubleValue("weapon_fiveseven", "id", GetFloatValue(skin.five7));
    skins_cfg.SetDoubleValue("weapon_glock", "id", GetFloatValue(skin.glock));
    skins_cfg.SetDoubleValue("weapon_ak47", "id", GetFloatValue(skin.ak47));
    skins_cfg.SetDoubleValue("weapon_aug", "id", GetFloatValue(skin.aug));
    skins_cfg.SetDoubleValue("weapon_awp", "id", GetFloatValue(skin.awp));
    skins_cfg.SetDoubleValue("weapon_famas", "id", GetFloatValue(skin.famas));
    skins_cfg.SetDoubleValue("weapon_g3sg1", "id", GetFloatValue(skin.g3));
    skins_cfg.SetDoubleValue("weapon_galilar", "id", GetFloatValue(skin.galil));
    skins_cfg.SetDoubleValue("weapon_m249", "id", GetFloatValue(skin.m249));
    skins_cfg.SetDoubleValue("weapon_m4a1", "id", GetFloatValue(skin.m4a4));
    skins_cfg.SetDoubleValue("weapon_mac10", "id", GetFloatValue(skin.mac10));
    skins_cfg.SetDoubleValue("weapon_p90", "id", GetFloatValue(skin.p90));
    skins_cfg.SetDoubleValue("weapon_ump45", "id", GetFloatValue(skin.ump));
    skins_cfg.SetDoubleValue("weapon_xm1014", "id", GetFloatValue(skin.xm));
    skins_cfg.SetDoubleValue("weapon_bizon", "id", GetFloatValue(skin.bizon));
    skins_cfg.SetDoubleValue("weapon_mag7", "id", GetFloatValue(skin.mag7));
    skins_cfg.SetDoubleValue("weapon_negev", "id", GetFloatValue(skin.negev));
    skins_cfg.SetDoubleValue("weapon_sawedoff", "id", GetFloatValue(skin.sawed));
    skins_cfg.SetDoubleValue("weapon_tec9", "id", GetFloatValue(skin.tec9));
    skins_cfg.SetDoubleValue("weapon_hkp2000", "id", GetFloatValue(skin.p2000));
    skins_cfg.SetDoubleValue("weapon_mp7", "id", GetFloatValue(skin.mp7));
    skins_cfg.SetDoubleValue("weapon_mp9", "id", GetFloatValue(skin.mp9));
    skins_cfg.SetDoubleValue("weapon_nova", "id", GetFloatValue(skin.nova));
    skins_cfg.SetDoubleValue("weapon_p250", "id", GetFloatValue(skin.p250));
    skins_cfg.SetDoubleValue("weapon_scar20", "id", GetFloatValue(skin.scar));
    skins_cfg.SetDoubleValue("weapon_sg556", "id", GetFloatValue(skin.sg));
    skins_cfg.SetDoubleValue("weapon_ssg08", "id", GetFloatValue(skin.scout));
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "id", GetFloatValue(skin.m4a1));
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "id", GetFloatValue(skin.usp));
    skins_cfg.SetDoubleValue("weapon_cz75a", "id", GetFloatValue(skin.cz));
    skins_cfg.SetDoubleValue("weapon_revolver", "id", GetFloatValue(skin.revolver));
    skins_cfg.SetDoubleValue("weapon_knife", "id", GetFloatValue(skin.CTknifeID));
    skins_cfg.SetDoubleValue("weapon_knife", "itemdef", GetFloatValue(skin.knifeCT));
    skins_cfg.SetDoubleValue("weapon_knife_t", "id", GetFloatValue(skin.TknifeID));
    skins_cfg.SetDoubleValue("weapon_knife_t", "itemdef", GetFloatValue(skin.knifeT));
    skins_cfg.SetDoubleValue("glove_t", "id", GetFloatValue(skin.TgloveID));
    skins_cfg.SetDoubleValue("glove_t", "itemdef", GetFloatValue(skin.gloveT));
    skins_cfg.SetDoubleValue("glove_ct", "id", GetFloatValue(skin.CTgloveID));
    skins_cfg.SetDoubleValue("glove_ct", "itemdef", GetFloatValue(skin.gloveCT));
    
    // Seeds
    
    
    
    skins_cfg.SaveFile(skins.c_str());
    
}

void Config::UpdateSkins() {
    
    skins_cfg.SetUnicode(true);
    
    skins_cfg.SetDoubleValue("weapon_deagle", "id", GetFloatValue(skin.deagle));
    skins_cfg.SetDoubleValue("weapon_elite", "id", GetFloatValue(skin.dual));
    skins_cfg.SetDoubleValue("weapon_fiveseven", "id", GetFloatValue(skin.five7));
    skins_cfg.SetDoubleValue("weapon_glock", "id", GetFloatValue(skin.glock));
    skins_cfg.SetDoubleValue("weapon_ak47", "id", GetFloatValue(skin.ak47));
    skins_cfg.SetDoubleValue("weapon_aug", "id", GetFloatValue(skin.aug));
    skins_cfg.SetDoubleValue("weapon_awp", "id", GetFloatValue(skin.awp));
    skins_cfg.SetDoubleValue("weapon_famas", "id", GetFloatValue(skin.famas));
    skins_cfg.SetDoubleValue("weapon_g3sg1", "id", GetFloatValue(skin.g3));
    skins_cfg.SetDoubleValue("weapon_galilar", "id", GetFloatValue(skin.galil));
    skins_cfg.SetDoubleValue("weapon_m249", "id", GetFloatValue(skin.m249));
    skins_cfg.SetDoubleValue("weapon_m4a1", "id", GetFloatValue(skin.m4a4));
    skins_cfg.SetDoubleValue("weapon_mac10", "id", GetFloatValue(skin.mac10));
    skins_cfg.SetDoubleValue("weapon_p90", "id", GetFloatValue(skin.p90));
    skins_cfg.SetDoubleValue("weapon_ump45", "id", GetFloatValue(skin.ump));
    skins_cfg.SetDoubleValue("weapon_xm1014", "id", GetFloatValue(skin.xm));
    skins_cfg.SetDoubleValue("weapon_bizon", "id", GetFloatValue(skin.bizon));
    skins_cfg.SetDoubleValue("weapon_mag7", "id", GetFloatValue(skin.mag7));
    skins_cfg.SetDoubleValue("weapon_negev", "id", GetFloatValue(skin.negev));
    skins_cfg.SetDoubleValue("weapon_sawedoff", "id", GetFloatValue(skin.sawed));
    skins_cfg.SetDoubleValue("weapon_tec9", "id", GetFloatValue(skin.tec9));
    skins_cfg.SetDoubleValue("weapon_hkp2000", "id", GetFloatValue(skin.p2000));
    skins_cfg.SetDoubleValue("weapon_mp7", "id", GetFloatValue(skin.mp7));
    skins_cfg.SetDoubleValue("weapon_mp9", "id", GetFloatValue(skin.mp9));
    skins_cfg.SetDoubleValue("weapon_nova", "id", GetFloatValue(skin.nova));
    skins_cfg.SetDoubleValue("weapon_p250", "id", GetFloatValue(skin.p250));
    skins_cfg.SetDoubleValue("weapon_scar20", "id", GetFloatValue(skin.scar));
    skins_cfg.SetDoubleValue("weapon_sg556", "id", GetFloatValue(skin.sg));
    skins_cfg.SetDoubleValue("weapon_ssg08", "id", GetFloatValue(skin.scout));
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "id", GetFloatValue(skin.m4a1));
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "id", GetFloatValue(skin.usp));
    skins_cfg.SetDoubleValue("weapon_cz75a", "id", GetFloatValue(skin.cz));
    skins_cfg.SetDoubleValue("weapon_revolver", "id", GetFloatValue(skin.revolver));
    skins_cfg.SetDoubleValue("weapon_knife", "id", GetFloatValue(skin.CTknifeID));
    skins_cfg.SetDoubleValue("weapon_knife", "itemdef", GetFloatValue(skin.knifeCT));
    skins_cfg.SetDoubleValue("weapon_knife_t", "id", GetFloatValue(skin.TknifeID));
    skins_cfg.SetDoubleValue("weapon_knife_t", "itemdef", GetFloatValue(skin.knifeT));
    skins_cfg.SetDoubleValue("glove_t", "id", GetFloatValue(skin.TgloveID));
    skins_cfg.SetDoubleValue("glove_t", "itemdef", GetFloatValue(skin.gloveT));
    skins_cfg.SetDoubleValue("glove_ct", "id", GetFloatValue(skin.CTgloveID));
    skins_cfg.SetDoubleValue("glove_ct", "itemdef", GetFloatValue(skin.gloveCT));
    
    // Seeds
    
    
    
    skins_cfg.SaveFile(skins.c_str());
    
}

void Config::LoadSkins() {
    
    if(!fileExist(skins.c_str()))
        InitSkins();
    
    skins_cfg.SetUnicode(true);
    skins_cfg.LoadFile(skins.c_str());
    
    skin.TknifeID   = skin_cfgget_f("weapon_knife_t", "id");
    skin.CTknifeID  = skin_cfgget_f("weapon_knife", "id");
    
    skin.TgloveID = skin_cfgget_f("glove_t", "id");
    skin.CTgloveID = skin_cfgget_f("glove_ct", "id");
    
    skin.galil   = skin_cfgget_f("weapon_galilar", "id");
    skin.famas   = skin_cfgget_f("weapon_famas", "id");
    skin.ak47      = skin_cfgget_f("weapon_ak47", "id");
    skin.m4a4      = skin_cfgget_f("weapon_m4a1", "id");
    skin.m4a1      = skin_cfgget_f("weapon_m4a1_silencer", "id");
    skin.scout   = skin_cfgget_f("weapon_ssg08", "id");
    skin.sg      = skin_cfgget_f("weapon_sg556", "id");
    skin.aug     = skin_cfgget_f("weapon_aug", "id");
    skin.awp     = skin_cfgget_f("weapon_awp", "id");
    skin.g3      = skin_cfgget_f("weapon_scar20", "id");
    skin.scar    = skin_cfgget_f("weapon_g3sg1", "id");
    
    skin.glock   = skin_cfgget_f("weapon_glock", "id");
    skin.usp     = skin_cfgget_f("weapon_usp_silencer", "id");
    skin.p2000   = skin_cfgget_f("weapon_hkp2000", "id");
    skin.dual    = skin_cfgget_f("weapon_elite", "id");
    skin.p250    = skin_cfgget_f("weapon_p250", "id");
    skin.tec9    = skin_cfgget_f("weapon_tec9", "id");
    skin.five7   = skin_cfgget_f("weapon_fiveseven", "id");
    skin.cz      = skin_cfgget_f("weapon_cz75a", "id");
    skin.deagle  = skin_cfgget_f("weapon_deagle", "id");
    skin.revolver      = skin_cfgget_f("weapon_revolver", "id");
    
    skin.mac10   = skin_cfgget_f("weapon_mac10", "id");
    skin.mp9     = skin_cfgget_f("weapon_mp9", "id");
    skin.mp7     = skin_cfgget_f("weapon_mp7", "id");
    skin.ump     = skin_cfgget_f("weapon_ump45", "id");
    skin.p90     = skin_cfgget_f("weapon_p90", "id");
    skin.bizon   = skin_cfgget_f("weapon_bizon", "id");
    
    skin.nova    = skin_cfgget_f("weapon_nova", "id");
    skin.sawed   = skin_cfgget_f("weapon_sawedoff", "id");
    skin.mag7    = skin_cfgget_f("weapon_mag7", "id 7");
    skin.xm      = skin_cfgget_f("weapon_xm1014", "id");
    skin.m249    = skin_cfgget_f("weapon_m249", "id");
    skin.negev   = skin_cfgget_f("weapon_negev", "id");
    
}



bool Config::HasWeaponConfiguration(const char* section) {
    skins_cfg.LoadFile(skins.c_str());
    CSimpleIniA::TNamesDepend sections;
    skins_cfg.GetAllSections(sections);
    sections.sort(CSimpleIniA::Entry::LoadOrder());
    
    for (auto sect : sections) {
        if(!strcmp(section, sect.pItem)) {
            return true;
        }
    }
    
    return false;
}


cSkin Config::GetWeaponConfiguration(const char *section) {
    
    skins_cfg.LoadFile(skins.c_str());
    
    cSkin weapon_config;
    
    weapon_config.Paintkit      = (int)skin_cfgget_f(section, "id");
    weapon_config.ItemDefinition= (int)skin_cfgget_f(section, "itemdef");
    
    return weapon_config;
}

