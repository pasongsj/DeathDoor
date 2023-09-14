#include "PrecompileHeader.h"
#include "MyTest.h"

#include "StaticParticleManager.h"

MyTest::MyTest()
{
}

MyTest::~MyTest()
{
}

void MyTest::Start()
{
	//TestRd0 = CreateComponent<GameEngineFBXRenderer>();
	//TestRd0->SetFBXMesh("Sphere.fbx", "CircleFade");
	//TestRd0->GetTransform()->SetLocalScale({ 600.0f, 600.0f, 600.0f });
	//
	//auto Units = TestRd0->GetAllRenderUnit();
	//
	//
	//for (int i = 0; i < Units.size(); i++)
	//{
	//	for (int j = 0; j < Units[i].size(); j++)
	//	{
	//		Units[i][j]->ShaderResHelper.SetTexture("DiffuseTexture", "CenterLevelBG.png");
	//		Units[i][j]->CircleFade = { 820.0f, 450.0f, 0.0f, 100.0f };
	//	}
	//}


	int a = 0;
	std::shared_ptr<StaticParticleManager> New  = GetLevel()->CreateActor<StaticParticleManager>();
	
	StaticParticleSetter Setter;
	
	New->SetMeshName("Sphere.fbx");
	
	Setter.StandardPosition = {0.0f, 0.0f, 0.0f};
	Setter.RangePosition = { 4.0f, 4.0f, 4.0f };
	
	Setter.StandardScale = {50.0f, 50.0f, 50.0f };
	Setter.RangeScale = { 5.0f, 5.0f, 5.0f };
	
	Setter.StandardDir = { 0.0f, 0.0f, 0.0f };
	Setter.RangeDir = { 1.0f, 1.0f, 0.0f};
	
	Setter.StandardSpeed = 30.0f;
	Setter.range_Speed = 5.0f;
	
	Setter.EmitInterTime = 0.1f;
	Setter.MaxLiveTime = 1.5f;
	Setter.MaxParticle = 30;
	
	Setter.EmitNum = 3;
	
	New->SetPaticleSetter(Setter);
	//New->SetDisposable();
	New->ParticleOn();

}

void MyTest::Update(float _Delta)
{
	//float4 PointPos = { 10.0f, 0.0f, 0.0f };
	//
	//std::shared_ptr<GameEngineCamera> Cam = GetLevel()->GetMainCamera();
	//
	//float4 PointVPPos = PointPos * Cam->GetView() * Cam->GetProjection();
	//PointVPPos *= GetLevel()->GetMainCamera()->GetViewPort();
	//PointVPPos /= PointVPPos.w;
	//PointVPPos.w = 1.0f;
	//
	//auto Units = TestRd0->GetAllRenderUnit();
	//
	//for (int i = 0; i < Units.size(); i++)
	//{
	//	for (int j = 0; j < Units[i].size(); j++)
	//	{
	//		//Units[i][j]->CircleFade.X -= 5.0f * _Delta;
	//		//Units[i][j]->CircleFade.Y -= 5.0f * _Delta;
	//		//
	//		//Units[i][j]->CircleFade.Distance += 50.0f * _Delta;
	//	}
	//}
	

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

void MyTest::TestRender()
{
	//Target1 에 멀쩡하게 그리기
	//Target2의 텍스쳐를 Target1로 설정 후 RenderUnit에 Blur처리하기.
	//두개를 머지하면?
	//근데 이러면 드로우콜이 3번인데?

	//애초에 Target1에서, 멀쩡한거를 1번 Texture에 
	//Blur된거를 2번 텍스쳐에 그리고
	//두개를 머지하기.
}

void MyTest::CreateKey()
{
	if (GameEngineInput::IsKey("MyTest") == false)
	{
		GameEngineInput::CreateKey("MyTest", 'A');
	}
}