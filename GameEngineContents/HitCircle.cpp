#include "PrecompileHeader.h"
#include "HitCircle.h"

HitCircle::HitCircle()
{
}

HitCircle::~HitCircle()
{
}

void HitCircle::Start()
{
	ParticleBase::Start();

	Unit = CreateRenderUnit();
	Unit->SetMesh("Rect");
	Unit->SetMaterial("HitCircle", RenderPath::Alpha);

	Unit->ShaderResHelper.SetTexture("DiffuseTexture", "HitCircle.png");

	GetTransform()->SetLocalScale({2.0f, 2.0f, 2.0f });
}

void HitCircle::Update(float _Delta)
{
	BillBoarding();

	if (GetLiveTime() >= 0.4f)
	{
		Death();
	}
}
