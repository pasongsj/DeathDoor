#include "PreCompileHeader.h"
#include "PlayerAttackTrail.h"
#include "PlayerAttackDefinition.h"

PlayerAttackTrail::PlayerAttackTrail() 
{
}

PlayerAttackTrail::~PlayerAttackTrail() 
{
}

void PlayerAttackTrail::Update(float _DeltaTime)
{
	if (nullptr == TrailRenderer)
	{
		return;
	}
	if (GetLiveTime() > EraseTime)
	{
		Death();
		return;
	}
}

void PlayerAttackTrail::CreateTrail(float4 _Dir,float4 _Pos, bool IsBasic)
{
	TrailRenderer = CreateComponent< ContentFBXRenderer>();
	GetTransform()->SetLocalScale(PLAYER_TRAIL_SCALE);
	if (true == IsBasic)
	{
		TrailRenderer->SetFBXMesh("Player_Slash_Light.fbx", "ContentMeshDeffered");
		GetTransform()->SetLocalPosition(_Pos + _Dir * PLAYER_TRAIL_MOVE_LIGHT);
	}
	else
	{
		TrailRenderer->SetFBXMesh("Player_Slash_Heavy.fbx", "ContentMeshDeffered");
		GetTransform()->SetLocalPosition(_Pos + _Dir * PLAYER_TRAIL_MOVE_HEAVY);
	}
	TrailRenderer->GetTransform()->SetLocalRotation(PLAYER_TRAIL_DIR);

	float4 CalRot = float4::ZERO;
	CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, _Dir);
	GetTransform()->SetLocalRotation(-CalRot);
	EraseTime = GetLiveTime() + PLAYER_TRAIL_TIMER;
}
