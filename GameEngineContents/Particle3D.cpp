#include "PrecompileHeader.h"
#include "Particle3D.h"

Particle3D::Particle3D()
{
}

Particle3D::~Particle3D()
{
}

void Particle3D::Start()
{
	PushCameraRender(0);

	SetFBXMesh("ParticleMesh.fbx", "Particle3D", RenderPath::Alpha);
}

void Particle3D::Update(float _Delta)
{
	GameEngineFBXRenderer::Update(_Delta);

	if (isAutoMove == true)
	{
		AutoMove(_Delta);
	}
	else if (isAutoMoveLerp == true)
	{
		AutoMoveLerp(_Delta);
	}

	if (isScaleDecrease == true)
	{
		ScaleDecrease(_Delta);
	}
	else if (isScaleDecreaseLerp == true)
	{
		ScaleDecreaseLerp(_Delta);
	}
}

void Particle3D::AutoMove(float _Delta)
{
	if(isLocalMove == false)
	{
		GetTransform()->AddWorldPosition(MoveDir * MoveSpeed * _Delta);
	}
	else
	{
		GetTransform()->AddLocalPosition(MoveDir * MoveSpeed * _Delta);
	}
}

void Particle3D::AutoMoveLerp(float _Delta)
{
	if (PosLerpRatio >= 1.0f)
	{
		Death();
	}

	float4 Pos = float4::Lerp(LerpStartPos, LerpEndPos, PosLerpRatio);
	
	if(isLocalMove == false)
	{
		GetTransform()->SetWorldPosition(Pos);
	}
	else
	{
		GetTransform()->SetLocalPosition(Pos);
	}

	PosLerpRatio += PosLerpSpeed * _Delta;
}

void Particle3D::ScaleDecrease(float _Delta)
{
	if (StartYScale.y <= 0.0f)
	{
		Death();
	}

	GetTransform()->SetLocalScale(StartYScale);
	StartYScale.y -= DecreaseSpeed * _Delta;
}

void Particle3D::ScaleDecreaseLerp(float _Delta)
{
	if (ScaleLerpRatio >= 1.0f)
	{
		Death();
	}

	float4 Scale = float4::Lerp(LerpStartScale, LerpEndScale, ScaleLerpRatio);
	GetTransform()->SetLocalScale(Scale);
	ScaleLerpRatio += ScaleLerpSpeed * _Delta;
}