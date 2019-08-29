#include "main.h"

// CLEAN CODE > ALL
//CGlowObjectManager* glowManager = nullptr;
ISurface*           pSurface        = nullptr;
CEffects*           pEffects        = nullptr;
IPanel*             pPanel          = nullptr;
ICvar*              pCvar           = nullptr;
IBaseClientDLL*     pClient         = nullptr;
IClientEntityList*  pEntList        = nullptr;
IVDebugOverlay*     pOverlay        = nullptr;
IEngineClient*      pEngine         = nullptr;
IMaterialSystem*    material = nullptr;
IVModelInfo*        pModelInfo      = nullptr;
IEngineTrace*       pEngineTrace    = nullptr;
IClientMode*        pClientMode     = nullptr;
CGlobalVarsBase*    pGlobals        = nullptr;
IInputSystem*       pInputSystem    = nullptr;
CInput*             pInput          = nullptr;
IMaterialSystem*    pMatSystem      = nullptr;
IEngineVGui*        pEngineGUI = nullptr;
IVModelRender*      pModelRender    = nullptr;
IPrediction*        pPrediction     = nullptr;
IMoveHelper*        pMoveHelper     = nullptr;
IGameMovement*      pGameMovement   = nullptr;
//IFileSystem* fileSystem = nullptr;
IPhysicsSurfaceProps* pPhysics      = nullptr;
IGameEventManager2* pGameEventManager = nullptr;
IEngineSound* sound = nullptr;
INetChannelInfo*    nci             = nullptr;

CMoveData* MoveData         = nullptr;


RandomSeedFn        RandomSeed;
SendClanTagFn       SetClanTag;
RandomIntFn         RandomInt;

MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;


VMT* paintVMT;
VMT* soundVMT;
VMT* createmoveVMT;
VMT* clientVMT;
VMT* modelVMT;
VMT* predVMT;
VMT* materialVMT;
VMT* game_event_vmt;
//VMT* gameVMT;

RecvVarProxyFn g_pSequence = nullptr;


