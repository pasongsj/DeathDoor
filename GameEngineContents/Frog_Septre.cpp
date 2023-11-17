#include "PrecompileHeader.h"
#include "Frog_Septre.h"

#include "PhysXCapsuleComponent.h"
#include "PhysXControllerComponent.h"
#include "ShockWave.h"
#include "Player.h"

Frog_Septre::Frog_Septre() 
{
}

Frog_Septre::~Frog_Septre() 
{
}

void Frog_Septre::Start()
{
	TriggerBase::Start();
	InitAnimation();
	InitComponent();
	SetFSMFUNC();
}

void Frog_Septre::Update(float _DeltaTime)
{
	TriggerBase::Update(_DeltaTime);
}

void Frog_Septre::InitComponent()
{
	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXCapsuleComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);

	//MeshScale.y = 1.f;
	m_pPhysXComponent->CreateSubShape(SubShapeType::SPHERE, MeshScale * 30.f, float4(0, 10, 0));
	m_pPhysXComponent->SetSubShapeFilter(PhysXFilterGroup::LeverTrigger);
	m_pPhysXComponent->AttachShape();
}

void Frog_Septre::InitAnimation()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("FrogSeptre_Static.FBX", "ContentMeshDeffered");
}

void Frog_Septre::SetFSMFUNC()
{
	SetChangeFSMCallBack([this]
		{
			//StateDuration = 0.0f;
			//StateChecker = false;
		});

	SetFSM(TriggerState::OFF,
		[this]
		{
		},
		[this](float Delta)
		{
			if (true == IsHit() && (Player::MainPlayer->GetPhysXComponent()->GetWorldPosition() - m_pPhysXComponent->GetWorldPosition()).Size()<3500.f)
			{
				SetNextState(TriggerState::PROGRESS);
			};
		},
		[this]
		{
		}
	);

	SetFSM(TriggerState::PROGRESS,
		[this]
		{
			if (nullptr != m_TriggerFunc)
			{
				m_TriggerFunc();
			}
			m_pRenderer->SetGlowToUnit(0, 0, "swampPillarMask.png");
			m_pRenderer->SetUnitDiffuseColorIntensity(0, 0, 4.0f);

			std::weak_ptr<ShockWave> Wave = CreateComponent<ShockWave>();
			Wave.lock()->GetTransform()->SetWorldRotation({ 90.0f, 0.0f, 0.0f });
			Wave.lock()->GetTransform()->SetLocalScale({ 10.0f, 10.0f, 1.0f });
		},
		[this](float Delta)
		{
			if (true)// glow켜고 이펙트 시전후 넘기기
			{
				SetNextState(TriggerState::ON);
			}
		},
		[this]
		{
		}
	);

	SetFSM(TriggerState::ON,
		[this]
		{
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	);
}
