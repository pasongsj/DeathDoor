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
	ChainRenderers.reserve(BOSS_OLDCROW_INCHAINRENDERCOUNT);

	for (int i = 0; i < BOSS_OLDCROW_INCHAINRENDERCOUNT; ++i)
	{
		CreateChainRenderer();
	}
}

void Boss_OldCrowChain::CreateChainRenderer()
{
	std::shared_ptr<GameEngineSpriteRenderer> ChainRenderer = CreateComponent<GameEngineSpriteRenderer>();

	ChainRenderer->SetScaleToTexture("CrowBossChain.png");

	float4 Scale = ChainRenderer->GetTransform()->GetLocalScale();

	ChainRenderer->GetTransform()->SetLocalScale(Scale / 5.0f);
	ChainRenderer->GetTransform()->SetLocalRotation(float4(90, 90, 0));
	ChainRenderer->GetTransform()->SetLocalPosition({ 0, 10, ChainRenderers.size() * - 105.0f });

	ChainRenderer->ColorOptionValue.MulColor = float4::BLACK;

	ChainRenderer->Off();

	ChainRenderers.push_back(ChainRenderer);

}

void Boss_OldCrowChain::Update(float _DeltaTime)
{
	if (IsOn)
	{
		float Value1 = GetTransform()->GetLocalPosition().z;
		float Value2 = OnRendererNumber * 105.0f;

		if (Value1 >= Value2)
		{
			if (static_cast<int>(ChainRenderers.size()) <= OnRendererNumber)
			{
				CreateChainRenderer();
			}

			ChainRenderers[OnRendererNumber]->On();
			++OnRendererNumber;
		}
	}
}

void Boss_OldCrowChain::SetDefault()
{
	IsOn = false;

	for (int i = 0; i < ChainRenderers.size(); ++i)
	{
		ChainRenderers[i]->Off();
	}

	GetTransform()->SetLocalPosition(float4::ZERO);
	
	OnRendererNumber = 0;
}

void Boss_OldCrowChain::OnChainEffect()
{
	IsOn = true;
}