#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include "PhysXDefault.h"
struct sTriangle
{
    UINT ID = -1;
	UINT NearID[3];
	float4 CenterPos = float4::ZERONULL;
	float Cost = -1;
	float Heuristic = -1;
	float Value = -1;
	bool Visit = false;

	struct compare
	{
		bool operator()(sTriangle a, sTriangle b);
	};
};


// 설명 :
class PhysXTriangleComponent : public GameEngineComponent, public PhysXDefault
{
	friend class compare;

public:
	// constrcuter destructer
	PhysXTriangleComponent();
	~PhysXTriangleComponent();

	// delete Function
	PhysXTriangleComponent(const PhysXTriangleComponent& _Other) = delete;
	PhysXTriangleComponent(PhysXTriangleComponent&& _Other) noexcept = delete;
	PhysXTriangleComponent& operator=(const PhysXTriangleComponent& _Other) = delete;
	PhysXTriangleComponent& operator=(PhysXTriangleComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(const std::string& _MeshName,bool _InverseIndex = true, float _Ratio = 1.f, float4 _GeoMetryRot = { 0.0f, 0.0f });
	physx::PxTriangleMesh* GetTriMesh()
	{
		return TriMesh;
	}
	void SetNavigation()
	{
		SetFilterData(PhysXFilterGroup::NaviMesh);
		UINT iTriangleSize = TriMesh->getNbTriangles();
		for (UINT i = 0; i < iTriangleSize; i++)
		{
			sTriangle Temp;
			Temp.ID = i;
			Temp.NearID;
			physx::PxTriangle TriangleTemp;
			physx::PxU32 VertexIndex[3];
			physx::PxMeshQuery::getTriangle(TriMesh, m_pRigidStatic->getGlobalPose(), i, TriangleTemp, VertexIndex, Temp.NearID);
			float4 Vertex0 = float4(TriangleTemp.verts[0].x, TriangleTemp.verts[0].y, TriangleTemp.verts[0].z);
			float4 Vertex1 = float4(TriangleTemp.verts[1].x, TriangleTemp.verts[1].y, TriangleTemp.verts[1].z);
			float4 Vertex2 = float4(TriangleTemp.verts[2].x, TriangleTemp.verts[2].y, TriangleTemp.verts[2].z);
			float4 Result = float4(
				((Vertex0.x + Vertex1.x + Vertex2.x) / 3.f),
				((Vertex0.y + Vertex1.y + Vertex2.y) / 3.f),
				((Vertex0.z + Vertex1.z + Vertex2.z) / 3.f));
			Temp.CenterPos = Result;
			vec_TriangleNav.push_back(Temp);
		}
		int a = 0;
	}
	bool FindRoad(float4 _Start, float4 _End);

	float4 FindRoadDir(float4 _Start, float4 _End)
	{
		bool bCheck = FindRoad(_Start, _End);
		if (false == bCheck)
		{
			return float4::ZERONULL;
		}
		if (dq_ResultRoad.empty())
		{
			return float4::ZERONULL;
		}
		float4 Front = dq_ResultRoad.back().CenterPos;
		Front.y = 0;
		float4 Start = _Start;
		Start.y = 0;

		float4 Result = (Front - Start).NormalizeReturn();
		return Result;
	}
	float4 FindRoadPos()
	{
		return dq_ResultRoad.front().CenterPos;
	}

	void GetRoad(std::deque<sTriangle>& _Deque)
	{
		_Deque = dq_ResultRoad;
	}
	
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void CustomFBXLoad(const std::string& _MeshName,float _Ratio, bool _InverseIndex);

private:
	// Phys액터 생성에 필요한 정보
	physx::PxCooking* m_pCooking = nullptr;
	bool m_bInit = false;

	std::vector<std::vector<physx::PxVec3>> VertexVec;
	std::vector<std::vector<physx::PxU32>> IndexVec;
	std::shared_ptr<class GameEngineFBXMesh> Mesh;
	physx::PxTriangleMesh* TriMesh = nullptr;

    std::vector<sTriangle> vec_TriangleNav;
	std::deque<sTriangle> dq_ResultRoad;

};