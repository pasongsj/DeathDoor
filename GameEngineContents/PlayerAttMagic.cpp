#include "PreCompileHeader.h"
#include "PlayerAttMagic.h"

#include "ContentFBXRenderer.h"
#include "PhysXSphereComponent.h"

PlayerAttMagic::PlayerAttMagic()
{
}

PlayerAttMagic::~PlayerAttMagic()
{
}
void PlayerAttMagic::Init()
{
	MagicRenderer = CreateComponent< ContentFBXRenderer>();
	MagicRenderer->SetFBXMesh("SphereDefault.fbx","ContentMeshDeffered");

	GetTransform()->SetLocalScale(float4::ONE * 0.2f);

	PhysXComp = CreateComponent< PhysXSphereComponent>();
	PhysXComp->CreatePhysXActors(float4::ONE  * 200.0f,float4::ZERO,true); 
	PhysXComp->SetFilterData(PhysXFilterGroup::PlayerSkill, PhysXFilterGroup::MonsterDynamic);
	//PhysXComp->SetPhysxMaterial(1.f, 1.f, 0.f);
	//PhysXComp->TurnOffGravity();
}


void PlayerAttMagic::Start()
{
	Init();
}

void PlayerAttMagic::Update(float _DeltaTime)
{
	if (true == Dir.IsZero())
	{
		return;
	}
	if (true == CheckCollision(PhysXFilterGroup::MonsterDynamic) || GetLiveTime() > firetime + 10.0f)
	{
		Death();
		return;
	}
	GetTransform()->AddLocalPosition(Dir * 2000.0f * _DeltaTime);
}
