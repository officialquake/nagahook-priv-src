#ifndef EnginePrediction_h
#define EnginePrediction_h

#include "../main.h"

extern float m_flOldCurtime;
extern float m_flOldFrametime;

class CEnginePrediction {
public:
    CEnginePrediction();
    void Start(CUserCmd* cmd);
    void End();
private:
    static CEnginePrediction* instance;
    float m_flOldCurtime = 0.f;
    float m_flOldFrametime = 0.f;
    CMoveData m_MoveData;
    int oldPFlags;
};

#endif /* EnginePrediction_h */
