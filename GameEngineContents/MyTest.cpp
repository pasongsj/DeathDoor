#include "PrecompileHeader.h"
#include "MyTest.h"

#include "StaticParticleManager.h"
#include "Player.h"
#include "FireObject.h"
#include "SkillSlot.h"

#include "HitEffect.h"
#include "WaterBox.h"

#include <GameEngineBase/GameEngineRandom.h>

MyTest::MyTest()
{
}

MyTest::~MyTest()
{
}

void MyTest::Start()
{
	CreateKey();
}

void MyTest::Update(float _Delta)
{
	if (GameEngineInput::IsDown("MyTest") == true)
	{
		GetLevel()->CreateActor<HitEffect>();
	}
}

void MyTest::TestRender()
{
}

void MyTest::Render2Dto3D()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 MousePos = GameEngineWindow::GetMousePosition();

	std::shared_ptr<GameEngineCamera> MainCamera = GetLevel()->GetMainCamera();
	float4 CameraPos = MainCamera->GetTransform()->GetWorldPosition();

	float Ray_X = ((2.0f * MousePos.x) / ScreenSize.x) - 1.0f;
	float Raz_Y = ((-2.0f * MousePos.y) / ScreenSize.y) + 1.0f;

	float4x4 ProjMatrix = MainCamera->GetProjection();

	Ray_X = Ray_X / ProjMatrix.Arr2D[0][0];
	Raz_Y = Raz_Y / ProjMatrix.Arr2D[1][1];

	float4 RayPos = CameraPos;
	float4 RayDir = { Ray_X, Raz_Y, 1.0f };

	float4x4 ViewInverse = MainCamera->GetView().InverseReturn();
	float4 WorldRayDir = DirectX::XMVector3TransformNormal(RayDir, ViewInverse);

	WorldRayDir.Normalize();

	float4 RayDest = RayPos;

	while (true)
	{
		RayDest += WorldRayDir;

		//대상에 충돌했는가
		if (RayDest.z >= 0.0f)
		{
			break;
		}
	}

	GetTransform()->SetLocalPosition(RayDest);
}

void MyTest::CreateKey()
{
	if (GameEngineInput::IsKey("MyTest") == false)
	{
		GameEngineInput::CreateKey("MyTest", 'A');
	}
}