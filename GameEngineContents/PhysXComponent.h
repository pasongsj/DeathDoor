#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include "PhysXDefault.h"

// Ό³Έν :
class PhysXComponent : public GameEngineComponent, public PhysXDefault
{
public:
	// constrcuter destructer
	PhysXComponent();
	~PhysXComponent();

	// delete Function
	PhysXComponent(const PhysXComponent& _Other) = delete;
	PhysXComponent(PhysXComponent&& _Other) noexcept = delete;
	PhysXComponent& operator=(const PhysXComponent& _Other) = delete;
	PhysXComponent& operator=(PhysXComponent&& _Other) noexcept = delete;

	virtual void CreatePhysXActors(float4 _GeoMetryScale = float4(2.0f, 2.0f, 2.0f), float4 _GeoMetryRot = float4::ZERO, bool _Static = false) {};
	virtual void CreatePhysXActors(physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = float4::ZERO, bool _Static = false) {};


	void SetShapeAxis(float _Rot = 0, float4 _Axis = float4::UP)
	{
		float Rot = _Rot * GameEngineMath::DegToRad;
		physx::PxTransform Transform;
		Transform.p = m_pShape->getLocalPose().p;
		Transform.q = physx::PxQuat(Rot, _Axis.PhysXVec3Return());
		m_pShape->setLocalPose(Transform);
	}
protected:

private:

};

