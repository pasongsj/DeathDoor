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
	Unit->SetMaterial("ContentMeshDeffered");
	//Unit->SetWaterUnit();

	Unit->ShaderResHelper.SetConstantBufferLink("BlurColor", BlurColor);
	Unit->ShaderResHelper.SetConstantBufferLink("ClipData", ClipData);
	Unit->Color.MulColor = float4::ZERONULL;
	Unit->Color.PlusColor = float4{0.0f, 0.0f, 1.0f, 0.2f};

	GetTransform()->SetLocalPosition({ -5000, -50 ,4500 });
	GetTransform()->SetLocalScale({ 15000 , 1 , 15000});
	GetTransform()->SetLocalRotation({ 0 , 45.0f , 0});

	GetLevel()->GetMainCamera()->SetWaterHeight(-50.0f);
}

void WaterBox::Update(float _Delta)
{
}
