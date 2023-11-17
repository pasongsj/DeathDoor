#include "PrecompileHeader.h"
#include "Mouse.h"
#include "ContentFBXUIRenderer.h"
#include "ContentFBXRenderer.h"
#include "Player.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{
#ifdef _DEBUG
#else
	ShowCursor(false);
#endif
	MousePivot = CreateComponent<GameEngineComponent>();
	MousePivot->GetTransform()->SetLocalRotation({ 90.0f, 0.0f, 0.0f });

	Ray = CreateComponent<GameEngineCollision>();
	Ray->GetTransform()->SetLocalPosition({ 0, 0 });
	Ray->GetTransform()->SetLocalScale({ 10.0f, 10.0f, 10.0f });
	Ray->SetColType(ColType::AABBBOX3D);
	Ray->SetOrder(2);

	MouseCursor = CreateComponent<ContentFBXUIRenderer>();
	MouseCursor->SetFBXMesh("Mouse.FBX", "ContentMeshUI");
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
	//RayCasting();
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

	//if (GameEngineInput::IsDown("Click") == false)
	//{
	//	return;
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


	int count = 0;

	//아무리 멀어도 카메라와의 거리는 2000보다 가까울 것이라고 가정
	while (count < 2000)
	{
		RayDest += WorldRayDir;

		Ray->GetTransform()->SetLocalPosition(RayDest);

		//대상에 충돌했는가

		//아예 길이가 1000짜리 회전한 박스 OBB를 만들어서, 충돌검사를 1000단위로 하는게 나을 수도
		//AABB 2천번보다는 OBB 2번이 빠르겠지
		if (Ray->Collision(1, ColType::AABBBOX3D, ColType::AABBBOX3D) != nullptr)
		{
			break;
		}

		count++;
	}
}

void Mouse::MouseRotationUpdate()
{
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 ScreenMousePos = GameEngineWindow::GetMousePosition();

	float4 DecartMousePos = { ScreenMousePos.x - ScreenSize.hx(), ScreenSize.hy() - ScreenMousePos.y };

	MouseCursor->GetTransform()->SetLocalPosition({DecartMousePos.x, 0.0f, -DecartMousePos.y});

	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetMainCamera();
	Camera->CameraTransformUpdate();
	
	float4x4 ViewMat = Camera->GetView();
	float4x4 ProjMat = Camera->GetProjection();
	float4x4 ViewPortMat = Camera->GetViewPort();
	float4x4 ViewProjViewPort = ViewMat * ProjMat * ViewPortMat;

	float4 PlayerScreenPos = PlayerPos * ViewProjViewPort;
	PlayerScreenPos /= PlayerScreenPos.w;
	PlayerScreenPos.w = 1.0f;

	float4 PlayerDecartPos = { PlayerScreenPos.x - ScreenSize.hx(), ScreenSize.hy() - PlayerScreenPos.y };
	float4 PlayerToMouseDir = DecartMousePos - PlayerDecartPos;
	PlayerToMouseDir.z = 0;
	PlayerToMouseDir.RotationAllDeg(Camera->GetTransform()->GetWorldRotation());
	PlayerToMouseDir.Normalize();

	float Cos_ZRotAngle = PlayerToMouseDir.x;
	float ZRotAngle = acos(Cos_ZRotAngle);

	ZRotAngle *= 180.0f / GameEngineMath::PIE;

	if (PlayerToMouseDir.y <= 0.0f)
	{
		ZRotAngle *= -1.0f;
	}

	MouseCursor->GetTransform()->SetLocalRotation({ 0.0f , ZRotAngle, 0.0f });

	float4 worldrot1 = MouseCursor->GetTransform()->GetLocalRotation();
}