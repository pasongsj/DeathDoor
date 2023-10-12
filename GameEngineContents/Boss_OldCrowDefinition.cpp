#include "PreCompileHeader.h"


//Chain
#define BOSS_OLDCROW_CHAINPIVOTCOUNT 4   //체인 피봇의 개수
#define BOSS_OLDCROW_USINGCHAINCOUNT 4   //사용 중인 체인을 확인할 묶음 벡터의 개수

#define BOSS_OLDCROW_MEGADASHPATTERNEND 1.75f  //메가 대쉬 패턴 끝나는 시간
#define BOSS_OLDCROW_CHAINCOUNT 200            //미리 만들 오브젝트풀 체인 개수
#define BOSS_OLDCROW_CREATECHAINTIME 1.2f      //패턴 내 체인 생성하는 시간

#define BOSS_OLDCROW_CHAINSPEED 150.0f   //체인 속도

//Dash
#define BOSS_OLDCROW_DASHSPEED 1000.0f
#define BOSS_OLDCROW_DASHSPEED2 BOSS_OLDCROW_DASHSPEED * 0.75f
#define BOSS_OLDCROW_MEGADASHSPEED 5000.0f