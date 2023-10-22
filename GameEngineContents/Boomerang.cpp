#include "PrecompileHeader.h"
#include "Boomerang.h"

Boomerang::Boomerang()
{
}

Boomerang::~Boomerang()
{
}


void Boomerang::Start()
{
	SetRender(float4::ONE * 150.0f, "Boomerang.fbx");
	SetPhysXComp(float4::ONE * 150.0f, float4::DOWN * 100.0f);
}

void Boomerang::Update(float _DeltaTime)
{
	if (nullptr == AttackRenderer)
	{
		return;
	}
	AttackRenderer->GetTransform()->SetLocalRotation(float4{ 0.0f, GetLiveTime() * 200.0f ,0 });

	if (BackTo == false)
	{
		if (GetLiveTime() > 3.0f)
		{
			SetShootSpeed(50.0f);
			DestPostion = float4::ZERONULL;
			BackTo = true;
		}
		else if (GetLiveTime() > 0.7f)
		{
			SetShootSpeed(200.0f);
		}
		else if (GetLiveTime() > 0.5f)
		{
			SetShootSpeed(400.0f);
		}
	}
 	else if(DestPostion != float4::ZERONULL)
	{
		float4 Distance = DestPostion - GetTransform()->GetWorldPosition();
		Distance.y = 0;
		SetTrans(Distance.NormalizeReturn());
		if (Distance.Size() < 50.0f)
		{
			SetShootSpeed(0.0f);
			Destroy = true;
		}
	}
	if (GetLiveTime() > 10.0f)
	{
		Destroy = true;
	}
	AttackBase::Update(_DeltaTime);
}