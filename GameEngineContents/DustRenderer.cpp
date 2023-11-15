#include "PrecompileHeader.h"
#include "DustRenderer.h"

DustRenderer::DustRenderer()
{
}

DustRenderer::~DustRenderer()
{
}

void DustRenderer::Start()
{
	PushCameraRender(-1);

	Unit = CreateRenderUnit();
	Unit->SetMesh("Rect");
	Unit->SetMaterial("Dust");

	Unit->ShaderResHelper.SetTexture("DustNoise", "DustBGNoise.png");
	Unit->ShaderResHelper.SetConstantBufferLink("ScaleBuffer", ScaleBuffer);
	Unit->ShaderResHelper.SetConstantBufferLink("Delta", Delta);
}

void DustRenderer::Update(float _DeltaTime)
{

}
