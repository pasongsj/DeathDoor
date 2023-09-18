#include "PreCompileHeader.h"
#include "EnemyBase.h"
#include "Player.h"
#include "PhysXCapsuleComponent.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Start()
{
	InitAniamtion();
}

void EnemyBase::Update(float _DetltaTime)
{
}

bool EnemyBase::InRangePlayer(float _Range)
{
	if (nullptr == Player::MainPlayer)
	{
		return false;
	}

	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	PlayerPos.y = 0;
	float4 EnemyPos = GetTransform()->GetWorldPosition();
	EnemyPos.y = 0;
	if ((PlayerPos - EnemyPos).Size() < _Range)
	{
		return true;
	}
	return false;
}

float4 EnemyBase::GetPlayerDir()
{
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	PlayerPos.y = 0;
	float4 EnemyPos = GetTransform()->GetWorldPosition();
	EnemyPos.y = 0;

	return (PlayerPos - EnemyPos).NormalizeReturn();
}


float4 EnemyBase::AggroDir(std::shared_ptr< PhysXCapsuleComponent> _Comp, float4 DefaultDir)
{
	float4 PlayerDir = GetPlayerDir();
	DefaultDir.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, PlayerDir);
	_Comp->SetRotation( -DefaultDir);
	return PlayerDir;
}
