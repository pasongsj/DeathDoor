#include "PreCompileHeader.h"

#include "Boss_OldCrowEgg.h"
#include "PhysXSphereComponent.h"

Boss_OldCrowEgg::Boss_OldCrowEgg() 
{
}

Boss_OldCrowEgg::~Boss_OldCrowEgg() 
{
}

void Boss_OldCrowEgg::Start()
{
	Renderer = CreateComponent<ContentFBXRenderer>();

	Renderer->SetFBXMesh("Boss_OldCrow_Egg.FBX", "ContentAniMeshDeffered");

	//PentagramRenderer1 = CreateComponent<GameEngineSpriteRenderer>();
	//PentagramRenderer1->SetScaleToTexture("pentagram.png");
	//PentagramRenderer2 = CreateComponent<GameEngineSpriteRenderer>();
	//PentagramRenderer2->SetScaleToTexture("pentagram.png");

	//float4 Scale = PentagramRenderer1->GetTransform()->GetLocalScale();

	//PentagramRenderer1->GetTransform()->SetLocalScale(Scale / 100.0f);
	//PentagramRenderer2->GetTransform()->SetLocalScale(Scale / 100.0f);

	GetTransform()->SetLocalScale(float4::ONE * 100.0f);
	
	//Angle = -90.0f;

	if (m_pSphereComp == nullptr)
	{
		m_pSphereComp = CreateComponent<PhysXSphereComponent>();

		m_pSphereComp->SetPhysxMaterial(1.0f, 1.0f, 0.0f);
		m_pSphereComp->CreatePhysXActors(float4{ 0.0f, 30.0f, 30.0f });
		m_pSphereComp->TurnOffGravity();
		//m_pSphereComp->SetFilterData(PhysXFilterGroup::CrowDebuff);
	}
}


void Boss_OldCrowEgg::Update(float _DeltaTime)
{
	if (false == IsGround)
	{
		float4 CollPoint = float4::ZERO;

		if (GetTransform()->GetWorldPosition().y <= 30.0f)
		{
			IsGround = true;
			return;
		}

		Dir.y -= 0.5f * _DeltaTime;

		m_pSphereComp->SetMoveSpeed(Dir.NormalizeReturn() * 700.0f);
	}
	else
	{
		m_pSphereComp->SetMoveSpeed(float4::ZERO);

		PentaGramScale += _DeltaTime * 10.0f;
	}
}

void Boss_OldCrowEgg::SetCrowEgg(float4 _Pos, float4 _Rot, float4 _Dir)
{
	m_pSphereComp->SetWorldPosWithParent(_Pos, _Rot);

	Dir = _Dir.NormalizeReturn();
}