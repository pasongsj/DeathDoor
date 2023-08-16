#include "PreCompileHeader.h"
#include "ProcessMapInfo.h"
#include <fstream>
ProcessMapInfo* ProcessMapInfo::RWProcessInst = nullptr;

ProcessMapInfo::ProcessMapInfo()
{
	RWProcessInst = this;
}

ProcessMapInfo::~ProcessMapInfo()
{
}

std::vector<SponeMapActor> ProcessMapInfo::OpenFile(GameEnginePath _Path)
{
	std::vector<SponeMapActor> NewActorStructs;

	std::ifstream ifs;
	ifs.open(_Path.GetFullPath(), std::ios_base::in | std::ios::binary);
	if (ifs.fail())
	{
		MsgAssert("파일을 읽는데 실패하였습니다");
		ifs.close();
		return NewActorStructs;
	}



	while (!ifs.eof()) {
		SponeMapActor NewActor;
		ifs.read((char*)&NewActor, sizeof(SponeMapActor));
		if (!ifs.eof())
			NewActorStructs.push_back(NewActor);
	}

	//while (ifs.good())
	//{
	//	SponeMapActor NewActor;
	//	ifs.read((char*)&NewActor.ActorIndex, sizeof(NewActor.ActorIndex));
	//	ifs.read((char*)&NewActor.ActorType, sizeof(NewActor.ActorType));
	//	ifs.read((char*)&NewActor.ActorOrder, sizeof(NewActor.ActorOrder));
	//	ifs.read((char*)&NewActor.FBXName, sizeof(NewActor.FBXName));
	//	ifs.read((char*)&NewActor.LocScale, sizeof(NewActor.LocScale));
	//	ifs.read((char*)&NewActor.LocRot, sizeof(NewActor.LocRot));
	//	ifs.read((char*)&NewActor.LocPos, sizeof(NewActor.LocPos));
	//	ifs.read((char*)&NewActor.ScaleRatio, sizeof(NewActor.ScaleRatio));
	//	ifs.read((char*)&NewActor.IsMoveable, sizeof(NewActor.IsMoveable));
	//	//std::vector<std::string> row = csv_read_row(ifs, ',');
	//	NewActorStructs.push_back(NewActor);
	//}
	ifs.close();
	return NewActorStructs;
}


void ProcessMapInfo::WriteFile(GameEnginePath _Path, const SponeMapActor& _Value)
{
	std::ofstream ofs;
	ofs.open(_Path.GetFullPath(), std::ios::out | std::ios::app | std::ios::binary);
	if (ofs.fail())
	{
		MsgAssert("파일을 여는데 실패하였습니다");
		ofs.close();
		return;
	}
	ofs.write((char*)&_Value, sizeof(struct SponeMapActor));
	ofs.close();
	return;
}

void ProcessMapInfo::CloseFile()
{
}
