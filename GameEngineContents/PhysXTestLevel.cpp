#include "PreCompileHeader.h"
#include "PhysXTestLevel.h"
#include "PhysXTestActor.h"
#include "PhysXTestPlane.h"
#include "Player.h"
#include <GameEngineCore/GameEngineCoreWindow.h>
PhysXTestLevel::PhysXTestLevel() 
{
}

PhysXTestLevel::~PhysXTestLevel() 
{
}

void PhysXTestLevel::Start()
{
	SetLevelType(PacketLevelType::PhysXTestLevel);
	CreateScene();	
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation({ 90.f,0.f,0.f });
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0,1000, .0f });

	GameEngineCoreWindow::AddDebugRenderTarget(0, "AllRenderTarget", GetMainCamera()->GetCamAllRenderTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(1, "LightRenderTarget", GetMainCamera()->GetDeferredLightTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(2, "MainCameraForwardTarget", GetMainCamera()->GetCamForwardTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(3, "DeferredTarget", GetMainCamera()->GetCamDeferrdTarget());


}

void PhysXTestLevel::LevelChangeStart()
{	

	{
		std::shared_ptr<GameEngineLight> Light = CreateActor<GameEngineLight>();
	}

	//m_pTestActor = CreateActor<PhysXTestActor>();
	CreateActor<PhysXTestPlane>();
	 CreateActor<Player>();
	
	std::shared_ptr<PhysXTestPlane> pWallPlane = CreateActor<PhysXTestPlane>();
}

void PhysXTestLevel::LevelChangeEnd()
{
	AllActorDestroy();
}

void PhysXTestLevel::Update(float _DeltaTime)
{
	//SetCameraPvd(GetTransform()->GetWorldPosition(), m_pTestActor->GetTransform()->GetWorldRotation());
}
