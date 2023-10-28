#include "PrecompileHeader.h"
#include "Crate.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

Crate::Crate()
{
}

Crate::~Crate()
{
}

void Crate::Start()
{
	TriggerBase::Start();
	InitAnimation();
	InitComponent();
	SetFSMFUNC();
}

void Crate::Update(float _DeltaTime)
{
	TriggerBase::Update(_DeltaTime);
}

void Crate::InitComponent()
{
	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);

}

void Crate::InitAnimation()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer1 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer2 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer3 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("CrateWhole.fbx", "ContentMeshDeffered");
	m_pRenderer1->SetFBXMesh("CratePiece1.fbx", "ContentMeshDeffered");
	m_pRenderer2->SetFBXMesh("CratePiece2.fbx", "ContentMeshDeffered");
	m_pRenderer3->SetFBXMesh("CratePiece3.fbx", "ContentMeshDeffered");
	//m_pRenderer->Off();
	//m_pRenderer1->Off(); //x
	//m_pRenderer2->Off(); //z
	//m_pRenderer3->Off();
}

void Crate::SetFSMFUNC()
{
	SetChangeFSMCallBack([this]
		{
			//StateDuration = 0.0f;
			//StateChecker = false;
		});

	SetFSM(TriggerState::OFF,
		[this]
		{
			m_pPhysXComponent->PhysXRelease();
			isPhysXCollision = 0;
			m_pRenderer->On();
			m_pRenderer1->GetTransform()->SetLocalRotation(float4::ZERO);
			m_pRenderer2->GetTransform()->SetLocalRotation(float4::ZERO);
		}, 
		[this](float Delta)
		{
			if (true == IsHit())
			{
				SetNextState(TriggerState::PROGRESS);
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
			float fTime = Delta * 3.f;
			m_pRenderer1->GetTransform()->AddLocalRotation(float4(90* fTime,0,0)); //x 136
			m_pRenderer1->GetTransform()->AddLocalPosition(float4(0, -100 * fTime, -130* fTime));
			m_pRenderer2->GetTransform()->AddLocalRotation(float4(0, 0, -90 * fTime));  //z
			m_pRenderer2->GetTransform()->AddLocalPosition(float4(-130 * fTime, -100 * fTime, 0));
			m_pRenderer3->GetTransform()->AddLocalPosition(float4(0, -260 * fTime, 0));

			m_pRenderer->FadeOut(0.33f, Delta);
			if (GetStateDuration()>0.33f)
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
			//πÆ∞Ì¡§
		},
		[this](float Delta)
		{
		},
		[this]
		{
		}
	);
}
