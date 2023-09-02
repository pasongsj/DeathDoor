#include "PrecompileHeader.h"
#include "Mouse.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{
	ShowCursor(false);

	MouseCursor = CreateComponent<GameEngineFBXRenderer>();
	MouseCursor->SetFBXMesh("Mouse.FBX", "ContentMesh");
	MouseCursor->GetTransform()->SetLocalScale({ 50, 50, 50 });

}

void Mouse::Update(float _DeltaTime)
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
	float4 ViewRayDir = DirectX::XMVector3TransformNormal(RayDir, ViewInverse);
		
	RayDir.Normalize();
	
	float4 RayDest = RayPos;
	
	//Z값은 나중에 캐릭터의 Z값으로 변환해야함.
	while (true)
	{
		RayDest += ViewRayDir;

		if (RayDest.z >= 0.0f)
		{
			break;
		}
	}

	//여기도 캐릭터의 Z값으로
	RayDest.z = 0.0f;

	MouseCursor->GetTransform()->SetWorldPosition(RayDest);

	//현재는 0,0을 중심으로 연산했으나, 추후 캐릭터의 위치로 연산해야함.

	/*

	float4 PlayerPos;
	float4 MouseDir = RayDest - PlayPos;
	float4 NomalizedMouseDir = MouseDir.NormalizeReturn();

	float Xangle = acos(NomalizedMouseDir.x);
	Xangle *= 180.0f / GameEngineMath::PIE;

	if (NmRayDest.y >= 0.0f)
	{
		Xangle *= -1.0f;
	}

	*/
	float4 NmRayDest = RayDest.NormalizeReturn();

	float Xangle = acos(NmRayDest.x);
	Xangle *= 180.0f / GameEngineMath::PIE;

	if (NmRayDest.y >= 0.0f)
	{
		Xangle *= -1.0f;
	}

	MouseCursor->GetTransform()->SetLocalRotation({0.0f, Xangle - 90.0f, 0.0f });

	//MouseCursor->GetTransform()->SetLocalPosition({ MousePos.x - WindowSize.hx(), WindowSize.hy() - MousePos.y });
	//MouseCursor->GetTransform()->SetLocalPosition(WorldMouse);
	//MousePos = float4{ MousePos.x - WindowSize.hx(), WindowSize.hy() - MousePos.y };
	//
	//MousePos *= GetLevel()->GetMainCamera()->GetViewPort().InverseReturn();
	//MousePos *= GetLevel()->GetMainCamera()->GetProjection().InverseReturn();
	//MousePos *= GetLevel()->GetMainCamera()->GetView().InverseReturn();
	
	//CursorCollision->GetTransform()->SetWorldPosition(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition() + float4{ -8, 10 } + MousePos);
}

void Mouse::Render(float _DeltaTime)
{
}
