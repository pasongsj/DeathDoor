#include "PrecompileHeader.h"
#include "CullingObject.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

CullingObject::CullingObject()
{
}

CullingObject::~CullingObject()
{
}

void CullingObject::Start()
{
}

void CullingObject::Update(float _DeltaTime)
{
}

// 얘는 Start 가 아니라, CreateActor 이후에 InitComponent 를 직접 호출하여 초기화 한다. 
void CullingObject::InitComponent(const std::string& _MeshName)
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh(_MeshName, "ContentMeshDeffered");
	m_pRenderer->Off();

	float4 MeshScale = m_pRenderer->GetMeshScale();

	/*m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetTrigger();
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::CullingObject);
	
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);*/
}

