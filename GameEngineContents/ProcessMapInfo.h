#pragma once
#include <GameEngineBase/GameEngineFile.h>
#include "MapEditGlobalValue.h"

class ProcessMapInfo
{
public:
	static ProcessMapInfo* RWProcessInst;
	// constrcuter destructer
	ProcessMapInfo() ;
	~ProcessMapInfo();

	// delete Function
	ProcessMapInfo(const ProcessMapInfo& _Other) = delete;
	ProcessMapInfo(ProcessMapInfo&& _Other) noexcept = delete;
	ProcessMapInfo& operator=(const ProcessMapInfo& _Other) = delete;
	ProcessMapInfo& operator=(ProcessMapInfo&& _Other) noexcept = delete;


	static std::vector<SponeMapActor> OpenFile(GameEnginePath _Path);

	static void CpyAndClear(GameEnginePath _Path);

	static void WriteFile(GameEnginePath _Path, const SponeMapActor& _Value);

	static void CreatPathFile(GameEnginePath _Path);

protected:

private:
	GameEnginePath Path;

};

