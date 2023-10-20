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
	//Unit->SetWaterUnit();

	Unit->ShaderResHelper.SetTexture("NormalMap", "WaterNormal.png");

	Unit->Color.MulColor = float4::ZERONULL;
	Unit->Color.PlusColor = float4{ 0.0f, 0.5f, 1.0f, 0.2f };

	GetTransform()->SetLocalPosition({ -5000, -100 ,4500 });
	GetTransform()->SetLocalScale({ 15000 , 1 , 15000 });
	GetTransform()->SetLocalRotation({ 0 , 45.0f , 0 });

	Unit->UVdata = { 15000.0f / 1024.0f, 15000.0f / 1024.0f };

	GetLevel()->GetMainCamera()->SetWaterHeight(-100.0f);
}

void WaterBox::Update(float _Delta)
{
	Unit->UVdata.z += 0.03f * _Delta;
	Unit->UVdata.w += 0.03f * _Delta;

	if (Unit->UVdata.z >= 1.0f)
	{
		Unit->UVdata.z -= 1.0f;
		Unit->UVdata.w -= 1.0f;
	}
}
