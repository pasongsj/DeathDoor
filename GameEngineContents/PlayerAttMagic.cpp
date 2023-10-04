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
	float4 Test = GetTransform()->GetWorldPosition();
	if (true == CheckCollision(PhysXFilterGroup::MonsterDynamic) || GetLiveTime() > firetime + 10.0f)
	{
		Death();
		return;
	}
	//GetTransform()->AddLocalPosition(Dir * 2000.0f * _DeltaTime);
	PhysXComp->GetDynamic()->setLinearVelocity({ 0,0,0 });
	PhysXComp->SetMoveSpeed(Dir * 500.0f);

	if (true == CheckCollision(PhysXFilterGroup::MonsterDynamic))
	{
		int a = 0;
	}
	UINT CheckNum = isPhysXCollision;
	isPhysXCollision = 0;
}
