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
	Unit->ShaderResHelper.SetConstantBufferLink("CamPos", CamPos);

	Unit->Color.MulColor = float4::ZERONULL;
	Unit->Color.PlusColor = float4{ 0.0f, 0.5f, 1.0f, 0.8f };

	GetTransform()->SetLocalPosition({ -5000, -120 ,4500 });
	GetTransform()->SetLocalScale({ 15000 , 1 , 15000 });
	GetTransform()->SetLocalRotation({ 0 , 45.0f , 0 });

	Unit->UVdata = { 15000.0f / 4096.0f, 15000.0f / 4096.0f};

	GetLevel()->SetWaterHeight(-120.0f);
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

	CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
}
