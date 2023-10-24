#include "PrecompileHeader.h"
#include "Frog_Lever.h"
#include <GameEngineCore/GameEngineFBXAnimation.h>

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"


Frog_Lever::Frog_Lever()
{
}

Frog_Lever::~Frog_Lever()
{
}

void Frog_Lever::Start()
{
	TriggerBase::Start();
	InitAnimation();
	InitComponent();
	SetFSMFUNC();
}

void Frog_Lever::Update(float _DeltaTime)
{
	TriggerBase::Update(_DeltaTime);
}

void Frog_Lever::InitComponent()
{

	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale *= 100.0f;

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);

	MeshScale.y = 10.f;
	m_pPhysXComponent->CreateSubShape(SubShapeType::BOX, MeshScale* 3.f,float4(0,50,0));
	m_pPhysXComponent->SetSubShapeFilter(PhysXFilterGroup::LeverTrigger);
	m_pPhysXComponent->AttachShape();
}
void Frog_Lever::InitAnimation()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->GetTransform()->SetLocalScale(float4{ 100, 100, 100 });
	m_pRenderer->SetFBXMesh("LEVER_MESH.FBX", "ContentAniMeshDeffered");
	m_pRenderer->CreateFBXAnimation("LEVER_OPEN", "LEVER_OPEN (1).FBX", { 1.f / 30.f, false });
	m_pRenderer->ChangeAnimation("LEVER_OPEN"); // 처음엔 0으로 고정으로 쓰기로 한듯?



	m_pRenderer->SetAnimationStartFunc("LEVER_OPEN", 0, [this]
		{
			m_pRenderer->PauseOn();
		});
}

void Frog_Lever::SetFSMFUNC()
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
			if (true == TriggerKeyCheck())
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
			m_pRenderer->PauseOff();
		},
		[this](float Delta)
		{
			if (m_pRenderer->IsAnimationEnd())
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
			m_pRenderer->PauseOn();
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	);
}
