#include "PrecompileHeader.h"
#include "ParticleRenderer.h"

ParticleRenderer::ParticleRenderer()
{
}

ParticleRenderer::~ParticleRenderer()
{
}

void ParticleRenderer::ParticlePosUpdate(float _Delta)
{
	GetTransform()->AddLocalPosition(Dir * Speed * _Delta);
}
