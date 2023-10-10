#include "PreCompileHeader.h"

#include "Boss_OldCrowChain.h"

Boss_OldCrowChain::Boss_OldCrowChain() 
{
}

Boss_OldCrowChain::~Boss_OldCrowChain() 
{
}

void Boss_OldCrowChain::Start()
{
	ChainRenderer = CreateComponent<GameEngineSpriteRenderer>();

	ChainRenderer->SetScaleToTexture("CrowBossChain.png");

	float4 Scale = ChainRenderer->GetTransform()->GetLocalScale();

	ChainRenderer->GetTransform()->SetLocalScale(Scale / 5.0f);
	ChainRenderer->GetTransform()->SetLocalRotation(float4(90, 90, 0));

	ChainRenderer->Off();
	IsOn = false;
}

void Boss_OldCrowChain::Setting(int _Num)
{
	ChainNumber = _Num;
}

void Boss_OldCrowChain::SetDefault()
{
	//GetTransform()->SetParent(GetTransform());
	ChainRenderer->Off();
	IsOn = false;
}

bool Boss_OldCrowChain::GetChainState()
{
	if (IsOn)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float4 Boss_OldCrowChain::GetRendererScale()
{
	return ChainRenderer->GetTransform()->GetLocalScale();
}

void Boss_OldCrowChain::OnRenderer()
{
	ChainRenderer->On();
	IsOn = true;
}