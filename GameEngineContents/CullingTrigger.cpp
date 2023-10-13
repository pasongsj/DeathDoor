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
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::CullingTrigger, PhysXFilterGroup::PlayerDynamic);
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);
	m_pPhysXComponent->SetTrigger();
}



void CullingTrigger::Set_CullingObject(std::shared_ptr<class CullingObject> _Obj, std::shared_ptr<class CullingObject> _Obj2)
{
	if (nullptr == _Obj || nullptr == _Obj2)
	{
		MsgAssert("컬링오브젝트가 nullptr 입니다.");
		return;
	}

	m_pCullingObject_1 = _Obj;
	m_pCullingObject_2 = _Obj2;

	m_pCullingObject_1.lock()->LinkOn();
	m_pCullingObject_2.lock()->LinkOn();
}

void CullingTrigger::On_CullingObject()
{
	m_pCullingObject_1.lock()->GetRenderer()->On();
	m_pCullingObject_2.lock()->GetRenderer()->On();
}

void CullingTrigger::Off_CullingObject()
{
	m_pCullingObject_1.lock()->GetRenderer()->Off();
	
	// m_pCullingObject_2.lock()->GetRenderer()->Off();
}
