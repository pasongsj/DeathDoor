#include "PrecompileHeader.h"
#include "SecretTile.h"

#include "PhysXBoxComponent.h"
#include "ContentFBXRenderer.h"

#include "FrogBossLevel.h"
#include "DustParticle.h"

#include <GameEngineBase/GameEngineRandom.h>

SecretTile::SecretTile()
{
}

SecretTile::~SecretTile()
{
}


void SecretTile::InActive()
{
	OffShake();
	m_bIsActive = false;
	m_pRenderer->Off();
	
	m_pPhysXComponent->Death();
	m_pPhysXComponent = nullptr;
}

void SecretTile::Active()
{
	m_bIsActive = true; 
	m_pRenderer->On();
	
	InitComponent();
	
	//float4 MeshScale = m_pRenderer->GetMeshScale();
	//m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();									
	//m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	//m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERO, true);
	//
	//m_pPhysXComponent->SetDynamicPivot(float4{ 0.0f, -MeshScale.y , 0.0f });
	//m_pPhysXComponent->SetPositionSetFromParentFlag(true);
	//m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);
	//
	//float4 Test = GetTransform()->GetLocalRotation();
	//
	////타일사이즈저장
	//m_TileSize = static_cast<float>(MeshScale.x * sqrt(2) / 2.0f);
}

void SecretTile::TileShake(float _DeltaTime)
{
	if (0.0f >= m_fShakeTime)
	{
 		m_bShake = false;
		m_fShakeTime = 2.0f;

		InActive();
		return;
	}

	// shake 코드치면 된다~ 부들부들대게 만들면 되는데~~ 
	m_fShakeTime -= _DeltaTime;

	int RandomValue = GameEngineRandom::MainRandom.RandomInt(1, 2);
	float RandomRotValue = GameEngineRandom::MainRandom.RandomFloat(-7.0f , 7.0f);
	if (RandomValue == 1)
	{
		GetTransform()->SetLocalRotation(float4{ RandomRotValue, 0, 0 });
	}

	else if (RandomValue == 2)
	{
		GetTransform()->SetLocalRotation(float4{ 0 , 0, RandomRotValue });
	}
}

void SecretTile::OffShake()
{
	m_bShake = false;
	m_fShakeTime = 2.0f;
	// GetTransform()->SetLocalRotation(float4{ 0, -45, 0 });

	for (int i = 0; i < DustParticleList.size(); i++)
	{
		DustParticleList[i]->SetFadeOut();
	}

	DustParticleList.clear();
}

void SecretTile::Start()
{
	GetTransform()->SetLocalPosition(float4{ 0.0f , 0.1f , 0.0f });

	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("FrogTile.fbx", "ContentMeshDeffered");

	InitComponent();
}

void SecretTile::Update(float _DeltaTime)
{
	if (true == m_bShake)
	{
		TileShake(_DeltaTime);
	}
}

void SecretTile::InitComponent()
{
	GetTransform()->SetLocalRotation(float4{ 0, 0, 0 });

	float4 MeshScale = m_pRenderer->GetMeshScale();

	m_pPhysXComponent = CreateComponent<PhysXBoxComponent>();
	m_pPhysXComponent->SetPhysxMaterial(0.0f, 0.0f, 0.0f);
	m_pPhysXComponent->CreatePhysXActors(MeshScale.PhysXVec3Return(), float4::ZERONULL, true);
	m_pPhysXComponent->SetDynamicPivot(float4{ 0.0f, -MeshScale.y , 0.0f });
	m_pPhysXComponent->SetPositionSetFromParentFlag(true);
	m_pPhysXComponent->SetFilterData(PhysXFilterGroup::Obstacle);

	m_TileSize = static_cast<float>(MeshScale.x * sqrt(2) / 2.0f);
}
void SecretTile::CreateDustParticle()
{
	for(int i = 0; i < 8; i++)
	{
		std::shared_ptr<DustParticle> Particle = CreateComponent<DustParticle>();
		Particle->GetTransform()->SetWorldScale({ 100.0f, 100.0f });
		Particle->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f});
		
		//어떤 선 위에 위치할 것인가
		//1 : 왼쪽 세로선
		//2 : 오른쪽 세로선
		//3 : 위쪽 가로선
		//4 : 아래쪽 가로선

		int Line = GameEngineRandom::MainRandom.RandomInt(1, 4);

		float X = 0.0f;
		float Y = 0.0f;

		if (Line == 1)
		{
			X = -200;
			Y = GameEngineRandom::MainRandom.RandomFloat(-200, 200);
		}
		if (Line == 2)
		{
			X = 200;
			Y = GameEngineRandom::MainRandom.RandomFloat(-200, 200);
		}
		if (Line == 3)
		{
			X = GameEngineRandom::MainRandom.RandomFloat(-200, 200);
			Y = 200;
		}
		if (Line == 4)
		{
			X = GameEngineRandom::MainRandom.RandomFloat(-200, 200);
			Y = -200;
		}

		Particle->GetTransform()->SetLocalPosition({ X, 30.0f, Y });
		Particle->BillboardingOff();
		
		DustParticleList.push_back(Particle);
	}
}