#include "PrecompileHeader.h"
#include "MyTest.h"

#include "DynamicParticleManager.h"

MyTest::MyTest()
{
}

MyTest::~MyTest()
{
}

void MyTest::Start()
{
	std::shared_ptr<DynamicParticleManager> New  = GetLevel()->CreateActor<DynamicParticleManager>();
	
	DynamicParticleSetter Setter;

	New->SetMeshName("Sphere.fbx");

	Setter.StandardPosition = &GetTransform()->GetTransDataRef();
	Setter.RangePosition = { 10.0f, 10.0f, 10.0f };

	Setter.StandardScale = { 45.0f, 45.0f, 45.0f };
	Setter.RangeScale = { 4.5f, 4.5f, 4.5f };
	
	Setter.StandardDir = { 0.0f, 0.0f, 0.0f };
	Setter.RangeDir = { 1.0f, 1.0f, 0.0f};

	Setter.StandardSpeed = 10.0f;
	Setter.range_Speed = 1.0f;

	Setter.EmitInterTime = 0.5f;
	Setter.MaxLiveTime = 1.0f;
	Setter.MaxParticle = 30;

	Setter.EmitNum = 4;

	New->SetPaticleSetter(Setter);
	//New->SetDisposable();
	New->ParticleOn();
}

void MyTest::Update(float _Delta)
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

	//float4 Rot = GetTransform()->GetLocalRotation();
	//float4 Rot1 = New->GetTransform()->GetWorldRotation();

	//if (GameEngineInput::IsDown("MyTest") == true)
	//{
	//	UpdateFunc = &ContentSoundPlayer::BGMChangeLerp;
	//}
	//
	//if (UpdateFunc != nullptr && UpdateFunc("BeginnersTown.mp3", 2.0f, _Delta) == true)
	//{
	//	UpdateFunc = nullptr;
	//}
}

void MyTest::CreateKey()
{
	if (GameEngineInput::IsKey("MyTest") == false)
	{
		GameEngineInput::CreateKey("MyTest", 'A');
	}
}