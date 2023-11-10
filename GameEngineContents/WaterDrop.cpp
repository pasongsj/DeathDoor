#include "PrecompileHeader.h"
#include "WaterDrop.h"

WaterDrop::WaterDrop()
{
}

WaterDrop::~WaterDrop()
{
}

void WaterDrop::Start()
{
	PushCameraRender(0);
	SetFBXMesh("Sphere.fbx", "waterDrop", RenderPath::Alpha);

	auto Units = GetAllRenderUnit();

	for (int i = 0; i < Units.size(); i++)
	{
		for (int j = 0; j < Units[i].size(); j++)
		{
			Units[i][j]->ShaderResHelper.SetTexture("DiffuseTexture", "WaterDropColor.png");
		}
	}
}

void WaterDrop::Update(float _Delta)
{
	if (UpdateFunc != nullptr)
	{
		UpdateFunc(*this, _Delta);
	}
}

void WaterDrop::MoveToParabola(float _Delta)
{
	GetTransform()->AddWorldPosition(Dir * Speed * _Delta + float4{0.0f, -Gravity * _Delta, 0.0f});
	Gravity += 600.0f * _Delta;
}

void WaterDrop::VerticalDrop(float _Delta)
{
	GetTransform()->AddWorldPosition({ 0.0f, -Gravity * _Delta, 0.0f });
}
