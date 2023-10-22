#include "PrecompileHeader.h"
#include "Frog_Lever.h"

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
	InitComponent();
}

void Frog_Lever::Update(float _DeltaTime)
{
	int a = 0;
}

void Frog_Lever::InitComponent()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->GetTransform()->SetLocalScale(float4{ 100, 100, 100 });
	m_pRenderer->SetFBXMesh("LEVER_MESH.FBX", "MeshAniTexture");
	m_pRenderer->CreateFBXAnimation("Lever_Open", "LEVER_OPEN (1).FBX", { 0.02f, true });
	m_pRenderer->ChangeAnimation("Lever_Open");

	float4 MeshScale = m_pRenderer->GetMeshScale();
	MeshScale *= 100.0f;

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);

	m_pPhysXTriggerComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXTriggerComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXTriggerComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);

	m_pPhysXTriggerComponent->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERONULL, GetTransform()->GetLocalPosition() + float4 { 0, 0 , -100}));
	m_pPhysXTriggerComponent->SetTrigger();

	// 충돌그룹세팅
	m_pPhysXTriggerComponent->SetFilterData(PhysXFilterGroup::LeverTrigger);
}
