#include "PrecompileHeader.h"
#include "StaticParticleManager.h"

#include <GameEngineBase/GameEngineRandom.h>

StaticParticleManager::StaticParticleManager()
{
}

StaticParticleManager::~StaticParticleManager()
{
}

void StaticParticleManager::Start()
{
}

void StaticParticleManager::Update(float _Delta)
{
	ParticleUpdate(_Delta);
}

void StaticParticleManager::Render(float _Delta)
{
}

void StaticParticleManager::ParticleUpdate(float _Delta)
{
	EmitCount += _Delta;

	if (isFull == true && CurParticle == 0)
	{
		Death();
		return;
	}

	if (EmitCount >= Setter.EmitInterTime && isOn == true && isFull == false)
	{
		EmitCount = 0.0f;

		for (int i = 0; i < Setter.EmitNum; i++)
		{
			CreateParticle();
		}
	}

	if (isDisposable == true && ParticleCount == Setter.MaxParticle)
	{
		isFull = true;
	}

	size_t NumOfParticle = ParticleList.size();

	for (int index = 0; index < NumOfParticle; index++)
	{

		if (ParticleList[index] == nullptr)
		{
			continue;
		}

		if (ParticleList[index]->GetUnit()->Color.MulColor.a <= 0.0f)
		{
			ParticleList[index]->Death();
			ParticleList[index] = nullptr;

			CurParticle--;

			continue;
		}

		ParticleList[index]->ParticlePosUpdate(_Delta);
		ParticleList[index]->GetUnit()->Color.MulColor.a -= (1.0f / Setter.MaxLiveTime) * _Delta;

		if (ParticleList[index]->GetUnit()->Color.MulColor.a <= 0.0f)
		{
			ParticleList[index]->GetUnit()->Color.MulColor.a = 0.0f;
		}
	}
}

void StaticParticleManager::CreateParticle()
{
	if (CurParticle >= Setter.MaxParticle)
	{
		return;
	}

	std::shared_ptr<ParticleRenderer> NewParticle = CreateComponent<ParticleRenderer>();
	NewParticle->SetFBXMesh(MeshName.data(), "ContentMesh");

	float4 Scale = 
	{
		GameEngineRandom::MainRandom.RandomFloat(Setter.StandardScale.x - Setter.RangeScale.x, Setter.StandardScale.x + Setter.RangeScale.x),
		GameEngineRandom::MainRandom.RandomFloat(Setter.StandardScale.y - Setter.RangeScale.y, Setter.StandardScale.y + Setter.RangeScale.y),
		GameEngineRandom::MainRandom.RandomFloat(Setter.StandardScale.z - Setter.RangeScale.z, Setter.StandardScale.z + Setter.RangeScale.z)
	};

	float4 Position =
	{
		GameEngineRandom::MainRandom.RandomFloat(Setter.StandardPosition.x - Setter.RangePosition.x, Setter.StandardPosition.x + Setter.RangePosition.x),
		GameEngineRandom::MainRandom.RandomFloat(Setter.StandardPosition.y - Setter.RangePosition.y, Setter.StandardPosition.y + Setter.RangePosition.y),
		GameEngineRandom::MainRandom.RandomFloat(Setter.StandardPosition.y - Setter.RangePosition.z, Setter.StandardPosition.y + Setter.RangePosition.z),
	};

	float4 Dir =
	{
		GameEngineRandom::MainRandom.RandomFloat(Setter.StandardDir.x - Setter.RangeDir.x, Setter.StandardDir.x + Setter.RangeDir.x),
		GameEngineRandom::MainRandom.RandomFloat(Setter.StandardDir.y - Setter.RangeDir.y, Setter.StandardDir.y + Setter.RangeDir.y)
	};

	float Speed = GameEngineRandom::MainRandom.RandomFloat(Setter.StandardSpeed - Setter.range_Speed, Setter.StandardSpeed + Setter.range_Speed);
	
	NewParticle->GetTransform()->SetLocalScale(Scale);
	NewParticle->GetTransform()->SetLocalPosition(Position);
	NewParticle->SetParticleInfo(Dir.NormalizeReturn(), Speed);

	PushParticleToFront(NewParticle);

	ParticleCount++;
	CurParticle++;
}

void StaticParticleManager::PushParticleToFront(std::shared_ptr<ParticleRenderer> _Particle)
{
	size_t Size = ParticleList.size();

	for (int i = 0; i < Size; i++)
	{
		if (ParticleList[i] == nullptr)
		{
			ParticleList[i] = _Particle;
			return;
		}
	}
}