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
	if (false == isShoot)
	{
		return;
	}
	float4 Test = GetTransform()->GetWorldPosition();
	if (true == CheckCollision(PhysXFilterGroup::MonsterDynamic) || GetLiveTime() > firetime + 10.0f)
	{
		Death();
		return;
	}
	PhysXComp->GetDynamic()->setLinearVelocity({ 0,0,0 });
	PhysXComp->SetMoveSpeed(Dir * 1000.0f);
	isPhysXCollision = 0;
}


void PlayerAttMagic::SetDir(const float4& _Dir, const float4& _Pos)
{
	if (true == _Dir.IsZero())
	{
		MsgAssert("Zero dir은 입력할 수 없습니다");
		return;
	}

	if (nullptr == PhysXComp)
	{
		PhysXComp = CreateComponent< PhysXSphereComponent>();
		PhysXComp->CreatePhysXActors(float4::ONE * 100.0f, float4::ZERO);
		PhysXComp->SetFilterData(PhysXFilterGroup::PlayerSkill, PhysXFilterGroup::MonsterDynamic);
		PhysXComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		PhysXComp->TurnOffGravity();
		PhysXComp->SetTrigger();
	}
	PhysXComp->GetDynamic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERO, _Pos));


	//PhysXComp->SetWorldPosWithParent(_Pos);
	Dir = _Dir;
	firetime = GetLiveTime();
}