#include "PrecompileHeader.h"
#include "ShortCutDoor.h"
#include "PhysXBoxComponent.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>
#include "FadeEffect.h"

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
	m_pFade = GetLevel()->GetLastTarget()->CreateEffect<FadeEffect>();
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
	m_pPhysXComponent->CreatePhysXActors(float4(140,200,30), float4::ZERONULL, true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);

	m_pPhysXComponent->CreateSubShape(SubShapeType::BOX, float4(140,60,140), float4(0, 50, -70));
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


	m_pRenderer1= CreateComponent<ContentFBXRenderer>();
	m_pRenderer1->GetTransform()->SetLocalScale(float4{ 100, 100, 100 });
	m_pRenderer1->SetFBXMesh("SHORTCUTDOOR_path.FBX", "ContentMeshDeffered");
	auto Unit = m_pRenderer->GetAllRenderUnit();
	Unit[0][4]->Off();
	Unit[0][5]->Off();
	Unit[0][6]->Off();
	Unit[0][7]->Off();
	Unit[0][8]->Off();
	//Unit[0][8]->ShaderResHelper.SetTexture("DiffuseTexture", "OldCrowFloor.png");
	//m_pRenderer->SetGlowToUnit(0, 8);
	//m_pRenderer->SetUnitDiffuseColorIntensity(0, 8, 4.0f);
	
	
	auto Unit1 = m_pRenderer1->GetAllRenderUnit();
	Unit1[0][0]->ShaderResHelper.SetTexture("DiffuseTexture", "OldCrowFloor.png");
	m_pRenderer1->SetGlowToUnit(0, 0);
	m_pRenderer1->SetUnitDiffuseColorIntensity(0, 0, 4.0f);
}

float test = 0.f;
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
			switch (m_eStartState)
			{
			case StartState::OPEN:
			{
				m_pRenderer->ChangeAnimation("OPEN_STILL");
			}
			break;
			case StartState::CLOSE:
			{
				m_pRenderer->ChangeAnimation("FLOOR");
			}
			break;
			}
		},
		[this](float Delta)
		{
			if (StartState::OPEN == m_eStartState)
			{
				m_pFade->FadeIn();
			}
			if (StartState::OPEN == m_eStartState && GetStateDuration() >= 1.5f)
			{
				SetNextState(TriggerState::PROGRESS);
			}

			if (true == TriggerKeyCheck())
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
			switch (m_eStartState)
			{
			case StartState::OPEN:
			{
				m_pRenderer->ChangeAnimation("CLOSE_FROM_INWARD");
			}
				break;
			case StartState::CLOSE:
			{
				m_pRenderer->ChangeAnimation("OPEN_Inward");
				m_pFade->FadeOut();
			}
				break;
			}
		},
		[this](float Delta)
		{	
			GetLevel()->GetLastTarget()->Effect(Delta);
			if (true == m_pRenderer->IsAnimationEnd())
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
			switch (m_eStartState)
			{
			case StartState::OPEN:
			{
				m_pRenderer->ChangeAnimation("FLOOR");
			}
			break;
			case StartState::CLOSE:
			{
				m_pRenderer->ChangeAnimation("OPEN_STILL");
				if (nullptr != m_TriggerFunc)
				{
					m_TriggerFunc();
				}
			}
			break;
			}

		},
		[this](float Delta)
		{
			GetLevel()->GetLastTarget()->Effect(Delta);
			//È­¸é Fade?
			if (StartState::OPEN == m_eStartState)
			{
				SetState(StartState::CLOSE);
				SetNextState(TriggerState::OFF);
			}

		},
		[this]
		{
		}
	);
}
