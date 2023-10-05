#include "PrecompileHeader.h"
#include "Map_Sanctuary.h"

#include "Player.h"

#include "ContentFBXRenderer.h"

// physX
#include "PhysXTriangleComponent.h"
#include "PhysXBoxComponent.h"
#include "PhysXCapsuleComponent.h"

#include "SecretTile.h"

Map_Sanctuary::Map_Sanctuary()
{
}

Map_Sanctuary::~Map_Sanctuary()
{
}

void Map_Sanctuary::NaviRenderSwitch()
{
	if (nullptr != m_pNaviRenderer)
	{
		if (true == m_pNaviRenderer->IsUpdate())
		{
			m_pNaviRenderer->Off();
		}
		else
		{
			m_pNaviRenderer->On();
		}
	}
}

void Map_Sanctuary::Start()
{
	// 컴포넌트 초기화 
	InitComponent();
}

void Map_Sanctuary::Update(float _DeltaTime)
{
}

void Map_Sanctuary::InitComponent()
{
	m_pRenderer = CreateComponent<ContentFBXRenderer>();
	m_pRenderer->SetFBXMesh("Map_Sanctuary.fbx", "ContentMeshDeffered");


	// test 
	auto AllUnit = m_pRenderer->GetAllRenderUnit();
	auto Unit = m_pRenderer->GetUnTexturedUnit();

	int a = 0; 
}

void Map_Sanctuary::Create_PhysXComponent()
{
}
