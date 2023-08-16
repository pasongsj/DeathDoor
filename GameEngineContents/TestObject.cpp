#include "PrecompileHeader.h"
#include "TestObject.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineFBXRenderer.h>
#include "PhysXTestLevel.h"

TestObject* TestObject::MainTestObject = nullptr;

TestObject::TestObject() 
{
	MainTestObject = this;
}

TestObject::~TestObject() 
{
}

void TestObject::Start()
{
	std::shared_ptr<GameEngineFBXRenderer> pRenderer = CreateComponent<GameEngineFBXRenderer>();
	pRenderer->SetFBXMesh("House1.fbx", "MeshTexture");

	float4 Scale = pRenderer->GetTransform()->GetLocalScale();
	pRenderer->GetTransform()->SetLocalScale(Scale * 10.0f);
	GetTransform()->SetLocalPosition(float4(0.f, 1000.f, 0.f));
	
}

void TestObject::Update(float _DeltaTime)
{
	NetControlType Type = GetControlType();

	switch (Type)
	{
	case NetControlType::None:
		UserUpdate(_DeltaTime);
		break;
	case NetControlType::UserControl:
		UserUpdate(_DeltaTime);
		break;
	case NetControlType::ServerControl:
		ServerUpdate(_DeltaTime);
		break;
	default:
		break;
	}
		
}

void TestObject::UserUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("SpeedBoost") && m_pSpeed > 1000.f)
	{
		m_pSpeed = 1000.f;
	}
	else
	{
		m_pSpeed = 200.f;
	}

	if (true == GameEngineInput::IsPress("CamMoveLeft"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldLeftVector() * m_pSpeed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveRight"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldRightVector() * m_pSpeed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveUp"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldUpVector() * m_pSpeed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveDown"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldDownVector() * m_pSpeed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveForward"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldForwardVector() * m_pSpeed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("CamMoveBack"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetWorldBackVector() * m_pSpeed * _DeltaTime);
	}
}

void TestObject::ServerUpdate(float _DeltaTime)
{
}

