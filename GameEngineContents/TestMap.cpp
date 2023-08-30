#include "PrecompileHeader.h"
#include "TestMap.h"


TestMap::TestMap()
{
}

TestMap::~TestMap()
{
}

void TestMap::Start()
{
	std::shared_ptr<GameEngineFBXRenderer> Renderer = CreateComponent<GameEngineFBXRenderer>();
	Renderer->SetFBXMesh("Cube14.fbx", "MeshTexture");

	int a = 0;
}

void TestMap::Update(float _DeltaTime)
{
}
