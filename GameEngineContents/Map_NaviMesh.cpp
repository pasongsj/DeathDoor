#include "PrecompileHeader.h"
#include "Map_NaviMesh.h"

#include "PhysXTriangleComponent.h"
#include "PhysXControllerComponent.h"
#include "Player.h"

Map_NaviMesh::Map_NaviMesh() 
{
}

Map_NaviMesh::~Map_NaviMesh() 
{
}

void Map_NaviMesh::Start()
{
	m_pNaviComp = CreateComponent<PhysXTriangleComponent>();
	m_pNaviComp->SetPhysxMaterial(0.f, 0.f, 0.f);
	m_pNaviComp->CreatePhysXActors("Fortress_Navi_DC.fbx", true);
	m_pNaviComp->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(float4{ 0 , -135, 0 }, float4::ZERO));
	m_pNaviComp->SetNavigation();
}

std::deque<sTriangle> Road;
float fTime;
void Map_NaviMesh::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("E"))
	{
		Player::MainPlayer->GetPhysXComponent()->TurnOffGravity();
		m_pNaviComp->FindRoad(Player::MainPlayer->GetTransform()->GetWorldPosition(), float4{ -1084 , 146, 5294 });
		m_pNaviComp->GetRoad(Road);
	}
	if (Road.empty() != true)
	{
		fTime += _DeltaTime * 10.f;

		sTriangle Test = Road.front();
		float4 Lerp = float4::LerpClamp(Player::MainPlayer->GetPhysXComponent()->GetWorldPosition(), Test.CenterPos, fTime);
		Player::MainPlayer->GetPhysXComponent()->SetWorldPosWithParent(Lerp);

		if (fTime >= 1.f)
		{
			Road.pop_front();
			fTime -= 1.f;
		}
	}
	else
	{
		Player::MainPlayer->GetPhysXComponent()->TurnOnGravity();
	}
}

