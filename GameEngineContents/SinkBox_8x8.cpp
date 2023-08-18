#include "PrecompileHeader.h"
#include "SinkBox_8x8.h"

SinkBox_8x8::SinkBox_8x8()
{
}

SinkBox_8x8::~SinkBox_8x8()
{
}

void SinkBox_8x8::Start()
{
	std::shared_ptr<GameEngineFBXRenderer> NewRenderer = CreateComponent<GameEngineFBXRenderer>();
	NewRenderer->SetFBXMesh("SinkBox_8x8.fbx", "MeshTexture");	
}