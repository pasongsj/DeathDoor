#include "PrecompileHeader.h"
#include "ShockWave.h"

ShockWave::ShockWave()
{
}

ShockWave::~ShockWave()
{
}

void ShockWave::Start()
{
	GameEngineRenderer::Start();

	Unit = CreateRenderUnit();
	Unit->SetMesh("Rect");
	Unit->SetMaterial("Content2DTexture", RenderPath::Alpha);
	Unit->ShaderResHelper.SetTexture("DiffuseTex", "ShockWave_1.png");
}

void ShockWave::Update(float _Delta)
{
	GetTransform()->AddLocalScale(float4::ONE * 10000.0f * _Delta);

	if (GetLiveTime() >= 2.0f)
	{
		Death();
	}
}
