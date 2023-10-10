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
	float4 Rot = float4::ZERO;
	Rot.y = float4::GetAngleVectorToVectorDeg360(PlayerDir, float4::FORWARD);
	_Comp->SetRotation( Rot - DefaultDir);
	return PlayerDir;
}

bool EnemyBase::CheckHit()
{
	//if ()// 플레이어로부터 공격을 받는다면 )
	//{
	//	
	//	return true;
	//}
	return false;
}
void EnemyBase::AddPlayerSpellCost()
{
	Player::MainPlayer->AddSpellCost();
}