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
	NewRenderer = CreateComponent<GameEngineFBXRenderer>();
	NewRenderer->SetFBXMesh("SinkBox_8x8.fbx", "MeshTexture");
}

void SinkBox_8x8::Update(float _Deltatime)
{
	float4 Pos = NewRenderer->GetTransform()->GetWorldScale();
	
	int a = 0;
}
