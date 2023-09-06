#include "PrecompileHeader.h"
#include "Mouse.h"
#include "ContentFBXUIRenderer.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{
	ShowCursor(false);

	MousePivot = CreateComponent<GameEngineComponent>();
	MousePivot->GetTransform()->SetLocalRotation({ 90.0f, 0.0f, 0.0f });

	MouseCursor = CreateComponent<ContentFBXUIRenderer>();
	MouseCursor->SetFBXMesh("Mouse.FBX", "ContentMesh");
	MouseCursor->GetTransform()->SetLocalScale({ 30, 30, 30 });
	MouseCursor->GetTransform()->SetParent(MousePivot->GetTransform());

	auto Units = MouseCursor->GetAllRenderUnit();

	for (int i = 0; i < Units.size(); i++)
	{
		for (int j = 0; j < Units[i].size(); j++)
		{
			Units[i][j]->ShaderResHelper.SetTexture("DiffuseTexture", "WhiteTexture.png");
		}
	}
}

void Mouse::Update(float _DeltaTime)
{
	RayCasting();
	MouseRotationUpdate();
}

void Mouse::Render(float _DeltaTime)
{
}

void Mouse::RayCasting()
{
	if (Count == 0)
	{
		Count++;
		return;
	}

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
}

void Mouse::MouseRotationUpdate()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	float4 ScreenMousePos = GameEngineWindow::GetMousePosition();
	float4 DecartMousePos = { ScreenMousePos.x - ScreenSize.hx(), ScreenSize.hy() - ScreenMousePos.y };

	MouseCursor->GetTransform()->SetLocalPosition({DecartMousePos.x, 0.0f, -DecartMousePos.y});

	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetMainCamera();

	Camera->CameraTransformUpdate();
	
	float4x4 ViewMat = Camera->GetView();
	float4x4 ProjMat = Camera->GetProjection();
	float4x4 ViewPortMat = Camera->GetViewPort();

	float4 PlayerPos = { 100, 0, 0 };	
	
	PlayerPos *= ViewMat;

	PlayerPos.x /= 800.0f;
	PlayerPos.y /= 450.0f;
	PlayerPos.z /= Camera->GetTransform()->GetWorldPosition().z;

	float4 PlayerProj = PlayerPos * ProjMat;
	float4 PlayerViewPort = PlayerProj * ViewPortMat;

	float4 DecartViewPortPos = { PlayerViewPort.x - ScreenSize.hx(), ScreenSize.hy() - PlayerViewPort.y };
	float4 PlayerToMouseDir = DecartMousePos - DecartViewPortPos;

	PlayerToMouseDir.Normalize();

	float Cos_ZRotAngle = PlayerToMouseDir.x;
	float ZRotAngle = acos(Cos_ZRotAngle);

	ZRotAngle *= 180.0f / GameEngineMath::PIE;

	MouseCursor->GetTransform()->SetLocalRotation({ 0.0f , ZRotAngle, 0.0f });

	float4 worldrot1 = MouseCursor->GetTransform()->GetLocalRotation();
}