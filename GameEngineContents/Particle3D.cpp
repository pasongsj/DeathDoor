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

	if (isScaleDecrease == true)
	{
		ScaleDecrease(_Delta);
	}
}

void Particle3D::AutoMove(float _Delta)
{
	GetTransform()->AddWorldPosition(MoveDir * MoveSpeed * _Delta);
}

void Particle3D::ScaleDecrease(float _Delta)
{
	if (StartYScale <= 0.0f)
	{
		return;
	}

	GetTransform()->SetLocalScale({ 1.0f, StartYScale, 1.0f });
	StartYScale -= DecreaseSpeed * _Delta;
}