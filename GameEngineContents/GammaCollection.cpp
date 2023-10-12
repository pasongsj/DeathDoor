#include "PrecompileHeader.h"
#include "GammaCollection.h"

GammaCollection::GammaCollection()
{
}

GammaCollection::~GammaCollection()
{
}

void GammaCollection::Start(GameEngineRenderTarget* _Target)
{
	GammaCollectionUnit.SetMesh("FullRect");
	GammaCollectionUnit.SetMaterial("GammaCollection");

	GammaCollectionTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::ZERONULL);

	MergeUnit.SetMesh("FullRect");
	MergeUnit.SetMaterial("Merge");
}

void GammaCollection::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	GammaCollectionTarget->Clear();
	GammaCollectionTarget->Setting();

	GammaCollectionUnit.ShaderResHelper.SetTexture("ScreenTexture", _Target->GetTexture(0));
	GammaCollectionUnit.Render(0.0f);
	GammaCollectionUnit.ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Setting();

	MergeUnit.ShaderResHelper.SetTexture("DiffuseTex", GammaCollectionTarget->GetTexture(0));
	MergeUnit.Render(0.0f);
	MergeUnit.ShaderResHelper.AllResourcesReset();

}
