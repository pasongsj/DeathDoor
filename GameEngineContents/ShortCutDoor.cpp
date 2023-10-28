#include "PrecompileHeader.h"
#include "ShortCutDoor.h"
#include "PhysXBoxComponent.h"

ShortCutDoor::ShortCutDoor() 
{
}

ShortCutDoor::~ShortCutDoor() 
{
}

void ShortCutDoor::Start()
{
	TriggerBase::Start();
	InitAnimation();
	InitComponent();
	SetFSMFUNC();
}

void ShortCutDoor::Update(float _DeltaTime)
{
	TriggerBase::Update(_DeltaTime);
}

void ShortCutDoor::InitComponent()
{
	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);

	MeshScale.y = 10.f;
	m_pPhysXComponent->CreateSubShape(SubShapeType::BOX, MeshScale * 3.f, float4(0, 50, 0));
	m_pPhysXComponent->SetSubShapeFilter(PhysXFilterGroup::LeverTrigger);
	m_pPhysXComponent->AttachShape();
}

void ShortCutDoor::InitAnimation()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->GetTransform()->SetLocalScale(float4{ 100, 100, 100 });
	m_pRenderer->SetFBXMesh("SHORTCUTDOOR_MESH.FBX", "ContentAniMeshDeffered");
	m_pRenderer->CreateFBXAnimation("DROP", "SHORTCUTDOOR_DROP.FBX", { 1.f / 30.f, false });
	m_pRenderer->CreateFBXAnimation("ROCKED", "SHORTCUTDOOR_ROCKED.FBX", { 1.f / 30.f, false });
	m_pRenderer->CreateFBXAnimation("FLOOR", "SHORTCUTDOOR_FLOOR.FBX", { 1.f / 30.f, false });
	m_pRenderer->CreateFBXAnimation("OPEN_Inward", "SHORTCUTDOOR_OPEN_INWARD.FBX", { 1.f / 30.f, false });
	m_pRenderer->CreateFBXAnimation("OPEN_STILL", "SHORTCUTDOOR_OPEN_STILL.FBX", { 1.f / 30.f, false });
	m_pRenderer->CreateFBXAnimation("CLOSE_FROM_INWARD", "SHORTCUTDOOR_CLOSE_FROM_INWARD.FBX", { 1.f / 30.f, false });
	m_pRenderer->ChangeAnimation("FLOOR"); 


}

void ShortCutDoor::SetFSMFUNC()
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
			if (true== IsPlayerInRange())
			{
				//e키 ui띄우기
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
			//문열리기
		},
		[this]
		{
		}
	);

	SetFSM(TriggerState::ON,
		[this]
		{
			//문고정
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	);
}
