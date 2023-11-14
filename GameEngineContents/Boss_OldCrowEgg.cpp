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

	Renderer->SetColor(float4::BLACK, 0.9f);

	PentagramPivot = GetLevel()->CreateActor<GameEngineActor>();

	PentagramPivot->GetTransform()->SetWorldScale(float4::ZERO);

	PentagramRenderer1 = PentagramPivot->CreateComponent<GameEngineSpriteRenderer>();
	PentagramRenderer1->GetUnit()->SetMaterial("Content2DTexture", RenderPath::Alpha);

	PentagramRenderer1->SetScaleToTexture("pentagram.png");
	PentagramRenderer1->GetTransform()->AddLocalPosition(float4{ 0, 5, 0 });
	PentagramRenderer1->GetTransform()->SetLocalScale(PentagramRenderer1->GetTransform()->GetLocalScale() * 0.4f);

	PentagramRenderer2 = PentagramPivot->CreateComponent<GameEngineSpriteRenderer>();
	PentagramRenderer2->GetUnit()->SetMaterial("Content2DTexture", RenderPath::Alpha);

	PentagramRenderer2->SetScaleToTexture("pentagram.png");
	PentagramRenderer2->GetTransform()->SetLocalScale(PentagramRenderer1->GetTransform()->GetLocalScale() * 2.0f );

	GetTransform()->SetLocalScale(float4::ONE * 100.0f);
	
	PentagramScale = 0.0f;
	PentagramPivot->GetTransform()->SetWorldScale(float4::ONE * PentagramScale);

	if (m_pSphereComp == nullptr)
	{
		m_pSphereComp = CreateComponent<PhysXSphereComponent>();

		m_pSphereComp->SetPhysxMaterial(1.0f, 1.0f, 0.0f);
		m_pSphereComp->CreatePhysXActors(float4{ 0.0f, 30.0f, 30.0f });
		m_pSphereComp->TurnOffGravity();

		m_pSphereComp->CreateSubShape(SubShapeType::SPHERE, float4{ 0, 500, 500 }, float4{ 0, 0, 0 });
		m_pSphereComp->SetSubShapeFilter(PhysXFilterGroup::CrowDebuff);
	}
}


void Boss_OldCrowEgg::Update(float _DeltaTime)
{
	if (GetLiveTime() > 11.0f)
	{
		PentagramPivot->Death();
		Death();

		return;
	}

	if (GetLiveTime() > 10.0f)
	{
		if (IsEnd == false)
		{
			IsEnd = true;
			ScaleValue = -1;
			m_pSphereComp->DetachShape();
		}
	}

	if (false == IsGround)
	{
		float4 CollPoint = float4::ZERO;
		float4 CurrentPos = GetTransform()->GetWorldPosition();

		if (CurrentPos.y <= 30.0f)
		{
			PentagramPivot->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
			PentagramPivot->GetTransform()->SetWorldRotation(float4{ 90, 0, 0 });

			m_pSphereComp->SetWorldPosWithParent(float4{ CurrentPos.x, 30.0f, CurrentPos.z });

			m_pSphereComp->AttachShape();

			GameEngineSound::Play("OldCrow_Egg_Land.mp3");
			GameEngineSound::Play("OldCrow_Egg_MagicSFX.mp3");

			IsGround = true;
			return;
		}

		Dir.y -= 1.5f * _DeltaTime;

		m_pSphereComp->SetMoveSpeed(Dir.NormalizeReturn() * 1500.0f);
	}
	else
	{

		m_pSphereComp->SetMoveSpeed(float4::ZERO);
		SetPentagramEffect(_DeltaTime);
	}



}

void Boss_OldCrowEgg::SetCrowEgg(float4 _Pos, float4 _Rot, float4 _Dir)
{
	m_pSphereComp->SetWorldPosWithParent(_Pos, _Rot);

	Dir = _Dir.NormalizeReturn();
}

void Boss_OldCrowEgg::SetPentagramEffect(float _DeltaTime)
{
	PentagramScale += _DeltaTime * ScaleValue;

	if (PentagramScale > 1.0f)
	{
		PentagramScale = 1.0f;
	}
	
	if (PentagramScale < 0.0f)
	{
		PentagramScale = 0.0f;
	}

	PentagramPivot->GetTransform()->SetWorldScale(float4::ONE * PentagramScale);

	float RotationSpeed = 10.0f;

	PentagramRenderer1->GetTransform()->AddLocalRotation(float4{0, 0,_DeltaTime * RotationSpeed });
	PentagramRenderer2->GetTransform()->AddLocalRotation(float4{ 0, 0, - _DeltaTime * RotationSpeed });
}