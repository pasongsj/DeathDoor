#include "PrecompileHeader.h"
#include "WaterBox.h"
#include "Player.h"

WaterBox::WaterBox()
{
}

WaterBox::~WaterBox()
{
}

void WaterBox::Start()
{
	PushCameraRender(0);

	Unit = CreateRenderUnit();
	Unit->SetMesh("Box");
	Unit->SetMaterial("Water");
	Unit->ShaderResHelper.SetTexture("NormalMap", "WaterNormal.png");
	Unit->Color.MulColor = float4::ZERONULL;
	Unit->Color.PlusColor = float4{ 0.0f, 0.5f, 1.0f, 0.8f };
}

void WaterBox::Update(float _Delta)
{
	float4 Scale = GetTransform()->GetLocalScale();
	float4 Position = GetTransform()->GetLocalPosition();

	Unit->UVdata.x = Scale.x / 4096.0f;
	Unit->UVdata.y = Scale.z / 4096.0f;

	GetLevel()->SetWaterHeight(Position.y);

	Unit->UVdata.z += 0.01f * _Delta;
	Unit->UVdata.w += 0.01f * _Delta;

	if (Unit->UVdata.z >= 1.0f)
	{
		Unit->UVdata.z -= 1.0f;
		Unit->UVdata.w -= 1.0f;
	}
}
