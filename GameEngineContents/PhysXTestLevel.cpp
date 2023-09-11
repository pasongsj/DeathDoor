#include "PreCompileHeader.h"
#include <GameEngineCore/GameEngineCoreWindow.h>

#include "PhysXTestLevel.h"
#include "PhysXTestActor.h"
#include "PhysXTestPlane.h"
#include "PhysXTrigger.h"
#include "Player.h"
#include <GameEngineCore/BloomEffect.h>
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
	CreateScene(); //LevelChangeStart 혹은 Start어디서 하든 상관없게끔 했음

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation({ 90.f,0.f,0.f });
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0,1000, .0f });

	m_pBloom = GetMainCamera()->GetDeferredLightTarget()->CreateEffect<BloomEffect>();

	GameEngineCoreWindow::AddDebugRenderTarget(0, "AllRenderTarget", GetMainCamera()->GetCamAllRenderTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(1, "LightRenderTarget", GetMainCamera()->GetDeferredLightTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(2, "MainCameraForwardTarget", GetMainCamera()->GetCamForwardTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(3, "DeferredTarget", GetMainCamera()->GetCamDeferrdTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(4, "BloomEffect", m_pBloom->ResultTarget);
	GameEngineCoreWindow::AddDebugRenderTarget(5, "BloomBlurEffect0", m_pBloom->BlurTarget0);
	GameEngineCoreWindow::AddDebugRenderTarget(6, "BloomBlurEffect1", m_pBloom->BlurTarget1);


	{
		std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();
	}

	m_pTestActor = CreateActor<PhysXTestActor>();
	CreateActor<PhysXTestPlane>();

	CreateActor<PhysXTrigger>();
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
