#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "PhysXSphereComponent.h"

class PlayerAttMagic : public GameEngineActor
{
	friend class Player;
public:
	// constrcuter destructer
	PlayerAttMagic() ;
	~PlayerAttMagic();

	// delete Function
	PlayerAttMagic(const PlayerAttMagic& _Other) = delete;
	PlayerAttMagic(PlayerAttMagic&& _Other) noexcept = delete;
	PlayerAttMagic& operator=(const PlayerAttMagic& _Other) = delete;
	PlayerAttMagic& operator=(PlayerAttMagic&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	void SetDir(const float4& _Dir, const float4& _Pos)
	{
		if (true == _Dir.IsZero())
		{
			MsgAssert("Zero dir은 입력할 수 없습니다");
			return;
		}

		PhysXComp = CreateComponent< PhysXSphereComponent>();
		PhysXComp->CreatePhysXActors(float4::ONE * 100.0f,float4::ZERO);
		PhysXComp->SetFilterData(PhysXFilterGroup::PlayerSkill, PhysXFilterGroup::MonsterDynamic);
		PhysXComp->GetDynamic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERO,_Pos));
		PhysXComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		PhysXComp->TurnOffGravity();

		//PhysXComp->SetWorldPosWithParent(_Pos);
		Dir = _Dir;
		firetime = GetLiveTime();
	}

	float4 Dir = float4::ZERO;
	float firetime = 0.0f;
	// Component
	// Render
	std::shared_ptr<class ContentFBXRenderer> MagicRenderer = nullptr;
	//physx
	std::shared_ptr<class PhysXSphereComponent> PhysXComp = nullptr;

	// init
	void Init();

};

