#pragma once

class ccombobox // this class only handles all the open checks for the combo boxes, nothing more
{
public:
    
    // Anti aim
    bool aaY_opend;
    bool aaX_opend;
    bool FaaY_opend;
    bool MaaY_opend;
    bool AaaY_opend;
    // Chams
    bool hands_opend;
    bool weapons_opend;
    bool players_opend;
    bool local_opend;
    
    bool fakeping_opend;
    // Menu
    bool legithitscanpri_opend;
    bool colors_opend;
    // Misc
    bool fakelag_opend;
     bool tp_opend;
    bool resolver_opend;
    bool hitscan_opend;
    bool legitaa_opend;
    bool fakewalk_opend;
    bool indicatorAA_opend;
    bool freestand_opend;
    // For aa corrections
    bool playerlist_opend_x[64];
    bool playerlist_opend_y[64];
    
    // Config
    bool mCol_opend;
    bool cfg_opend;
    
    // For text input
    bool misc_name, misc_changename;
    
};

class cVariables : public ccombobox
{
public:
    
    bool menu               = false;
    int  buttonPadding      = 24;
    int  playerTab          = 0;
    int  inputIndex         = 0;
    bool cfgInit = false;
    
    class cAimbot
    {
    public:
        
        bool enabled     = true;         // Enable
        
        bool LegitEnabled = false;
        bool legitHitscan = false;
        float legitFOV = 0.f;
        bool smooth        = false;
        float smoothf    = 1.f;
        bool LegitRCS = false;
        float LegitRCSx = 0.f;
        float LegitRCSy = 0.f;
        int legitHitscanType = 0;
        
        bool autoknife     = false;         // Enable
        bool autostop     = false;         // Enable
        bool prediction        = false;
        int baimxhp     = 0;         // Enable
        bool baimhp     = false;         // Enable
        int jitter     = 0;
        bool freestand = false;
        bool slowalk = false;
        bool silent      = true;         // Silent Aim ob
        int  FovToPlayer = 180;          // Aimbot Fov
        int  hitbox      = 0;            // Hitbox
        int  pointscale  = 80;           // Pointscale
        bool trigger     = false;        // Will shoot when an enemy is in your crosshair
        //bool prediction  = true;         // Player prediction
        bool autowall    = true;         // Shoots through walls if calulated damage is higher than set amount
        int  mindmg      = 5;            // Autowall min damage
        bool hitchance  = true;         // Hitchance
        int accuracyhithcance = 0;     // Hitchance Accuacry
        bool hitscan    = true;         // Hitscan
        int hitscantype = 0;            // HItscan Types
        int legitaatype = 0;            // HItscan Types
        bool autoshoot  = false;        // Shoots for you
        bool autoscope  = true;         // Autoscope
        //bool autostop   = false;        // auto stop
        bool autopistol = true;         // Pistol is like AK
        bool autocock   = true;        // Auto Revovler
        bool autocrouch = false;        // Crouch when something is in fov
        //bool autozeus   = false;         // Zeus when something is close enough
        bool rcs        = false;        // Recoil control system
        int rcsf        = 0;            // Recoil control
        bool Yawresolver= false;        // Resolver
        int yresolve    = 0;            // different resolver
        bool fakewalk   = true;        // Fake Walk
        int fakewalktype = 0;         // Fakewalk types
        bool backtrack = false;
        bool autoslow = false;
        
        bool freestanding = false;
        
        
    }aimbot;
    
    class cVisuals
    {
    public:
        
        bool enabled    = true;        // Enable
        bool enemyonly  = true;        // Enemy only
        bool visonly    = false;       // Visual only
        bool bullett    = false;       // Visual only
        bool box        = false;       // Box ESP
        bool name       = true;        // Name ESP
        bool health     = true;        // Health Bar
        bool healthtext = true;        // Health Text
        bool armour     = false;       // Armour Bar
        bool skeleton   = true;        // Skeleton ESP
        bool snapline   = false;       // Snaplines obv
        bool rcrosshair = true;       // Recoil Crosshair (Shows but doesn't move)
        bool scrosshair = false;       // Sniper Crosshair
        bool defusing   = true;        // Defusing ESP
        bool noscopeaugsg   = true;        // Defusing ESP
        bool rescuing   = false;       // Hostage rescue and carrying esp
        bool scoped     = true;        // Scoped ESP
        bool weapons    = false;       // Dropped Weapons
        bool bombtimer  = true;        // Bomb Timer
        bool skinc      = true;        // SkinChanger
        bool nosmoke    = false;        // No Smoke
        bool antiaim_indicator= true;  // Manual AA idicator
        int indicatorAA_types = 2;     // antiaim idicator
        bool anglelinenames = false;     // antiaim idicator
        bool aaline = false;     // antiaim idicator
        bool antiaiminfos= true;       // AntiAim Lines
        bool direction = false;         // Enemy Direction
        bool hitmarker  = true;        // Aimware Hitmarkers
        bool inverseragdoll  = false;        // Aimware Hitmarkers
        bool antiafkkick  = false;        // Aimware Hitmarkers
        bool hitmarkersounds  = true;        // Aimware Hitmarkers
        bool allieshit  = true;        // Aimware Hitmarkers
        bool enemyhit  = true;        // Aimware Hitmarkers
        int hitinnergap = 5;     // antiaim idicator
        int hitsize = 16;     // antiaim idicator
        int hitduration = 2000;
        bool spreadcircle = true;
        bool grenade = true;
        bool active    = true;
        float edge_distance = 25.f;
        bool edge    = false;
        
        
        
        
        // Chams
        bool chams      = true;         // Player Chams
        bool localchams = false;         // Player Chams
        bool handchams  = false;        // Handchams obv
        bool weaponchams= false;        // Weapon chams obv
        bool fakelagchams= false;        // Weapon chams obv
        int weaponType  = 1;            // Weapon Type 0 - Lit 1 - Texture 2 - Wireframe
        int handsType   = 1;            // Hand   Type 0 - Lit 1 - Texture 2 - Wireframe
        int playersType = 1;            // Player Type 0 - Lit 1 - Texture
        int fakelagtype = 1;            // Player Type 0 - Lit 1 - Texture
        int localchamstype = 1;            // Player Type 0 -
        int tptype = 1;
        
        int weaponchams_alpha   = 255;  // Weapon Chams Alpha / opacity
        int handchams_alpha     = 255;  // Hand   Chams Alpha / opacity
        int playerchams_alpha   = 255;  // Player Chams Alpha / opacity
        int localchams_alpha   = 255;  // Player Chams Alpha / opacity
        int fakelagchams_alpha   = 255;  // Player Chams Alpha / opacity
        
    }visuals;
    
    class cMisc
    {
    public:
        
        bool enabled        = true;     // Enabled
        bool transparent        = true;     // Enabled
        bool snipercrosshair        = false;     // Enabled
        bool antiuntrust    = true;     // Anti Untrust KEEP ON AT ALL TIMES UNLESS YOU KNOW WHAT YOURE DOING
        bool radar    = false;
        bool noduckcooldown    = false;
        bool spreadcrosshair    = false;
        bool dlights        = false;
        bool unload        = false;
        
        float AAAngle;
        int Up = 1;
        int Down = 1;
        int Left = 1;
        int Right = 1;
        
        bool showenemieslog = false;
        bool showallieslog = false;
        bool dlight = false;
        bool dlightenemy = false;
        bool dlightallies = false;
        float loggerduration = 3000.f;
        float dlightradius = 500.0f;
        float loggerlines = 10;
        bool showlocalplayer = false;
        
        bool norecoil       = true;
        bool scopeonly       = true;
        bool thirdperson    = false;     // Basically RCS without slider
         bool manualcrosshair    = false;     // Basically RCS without slider
        bool legitaa    = false;     // Basically RCS without slider
        bool manualaa    = false;     // Basically RCS without slider
        bool novisual       = true;     // No visual recoil ofc
        bool bhop           = true;     // BunnyHop
        bool autostrafe     = true;     // Strafes for you ofc
        bool cstrafe        = false;    // Circle strafes
        bool airstuck       = false;    // Airstuck
        bool fovt           = true;    // Fov Changer Enabled
        int fov             = 20;       // FOV changer
        bool watermark      = false;
        bool backtrack = false;
        bool moonwalk = false;
        float tpoffset = 64.f;
        bool freestanding           = false;
        
        bool lbybreaker           = false;
        bool lbybreakermanual           = false;
        float lbybreakeroffset = 180.0f;
        
        // Different Clantags
        bool clantag         = false;    // Enables clantag
        
        bool showrank       = true;     // Show everyboys rank in MM
        bool spammer        = false;    // Chat spammer
        bool fullbright        = false;    // Chat spammer
        bool noflash        = true;     // Disabled flashbangs
        int flashalpha      = 255.f;    // How "flashed" you are
        bool noscope        = false;     // Noscope
        
        bool fakelag        = false;    // Fake lag enable (WIP)
        bool flagchams        = false;    // Fake lag enable (WIP)
         bool scopechamshh        = false;    // Fake lag enable (WIP)
        int fakelagfactor   = 0;        // Fake Lag (WIP)
        bool adaptive       = false;
        bool fakeping        = false;    // Fake lag enable (WIP)
        int fakepingtype   = 0;        // Fake Lag (WIP)  //
        int fakepingvalue   = 0;        // Fake Lag (WIP)  //
        
        
        bool nightmode      = false;    // Night Mode
         bool grenadepred      = false;    // Night Mode
        bool desynchams      = false;    // Night Mode
        bool asuswalls      = false;    // asuswalls - see through walls
        bool worldpaint     = false;    // World Paint
        bool changesky      = false;    // Changes Sky
        bool antiscreenshot = false;    // Anti screenshot
        bool showspectators = false;    // Spectator List
        
        // AntiAim
        bool antiaim        = false;    // Anti aims / "spinbot"
        //bool legitaa        = false;
        bool thirdpersonmode= false;    // Thirdperson
        bool attargets      = true;     // AtTargets ofc
        bool fakeaa         = false;    // Fake anti aim
        int delta           = 115;      // LBY Delta
        int aaY             = 0;        // Yaw AntiAim
        int aaX             = 0;        // Pitch AntiAim
        int FaaY            = 0;        // Yaw Fake anti aim (Thnx Ziwiiz)
        int MaaY            = 0;        // Y Moving anti aim
        int AaaY            = 0;        // Air  Yaw Moving antiaim
        int Yoffset         = 0;        // Yaw Offset
        int FYoffset        = 0;        // Fake Yaw Offset
        bool antiResolverFlip= false;
        bool resolverfucker= false;
        bool turbojizzer = false;
        bool backjizzer = false;//lby flip
        bool lby_spin = false;
        bool tank = false;
        float asusalpha      = .0;
        
    }misc;
    
    class cColors
    {
    public:
        
        int combo   = 0;
        int fakelag_r = 0;
        int fakelag_g = 0;
        int fakelag_b = 0;
        int fakelag_a = 0;
        
        Color ctchams;
        Color fakealgchams;
        Color scopedchams;
        Color tchams;
        Color dlight;
        Color fakelag;
        Color grenadepred;
        Color localchams;
        Color ctchams_ign;
        Color tchams_ign;
        
        Color tbox;
        Color tbox_ign;
        
        Color ctbox;
        Color ctbox_ign;
        
        Color hands;
        Color weapon;
        
        Color scope;
        Color sky;
        Color world;
        //Color hitmarkers;
        
        Color asus = Color(255, 255, 255, 150);
        
    }colors;
    class cLegit
    {
        bool enabled        = false;
        
        bool flash_check    = false;
        
        int fov             = 0;
        
        bool backtrack      = false;
        
        bool  smoothing     = false;
        int   smooth_factor = 0.f;
        
        bool  recoil_control= false;
        int   rcs_factor    = 0.f;
    }legit;
};

struct Corrections
{
    float x, y;
    bool whitelist;
    bool resolved;
    bool baim;
    
    int dropdown_x = 0;
    int dropdown_y = 0;
};


extern cVariables vars;
extern Corrections gCorrections[64];
