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
	Unit->SetMaterial("Water", RenderPath::Custom01);
	Unit->ShaderResHelper.SetTexture("NormalMap", "WaterNormal.png");
	Unit->Color.MulColor = float4::ZERONULL;
	Unit->Color.PlusColor = float4{ 0.0f, 0.9f, 0.5f, 1.0f };
}

void WaterBox::SetWaterPosition(float4 _Pos)
{
	GetTransform()->SetLocalPosition(_Pos);
	GetLevel()->SetWaterHeight(_Pos.y);

	Height = _Pos.y;
}

void WaterBox::Update(float _Delta)
{
	float4 Scale = GetTransform()->GetLocalScale();
	
	//Unit->UVdata.x = Scale.x  / 4096.0f;
	//Unit->UVdata.y = Scale.z / 4096.0f;
	Unit->UVdata.x = Scale.x / (Scale.x * 4096.0f / 15000.0f);
	Unit->UVdata.y = Scale.z / (Scale.z * 4096.0f / 15000.0f);

	//Angle += 30.0f * _Delta;
	//float RadAngle = Angle * GameEngineMath::DegToRad;

	//float Y = Height + 15.0f * sin(RadAngle);
	//
	//float4 Position = GetTransform()->GetLocalPosition();
	//GetTransform()->SetLocalPosition({ Position.x, Y,Position.z });
	//GetLevel()->SetWaterHeight(Y);

	Unit->UVdata.z += 0.01f * _Delta;
	Unit->UVdata.w += 0.01f * _Delta;

	if (Unit->UVdata.z >= 1.0f)
	{
		Unit->UVdata.z -= 1.0f;
		Unit->UVdata.w -= 1.0f;
	}
}
