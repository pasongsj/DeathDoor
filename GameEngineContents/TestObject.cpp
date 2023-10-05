#include "PrecompileHeader.h"
#include "TestObject.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineFBXRenderer.h>
#include "ServerPacket.h"

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
	GetTransform()->SetLocalPosition(float4(0.f, 10.f, 0.f));
	
}

void TestObject::Update(float _DeltaTime)
{
	NetControlType Type = GetControlType();

	switch (Type)
	{
	case NetControlType::UserControl:
		UserUpdate(_DeltaTime);
		break;
	case NetControlType::NetControl:
		NetUpdate(_DeltaTime);
		break;
	default:
		break;
	}

}

void TestObject::NetUpdate(float _DeltaTime)
{
	if (false == IsPacket())
	{
		return;
	}

	while (IsPacket())
	{
		PacketEnum Type = GetFirstPacketType<PacketEnum>();

		switch (Type)
		{
		case PacketEnum::ObjectUpdatePacket:
		{
			std::shared_ptr<ObjectUpdatePacket> ObjectUpdate = PopFirstPacket<ObjectUpdatePacket>();
			if (ObjectUpdate->LevelType != GetLevel()->GetLevelType<PacketLevelType>())
			{
				//현재 레벨에 해당하지 않는 패킷을 보냈습니다.
				break;
			}
			PacketDataType Type = ObjectUpdate->DataType;
			switch (Type)
			{
			case PacketDataType::Transform:
				GetTransform()->SetLocalPosition(ObjectUpdate->Scale);
				GetTransform()->SetLocalPosition(ObjectUpdate->Position);
				GetTransform()->SetLocalRotation(ObjectUpdate->Rotation);
				break;
			case PacketDataType::State:
				//ChangeSate
				break;
			case PacketDataType::CharacterType:
				//Change Animation
				break;
			case PacketDataType::Items:
				// items
				break;
			default:
				break;
			}

			break;
		}
		default:
			MsgAssert("처리하지 못하는 패킷이 플레이어로 날아왔습니다.");
			return;
		}
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


void TestObject::SendNetPacket()
{

	if (true == IsNet())
	{
		//transform 보내기
		{
			std::shared_ptr<ObjectUpdatePacket> NewPacket = std::make_shared<ObjectUpdatePacket>();
			NewPacket->SetObjectID(GetNetObjectID());
			NewPacket->LevelType = GetLevel()->GetLevelType<PacketLevelType>();
			//NewPacket->ObjectType = PacketObjectType::Player;
			NewPacket->DataType = PacketDataType::Transform;
			NewPacket->Scale = GetTransform()->GetLocalScale();
			NewPacket->Position = GetTransform()->GetLocalPosition();
			NewPacket->Rotation = GetTransform()->GetLocalRotation();
			GetNet()->SendPacket(NewPacket);
		}
		//state보내기
		//{
		//	std::shared_ptr<ObjectUpdatePacket> NewPacket = std::make_shared<ObjectUpdatePacket>();
		//	NewPacket->SetObjectID(GetNetObjectID());
		//	NewPacket->ObjectType = PacketObjectType::Player;
		//	NewPacket->DataType = PacketDataType::State;
		//	NewPacket->ObjectState = PacketObjectBaseState::Base;
		//	GetNet()->SendPacket(NewPacket);
		//}
	}
}
