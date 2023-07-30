#include "PrecompileHeader.h"
#include "TestObject.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>

TestObject::TestObject() 
{
}

TestObject::~TestObject() 
{
}

void TestObject::Start()
{
	m_pTestObj = CreateComponent <GameEngineSpriteRenderer>();
	m_pTestObj->GetTransform()->SetLocalScale(float4{100.f, 100.f, 100.f});
}

void TestObject::Update(float _DeltaTime)
{
		if (true == GameEngineInput::IsPress("SpeedBoost")&& m_pSpeed>1000.f)
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

