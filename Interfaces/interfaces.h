#pragma once

namespace Global
{
    extern bool*                send_packet;
    extern array<QAngle, 2>     angles;
    extern CUserCmd*            cmd;
    extern C_BasePlayer*        local;
    extern C_BaseCombatWeapon*  weapon;
    extern float fake_angle;
    extern float real_angle;
    extern Vector fake_ang1e;
    extern Vector real_ang1e;
    extern Vector GFakeAngle;
    extern Vector GRealAngle;
}
namespace AntiAem{
    extern Vector GFakeAngle;
    extern Vector GRealAngle;
    extern Vector GRealAngle1;
    extern Vector realangle;
    extern Vector fakeangle;
}

extern ISurface*            pSurface;
extern CEffects*            pEffects;
extern IPanel*              pPanel;
extern ICvar*               pCvar;
extern IBaseClientDLL*      pClient;
extern IEngineSound* sound;
extern IClientEntityList*   pEntList;
extern IEngineVGui*         pEngineGUI;
//extern IFileSystem* fileSystem;
extern IEngineClient*       pEngine;
extern IVModelInfo*         pModelInfo;
extern IEngineTrace*        pEngineTrace;
extern IClientMode*         pClientMode;
extern CGlobalVarsBase*     pGlobals;
//extern CViewRender*         viewRender;
extern IInputSystem*        pInputSystem;
extern CInput*              pInput;
extern IMaterialSystem*     pMatSystem;
extern IVModelRender*       pModelRender;
extern IPrediction*         pPrediction;
extern IGameMovement*       pGameMovement;
extern IMoveHelper*         pMoveHelper;
extern IPhysicsSurfaceProps*pPhysics;
extern CGlowObjectManager* glowManager;
extern RandomSeedFn         RandomSeed;
extern RandomIntFn          RandomInt;
extern SendClanTagFn        SetClanTag;
extern MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;
extern IGameEventManager2* pGameEventManager;
extern INetChannelInfo*     nci;


extern VMT* paintVMT;
extern VMT* createmoveVMT;
extern VMT* clientVMT;
extern VMT* modelVMT;
extern VMT* predVMT;
extern VMT* materialVMT;
extern VMT* game_event_vmt;

extern VMT* gameEventsVMT;
//extern VMT* viewRenderVMT;

extern RecvVarProxyFn g_pSequence;
extern int* nPredictionRandomSeed;
extern CMoveData* MoveData;


