#include "PrecompileHeader.h"
#include "CullingTrigger.h"

#include "ContentFBXRenderer.h"
#include "PhysXBoxComponent.h"

#include "CullingObject.h"

CullingTrigger::CullingTrigger()
{
}

CullingTrigger::~CullingTrigger()
{
}



void CullingTrigger::Start()
{
	InitComponent();
}

void CullingTrigger::Update(float _DeltaTime)
{
	//if (true == CheckCollision(PhysXFilterGroup::PlayerDynamic))
	//{
	//	// 내가 플레이어 다이나믹이랑 충돌했고
	//	if (false == m_bIsActivate)
	//	{
	//		TriggerOn();
	//		On_CullingObject();
	//	}
	//}

	// isPhysXCollision = 0;
}

void CullingTrigger::InitComponent()
{	
	GetTransform()->SetLocalPosition(float4{ 0, 5, 0 });

	m_pRenderer = CreateComponent<ContentFBXRenderer>();

	// 트리거 메쉬 변경 예정
	m_pRenderer->SetFBXMesh("Ruins_Wall.fbx", "ContentMeshDeffered");

	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::CullingTrigger);
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);
	m_pPhysXComponent->SetTrigger();
}


void CullingTrigger::Set_CullingObjectNumber(int _Number0 , int _Number1, int _Number2, int _Number3 /*= INT_MAX*/)
{
	if (0 > _Number0 || 0 > _Number1 || 0 > _Number2 || 1 >= _Number3)
	{
		MsgAssert("인덱스 값이 이상합니다.");
		return;
	}

	m_vCullingObj_Numbers.push_back(_Number0);
	m_vCullingObj_Numbers.push_back(_Number1);
	m_vCullingObj_Numbers.push_back(_Number2);


	if (INT_MAX != _Number3)
	{
		m_vCullingObj_Numbers.push_back(_Number3);
	}
}
