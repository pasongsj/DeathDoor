#include "PreCompileHeader.h"
#include <GameEngineCore/GameEngineCoreWindow.h>

#include <GameEngineCore/BloomEffect.h>
#include <GameEngineCore/GameEngineParticleRenderer.h>

#include "PhysXTestLevel.h"
#include "PhysXTestActor.h"
#include "PhysXTestPlane.h"
#include "PhysXBoxComponent.h"
#include "PhysXTrigger.h"
#include "Player.h"



PhysXTestLevel::PhysXTestLevel() 
{
}

PhysXTestLevel::~PhysXTestLevel() 
{
}

void PhysXTestLevel::Start()
{
	SetLevelType(PacketLevelType::PhysXTestLevel);
}

void PhysXTestLevel::LevelChangeStart()
{
	std::shared_ptr<GameEngineActor> TestP = CreateActor<GameEngineActor>();
	std::shared_ptr<GameEngineParticleRenderer> Particle = TestP->CreateComponent<GameEngineParticleRenderer>();

	CreateScene(); //LevelChangeStart 혹은 Start어디서 하든 상관없게끔 했음

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation({ 90.f,0.f,0.f });
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0,1000, .0f });

	m_pBloom = GetMainCamera()->GetDeferredLightTarget()->CreateEffect<BloomEffect>();

	{
		std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();
	}

	m_pTestActor = CreateActor<PhysXTestActor>();
	m_pTestActor->SetName("TestActor");
	
	std::shared_ptr<PhysXTestPlane> test = CreateActor<PhysXTestPlane>();
	test->GetComp()->SetWorldPosWithParent(float4(100, 0, 100));

	std::shared_ptr<PhysXTrigger> testTrigger = CreateActor<PhysXTrigger>();
	testTrigger->SetName("TestTrigger");
	std::shared_ptr<PhysXTestPlane> pWallPlane = CreateActor<PhysXTestPlane>();
	//m_pTestActor = CreateActor<Player>();
	
	
}

void PhysXTestLevel::LevelChangeEnd()
{
	AllActorDestroy();
}

void PhysXTestLevel::Update(float _DeltaTime)
{
	//SetCameraPvd({5000,5000,5000}, m_pTestActor->GetTransform()->GetWorldRotation());
}
