#include "PrecompileHeader.h"
#include "SinkBox_4x4.h"

SinkBox_4x4::SinkBox_4x4()
{
}

SinkBox_4x4::~SinkBox_4x4()
{
}

void SinkBox_4x4::Start()
{
	std::shared_ptr<GameEngineFBXRenderer> NewRenderer = CreateComponent<GameEngineFBXRenderer>();
	NewRenderer->SetFBXMesh("SinkBox_4x4.fbx", "MeshTexture");
}