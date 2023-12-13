#include "PreCompileHeader.h"
#include "HealthPlant.h"
#include "PhysXBoxComponent.h"
#include "Player.h"

HealthPlant::HealthPlant()
{
}

HealthPlant::~HealthPlant()
{
}

void HealthPlant::Start()
{
	TriggerBase::Start();
	InitAnimation();
	InitComponent();
	SetFSMFUNC();
}

void HealthPlant::Update(float _DeltaTime)
{
	TriggerBase::Update(_DeltaTime);
}

void HealthPlant::InitComponent()
{
	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale *= 100.0f;

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);

	MeshScale.y = 10.f;
	m_pPhysXComponent->CreateSubShape(SubShapeType::BOX, MeshScale * 3.f, float4(0, 50, 0));
	m_pPhysXComponent->SetSubShapeFilter(PhysXFilterGroup::LeverTrigger);
	m_pPhysXComponent->AttachShape();
}

void HealthPlant::InitAnimation()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("Health_Plant_MESH.FBX", "ContentAniMeshDeffered");
	m_pRenderer->CreateFBXAnimation("IDLE", "Health_Plant_Idle.fbx", { 1.0f / 30, true });
	//m_pRenderer->CreateFBXAnimation("0", "Health_Plant_Growing.fbx", { 0.1f });
	m_pRenderer->CreateFBXAnimation("RELEASE", "Health_Plant_Release.fbx", { 1.0f / 30, false });
	//m_pRenderer->CreateFBXAnimation("3", "Health_Plant_UnGrown.fbx", { 0.1f });
	m_pRenderer->ChangeAnimation("IDLE");
	m_pRenderer->GetTransform()->SetLocalScale(float4::ONE * 150.0f);
	m_pRenderer->SetUnitColor(0, 0, float4::WHITE, 20.0f);
}

void HealthPlant::SetFSMFUNC()
{
	SetChangeFSMCallBack([this]
		{
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
			m_pRenderer->ChangeAnimation("RELEASE");
			m_sData.Type = InteractionData::InteractionDataType::Plant;
			Player::MainPlayer->GetInteractionData(m_sData);
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
			if (nullptr != m_TriggerFunc)
			{
				m_TriggerFunc();
			}
		}
	);

	SetFSM(TriggerState::ON,
		[this]
		{
		},
		[this](float Delta)
		{
			return;
		},
		[this]
		{
		}
	);
}
