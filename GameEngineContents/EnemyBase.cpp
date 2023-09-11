#include "PreCompileHeader.h"
#include "EnemyBase.h"
#include "Player.h"

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
