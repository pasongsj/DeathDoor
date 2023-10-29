#include "PrecompileHeader.h"
#include "SwordTrailRenderer.h"

SwordTrailRenderer::SwordTrailRenderer()
{
}

SwordTrailRenderer::~SwordTrailRenderer()
{
}

void SwordTrailRenderer::Start()
{
	PushCameraRender(0);
}

void SwordTrailRenderer::SetFBXMesh(const std::string& _MeshName, const std::string _SettingName, bool _isRight)
{
	GameEngineFBXRenderer::SetFBXMesh(_MeshName, "SwordTrailShader");

	auto Units = GetAllRenderUnit();

	for (int i = 0; i < Units.size(); i++)
	{
		for (int j = 0; j < Units[i].size(); j++)
		{
			Units[i][j]->ShaderResHelper.SetTexture("DiffuseTexture", "SwordTrail.png");
			
			if(_isRight == true)
			{
				Units[i][j]->ShaderResHelper.SetTexture("MaskTexture", "SwordTrailMask.png");
			}
			else
			{
				Units[i][j]->ShaderResHelper.SetTexture("MaskTexture", "SwordTrailReverseMask.png");
			}

			Units[i][j]->ShaderResHelper.SetConstantBufferLink("ClipData", ClipData);
		}
	}
}
