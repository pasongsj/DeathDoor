#pragma once
#include <bitset>
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
	static void CpyFile(GameEnginePath _Path,const std::string& FileName = "");
	static void ClearFile(GameEnginePath _Path);

	static void WriteFile(GameEnginePath _Path, const SponeMapActor& _Value);

	static void WriteAllFile(GameEnginePath _Path, std::map<int, SponeMapActor> _AllStruct );


	static void CreatPathFile(GameEnginePath _Path);

	static void BinToText(const SponeMapActor& _Value,GameEnginePath _Load);

protected:

private:
	GameEnginePath Path;

};

