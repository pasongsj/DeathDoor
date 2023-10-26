#include "PrecompileHeader.h"
#include "Ladder.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

#include "Player.h"

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
	SetNextState(TriggerState::PROGRESS);
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
	
	m_pPhysXComponent->CreateSubShape(SubShapeType::BOX, float4(100,10,100), float4(50, 10, 0));
	m_pPhysXComponent->SetSubShapeFilter(PhysXFilterGroup::LeverTrigger);
	m_pPhysXComponent->AttachShape();

}

void Ladder::InitAnimation()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("Ladder.fbx", "ContentMeshDeffered");
	m_pRenderer->GetTransform()->SetLocalPosition(float4(0, LadderHeight - m_fHeight, 0));
	auto Unit = m_pRenderer->GetAllRenderUnit();
	Unit[0][0]->ShaderResHelper.SetTexture("DiffuseTexture", "BlackScreen.png");
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
			m_pRenderer->Off();
		},
		[this](float Delta)
		{
			if (false == m_bHidden)
			{
				//히든 사다리가 해제되면 넘기기
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
			 m_pRenderer->On();

			if (nullptr!=m_TriggerFunc)
			{
				m_TriggerFunc();
			}

		},
		[this](float Delta)
		{
			if (true == IsPlayerInRange())
			{
				// e키 누르라는 ui띄우기			
			}
			if (true == TriggerKeyCheck())
			{
				//키눌렸으면 ON으로 전환하고 PlayerClimb상태로 전환
				SetNextState(TriggerState::ON);
			};
		},
		[this]
		{
		}
	);

	SetFSM(TriggerState::ON,
		[this]
		{
			//e키 ui끄기
		},
		[this](float Delta)
		{
			//플레이어가 특정 위치 이상으로 올라가버렸다면 강제적으로 맨위 바닥까지 올려보내주기
		},
		[this]
		{
		}
	);
}

void Ladder::SetLadderPosition()
{
	// 플레이어한테 포지션 보내주기
}
