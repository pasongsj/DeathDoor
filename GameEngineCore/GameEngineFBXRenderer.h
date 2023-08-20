#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineFBXMesh.h"

// Ό³Έν :
class GameEngineFBXRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineFBXRenderer();
	~GameEngineFBXRenderer();

	// delete Function
	GameEngineFBXRenderer(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer(GameEngineFBXRenderer&& _Other) noexcept = delete;
	GameEngineFBXRenderer& operator=(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer& operator=(GameEngineFBXRenderer&& _Other) noexcept = delete;

	virtual void SetFBXMesh(const std::string& _Name, std::string _Material);
	virtual void SetFBXMesh(const std::string& _Name, std::string _Material, size_t MeshIndex);
	virtual std::shared_ptr<GameEngineRenderUnit> SetFBXMesh(const std::string& _Name, std::string _Material, size_t MeshIndex, size_t _SubSetIndex);

	std::map<std::pair<size_t, size_t>, std::shared_ptr<GameEngineRenderUnit>> GetUnTexturedUnit()
	{
		return UnTexturedUnit;
	}

	inline std::shared_ptr<GameEngineFBXMesh> GetFBXMesh()
	{
		return FBXMesh;
	}

	inline std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> GetRenderUnit()
	{
		return Unit;
	}

protected:
	//void Render(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFBXMesh> FBXMesh;
	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> Unit;

	std::map<std::pair<size_t, size_t>, std::shared_ptr<GameEngineRenderUnit>> UnTexturedUnit;
};

