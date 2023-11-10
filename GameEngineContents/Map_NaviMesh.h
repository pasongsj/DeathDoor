#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Map_NaviMesh : public GameEngineActor
{
public:
	// constrcuter destructer
	Map_NaviMesh();
	~Map_NaviMesh();

	// delete Function
	Map_NaviMesh(const Map_NaviMesh& _Other) = delete;
	Map_NaviMesh(Map_NaviMesh&& _Other) noexcept = delete;
	Map_NaviMesh& operator=(const Map_NaviMesh& _Other) = delete;
	Map_NaviMesh& operator=(Map_NaviMesh&& _Other) noexcept = delete;

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);

private:
	std::shared_ptr<class PhysXTriangleComponent> m_pNaviComp = nullptr;


};

