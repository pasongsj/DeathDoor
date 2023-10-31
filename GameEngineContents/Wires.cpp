#include "PrecompileHeader.h"
#include "Wires.h"

#include "ContentFBXRenderer.h"


Wires::Wires()
{
}

Wires::~Wires()
{
}

void Wires::Start()
{
	InitComponent();
}

void Wires::Update(float _DeltaTime)
{
}

void Wires::InitComponent()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("Wires.fbx", "ContentMeshDeffered");
}
