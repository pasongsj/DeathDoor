#include "PrecompileHeader.h"
#include "Mushroom.h"
#include <GameEngineCore/GameEngineFBXAnimation.h>

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

Mushroom::Mushroom() 
{
}

Mushroom::~Mushroom() 
{
}

void Mushroom::Start()
{
	TriggerBase::Start();
	InitAnimation();
	InitComponent();
	SetFSMFUNC();
	SetNextState(TriggerState::PROGRESS);
}

void Mushroom::Update(float _DeltaTime)
{
	TriggerBase::Update(_DeltaTime);
}

void Mushroom::InitComponent()
{
	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL,true);
	m_pPhysXComponent->SetTrigger();
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::LeverTrigger);
	//m_pPhysXComponent->SetPositionSetFromParentFlag(true);
}

void Mushroom::InitAnimation()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("Mushroom.FBX", "ContentMeshDeffered");
}

void Mushroom::SetFSMFUNC()
{
	SetChangeFSMCallBack([this]
		{
			//StateDuration = 0.0f;
			//StateChecker = false;
		});

	SetFSM(TriggerState::OFF,
		[this]
		{
			m_pRenderer->Off();
		},
		[this](float Delta)
		{
			if (GetStateDuration()>5.f)
			{
				SetNextState(TriggerState::ON);
			}
		},
		[this]
		{
		}
	);

	SetFSM(TriggerState::PROGRESS,
		[this]
		{

		},
		[this](float Delta)
		{
			if (true == IsHit())
			{
				SetNextState(TriggerState::OFF);
			};
		},
		[this]
		{
			//Player에게 마나 1칸 채워주기;
		}
	);

	SetFSM(TriggerState::ON,
		[this]
		{
			m_pRenderer->On();
		},
		[this](float Delta)
		{
			SetNextState(TriggerState::PROGRESS);
		},
		[this]
		{
		}
	);
}
