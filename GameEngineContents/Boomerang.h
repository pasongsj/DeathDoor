#pragma once
#include "EnemyAttackSphere.h"

class Boomerang : public EnemyAttackSphere
{
	friend class EnemyJumper;
public:

	Boomerang();
	~Boomerang();

	Boomerang(const Boomerang& _Other) = delete;
	Boomerang(Boomerang&& _Other) noexcept = delete;
	Boomerang& operator=(const Boomerang& _Other) = delete;
	Boomerang& operator=(Boomerang&& _Other) noexcept = delete;




protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	bool BackTo = false;

	bool Destroy = false;
	void SetDestPos(const float4& _Pos)
	{
		DestPostion = _Pos;
		float4 Dir = DestPostion - GetTransform()->GetWorldPosition();
		Dir.Normalize();
		SetTrans(Dir);
		SetShootSpeed(800.0f);
	}


	float4 DestPostion = float4::ZERONULL;

};

