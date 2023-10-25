#include "PrecompileHeader.h"
#include "Ladder.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

Ladder::Ladder()
{
}

Ladder::~Ladder()
{
}

void Ladder::Start()
{
	TriggerBase::Start();
	InitAnimation();
	InitComponent();
	SetFSMFUNC();
}

void Ladder::Update(float _DeltaTime)
{
	TriggerBase::Update(_DeltaTime);
}

void Ladder::InitComponent()
{
	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);
	
	m_pPhysXComponent->CreateSubShape(SubShapeType::BOX, float4(100,10,100), float4(-50, 10, 0));
	m_pPhysXComponent->SetSubShapeFilter(PhysXFilterGroup::LeverTrigger);
	m_pPhysXComponent->AttachShape();
}

void Ladder::InitAnimation()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("Ladder.fbx", "ContentMeshDeffered");
}

void Ladder::SetFSMFUNC()
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
			if (true == TriggerHitCheck())
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
			if (nullptr!=m_TriggerFunc)
			{
				m_TriggerFunc();
			}
			m_pRenderer->SetGlowToUnit(0, 0, "swampPillarMask.png");

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
