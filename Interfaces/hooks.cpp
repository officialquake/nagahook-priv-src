#include "main.h"
#include "skinchanger.h"
#include "index.h"
#include "../EventListener.h"
EventListener* eventlistener = nullptr;
bool* bSendPacket = nullptr;
int* nPredictionRandomSeed  = nullptr;

void InitializeInterfaces()
{
    pSurface        = GetInterface<ISurface>("./bin/osx64/vguimatsurface.dylib", "VGUI_Surface");
    pPanel          = GetInterface<IPanel>("./bin/osx64/vgui2.dylib", "VGUI_Panel");
    pEffects        = GetInterface<CEffects>("./bin/osx64/engine.dylib", "VEngineEffects"); 
    pCvar           = GetInterface<ICvar>("./bin/osx64/materialsystem.dylib", "VEngineCvar");
    pClient         = GetInterface<IBaseClientDLL>("./csgo/bin/osx64/client_panorama.dylib", "VClient");
    pEngine         = GetInterface<IEngineClient>("./bin/osx64/engine.dylib", "VEngineClient");
    pEntList        = GetInterface<IClientEntityList>("./csgo/bin/osx64/client_panorama.dylib", "VClientEntityList");
    pOverlay        = GetInterface<IVDebugOverlay>("./bin/osx64/engine.dylib", "VDebugOverlay004", true);
    pEngineTrace    = GetInterface<IEngineTrace>("./bin/osx64/engine.dylib", "EngineTraceClient");
    pModelInfo      = GetInterface<IVModelInfo>("./bin/osx64/engine.dylib", "VModelInfoClient");
    pInputSystem    = GetInterface<IInputSystem>("./bin/osx64/inputsystem.dylib", "InputSystemVersion");
    pModelRender    = GetInterface<IVModelRender>("./bin/osx64/engine.dylib", "VEngineModel");
    pMatSystem      = GetInterface<IMaterialSystem>("./bin/osx64/materialsystem.dylib", "VMaterialSystem");
    pPrediction     = GetInterface<IPrediction>("./csgo/bin/osx64/client_panorama.dylib", "VClientPrediction");
    pEngineGUI      = GetInterface<IEngineVGui>("./bin/osx64/engine.dylib", "VEngineVGui");
   // sound           = GetInterface<IEngineSound>("./bin/osx64/engine.dylib", "IEngineSoundClient");
    pGameMovement   = GetInterface<IGameMovement>("./csgo/bin/osx64/client_panorama.dylib", "GameMovement");
    //fileSystem      = GetInterface<IFileSystem>("./bin/osx64/filesystem_stdio.dylib", "VFileSytem");
    //glowManager     = GetInterface<CGlowObjectManager>("<#const char *filename#>", "<#const char *version#>")
    pPhysics        = GetInterface<IPhysicsSurfaceProps>("./bin/osx64/vphysics.dylib", "VPhysicsSurfaceProps");
    pGameEventManager = GetInterface<IGameEventManager2>("./bin/osx64/engine.dylib", "GAMEEVENTSMANAGER002", true);
    eventlistener = new EventListener({ "cs_game_disconnected", "player_connect_full", "player_death", "player_hurt", "bullet_impact", "round_start", "round_end", "weapon_fire", "switch_team", "player_death", "item_purchase", "item_remove", "item_pickup", "bomb_begindefuse", "enter_bombzone", "bomb_beginplant" });
    
    
}

void ProtectAddr(void* addr, int prot)
{
    long pagesize = sysconf(_SC_PAGESIZE);
    void* address = (void *)((long)(uintptr_t)addr & ~(pagesize - 1));
    mprotect(address, sizeof(address), prot);
}

void InitializeVMTs()
{
    uintptr_t findClientMode = CPatternScanner::Instance()->GetPointer("client_panorama.dylib",(unsigned char*)CLIENTMODE_SIG, CLIENTMODE_MASK, 0xA) + 0x4;
    uintptr_t findGlobalVars = CPatternScanner::Instance()->GetPointer("client_panorama.dylib", (unsigned char*)GLOBALS_SIG, GLOBALS_MASK, 0x3) + 0x4;
   // uintptr_t viewrenderPtr = CPatternScanner::Instance()->GetProcedure("client_panorama.dylib", (unsigned char*)VIEWRENDER_SIG, VIEWREDNER_MASK);
    uintptr_t findRankReveal = CPatternScanner::Instance()->GetPointer("client_panorama.dylib",(unsigned char*)RANKREVEAL_SIG, RANKREVEAL_MASK, 0x15) + 0x4;
    uintptr_t findClanTag    = CPatternScanner::Instance()->GetPointer("engine.dylib", (unsigned char*) CLANTAG_SIG, CLANTAG_MASK, 0xB) + 0x4;
    uintptr_t sendPacketPtr =  CPatternScanner::Instance()->GetProcedure("engine.dylib", (unsigned char*)SENDPACKET_SIG, SENDPACKET_MASK, 0x1) + 0x2;
    uint64_t findMoveData = CPatternScanner::Instance()->GetPointer("client_panorama.dylib", (unsigned char*)"\x48\x8D\x05\x00\x00\x00\x00\x48\x8B\x00\x0F\x57\xC0\x0F\x2E\x40\x00\x73\x00", "xxx????xxxxxxxxx?x?", 0x3) + 0x4;
    uintptr_t predictionSeedPointer = CPatternScanner::Instance()->GetPointer("client_panorama.dylib", (unsigned char*)"\x48\x8D\x0D\x00\x00\x00\x00\x89\x01\x5D\xC3", "xxx????xxxx", 0x3) + 0x4;

    
    bSendPacket = reinterpret_cast<bool*>(sendPacketPtr);
    ProtectAddr(bSendPacket, PROT_READ | PROT_WRITE | PROT_EXEC);
    pInput = *reinterpret_cast<CInput**>(GetAbsoluteAddress(getvfunc<uintptr_t>(pClient, 16) + 4, 3, 7));
    //glowManager = reinterpret_cast<GlowObjectManagerFn>(CPatternScanner::Instance()->GetProcedure("client_panorama.dylib", (unsigned char*)"\xE8\x00\x00\x00\x00\xC7\x40\x00\x00\x00\x00\x00\x48\x8D\x3D\x00\x00\x00\x00\xBE", "x????xx????xxxx????x", 0))();
    
    void* handle = dlopen("./csgo/bin/osx64/client_panorama.dylib", RTLD_NOLOAD | RTLD_NOW);
    RandomInt       = reinterpret_cast<RandomIntFn>(dlsym(handle, "RandomInt"));
    RandomSeed      = reinterpret_cast<RandomSeedFn>(dlsym(handle, "RandomSeed"));
    dlclose(handle);
    
    SetClanTag  = reinterpret_cast<SendClanTagFn>(findClanTag);
    pClientMode = reinterpret_cast<IClientMode*>(findClientMode);
    pGlobals    = *reinterpret_cast<CGlobalVarsBase**>(findGlobalVars);
    nPredictionRandomSeed = reinterpret_cast<int*>(predictionSeedPointer);
    MoveData = *reinterpret_cast<CMoveData**>(findMoveData);
    MsgFunc_ServerRankRevealAll = reinterpret_cast<MsgFunc_ServerRankRevealAllFn>(findRankReveal);

    paintVMT        = new VMT(pPanel);
    createmoveVMT   = new VMT(pClientMode);
    clientVMT       = new VMT(pClient);
    modelVMT        = new VMT(pModelRender);
    predVMT         = new VMT(pPrediction);
    game_event_vmt  = new VMT(pGameEventManager);
    //soundVMT        = new VMT(sound);
    //viewRenderVMT   = new VMT(viewRender);
    
}

uintptr_t hooker::FindPlayerAnimStateOffset()
{
    static uintptr_t animstateoffset;
    if(!animstateoffset)
    {
        animstateoffset = *reinterpret_cast<uint32_t*>(CPatternScanner::Instance()->GetProcedure("client_panorama.dylib", (unsigned char*)"\x48\x8B\xBB\x00\x00\x00\x00\x48\x85\xFF\x74\x41\xE8\x00\x00\x00\x00\x4C", "xxx????xxxxxx????x", 0) +3);
    }else{
    }
    return animstateoffset;
}


void InitializeHooks()
{
    
    paintVMT->HookVM((void*)hkPaintTraverse, 42);
    paintVMT->ApplyVMT();
        
    createmoveVMT->HookVM((void*)hkCreateMove, 25);
    createmoveVMT->HookVM((void*)hkOverrideView, 19);
    createmoveVMT->ApplyVMT();
    
    clientVMT->HookVM((void*)hkKeyEvent, 21);
    clientVMT->HookVM((void*)hkFrameStage, FrameStageIndex);
    clientVMT->ApplyVMT();
    
    modelVMT->HookVM((void*)hkDrawModelExecute, 21);
    modelVMT->ApplyVMT();
    
    predVMT->HookVM((void*)hkRunCommand, 20);
    predVMT->ApplyVMT();

    game_event_vmt->HookVM((void*)hkFireEventClientSide, 36);
    game_event_vmt->HookVM((void*)FireEvent_hk, 9);
    game_event_vmt->ApplyVMT();
    
    //viewRenderVMT->HookVM((void*)RenderView, 6);
    //viewRenderVMT->ApplyVMT();
    
    g_pSequence = (RecvVarProxyFn)NetVarManager::HookProp("DT_BaseViewModel", "m_nSequence", HSequenceProxyFn);
}


void UpdateResolver()
{
    OldProxy_Y = (RecvVarProxyFn)NetVarManager::HookProp("DT_CSPlayer", "m_angEyeAngles[1]", FixYaw);
}

void PrintInfo()
{
    pCvar->ConsoleColorPrintf(Color::White(), "[D E A D] Injected successfully!\n");
    pCvar->ConsoleColorPrintf(Color::Red(), "Credits to: \n");
    pCvar->ConsoleColorPrintf(Color::Green(), "Syn/-X making breathless\n");
    pCvar->ConsoleColorPrintf(Color::Yellow(), "ViKiNG making barbossa\n");
    pCvar->ConsoleColorPrintf(Color::Blue(), "Akalisch (netvarmanager/patternscanner)\n");
    pCvar->ConsoleColorPrintf(Color::Purple(), "Warlauke (barbossa)\n");
    pCvar->ConsoleColorPrintf(Color::Avoz(), "Tim (idk he's a fat fuck)\n");
}

