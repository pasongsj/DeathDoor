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
	//ShowCursor(false);

	MouseCursor = CreateComponent<GameEngineFBXRenderer>();
	MouseCursor->SetFBXMesh("Mouse.FBX", "ContentMesh");
	MouseCursor->GetTransform()->SetLocalScale({ 5, 5, 5 });

	std::shared_ptr<GameEngineFBXRenderer> New = CreateComponent<GameEngineFBXRenderer>();
	New->SetFBXMesh("Hall_Crow_3.FBX", "ContentMesh");
}

void Mouse::Update(float _DeltaTime)
{
	float4 WindowSize = GameEngineWindow::GetScreenSize();
	float4 MousePos = GameEngineWindow::GetMousePosition();
	MousePos = float4{ MousePos.x - WindowSize.hx(), WindowSize.hy() - MousePos.y };

	DirectX::XMFLOAT3 unprojected;
	DirectX::XMMATRIX invViewProj = DirectX::XMMatrixInverse(nullptr, GetLevel()->GetMainCamera()->GetView() * GetLevel()->GetMainCamera()->GetProjection());
	DirectX::XMFLOAT3 screenPos = DirectX::XMFLOAT3(MousePos.x, MousePos.y, 0.0f);
	DirectX::XMStoreFloat3(&unprojected, XMVector3TransformCoord(XMLoadFloat3(&screenPos), invViewProj));

	float4 Pos_3d = { unprojected.x, unprojected.y, unprojected.z };
	MouseCursor->GetTransform()->SetLocalPosition(Pos_3d);
	
	//CursorCollision->GetTransform()->SetWorldPosition(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition() + float4{ -8, 10 } + MousePos);
}

void Mouse::Render(float _DeltaTime)
{
}
