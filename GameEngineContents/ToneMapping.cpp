#include "PrecompileHeader.h"
#include "ToneMapping.h"

ToneMapping::ToneMapping()
{
}

ToneMapping::~ToneMapping()
{
}

void ToneMapping::Start(GameEngineRenderTarget* _Target)
{
	ToneMappingTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);

	ToneMappingUnit.SetMesh("FullRect");
	ToneMappingUnit.SetMaterial("ToneMapping");
}

void ToneMapping::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	ToneMappingTarget->Clear();
	ToneMappingTarget->Setting();

	ToneMappingUnit.ShaderResHelper.SetTexture("DiffuseTexture", _Target->GetTexture(0));
	ToneMappingUnit.Render(_DeltaTime);
	ToneMappingUnit.ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Merge(ToneMappingTarget);
}
