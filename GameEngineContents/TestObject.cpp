#include "PrecompileHeader.h"
#include "TestObject.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineFBXRenderer.h>
#include "ObjectUpdatePacket.h"

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

	static float Delta = 0.0f;

	Delta += _DeltaTime;

	if (Delta <= 1.0f / 60.0f)
	{
		return;
	}

	Delta -= 1.0f / 60.0f;

	if (true == IsNet())
	{
		std::shared_ptr<ObjectUpdatePacket> NewPacket = std::make_shared<ObjectUpdatePacket>();
		NewPacket->SetObjectID(GetNetObjectID());
		NewPacket->Position = GetTransform()->GetWorldPosition();
		NewPacket->Rotation = GetTransform()->GetWorldRotation();
		GetNet()->SendPacket(NewPacket);
	}
}

void TestObject::ServerUpdate(float _DeltaTime)
{
}

