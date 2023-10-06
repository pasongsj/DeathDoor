#pragma once
#include "PlayerAttackBase.h"
class PlayerAttackMagic : public PlayerAttackBase
{
public:
	// constrcuter destructer
	PlayerAttackMagic() ;
	~PlayerAttackMagic();

	// delete Function
	PlayerAttackMagic(const PlayerAttackMagic& _Other) = delete;
	PlayerAttackMagic(PlayerAttackMagic&& _Other) noexcept = delete;
	PlayerAttackMagic& operator=(const PlayerAttackMagic& _Other) = delete;
	PlayerAttackMagic& operator=(PlayerAttackMagic&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//bool isShoot = false;

	//void SetDir(const float4& _Dir, const float4& _Pos);

	//float4 Dir = float4::ZERO;
	//float firetime = 0.0f;
	//// Component
	//// Render
	//std::shared_ptr<class ContentFBXRenderer> MagicRenderer = nullptr;
	////physx
	//std::shared_ptr<class PhysXSphereComponent> PhysXComp = nullptr;

	//// init
	//void Init();

};

