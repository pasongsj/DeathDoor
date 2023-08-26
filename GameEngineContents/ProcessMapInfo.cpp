#include "PreCompileHeader.h"
#include "ProcessMapInfo.h"
#include <fstream>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineSerializer.h>


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
	if (std::string::npos != _Path.GetFileName().find("read.csv"))
	{
		return ReadFromText(_Path);
	}
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
		ifs.read((char*)&NewActor.MeshType, sizeof(int));
		ifs.read((char*)&NewActor.LocRot, sizeof(float4::ZERO));
		ifs.read((char*)&NewActor.LocPos, sizeof(float4::ZERO));
		ifs.read((char*)&NewActor.ScaleRatio, sizeof(float));
		ifs.read((char*)&NewActor.FBXNameLen, sizeof(int));
		int Len = static_cast<int>(NewActor.FBXNameLen);
		if (Len <= 0)
		{
			break;
		}
		char* tmp1 = new char[Len + 1];
		ifs.read(tmp1, Len);
		tmp1[Len] = '\0';
		NewActor.FBXName = tmp1;

		ifs.read((char*)&NewActor.MeterialLen, sizeof(int));
		Len = static_cast<int>(NewActor.MeterialLen);
		if (Len <= 0)
		{
			break;
		}
		char* tmp2 = new char[Len + 1];
		ifs.read(tmp2, Len);
		tmp2[Len] = '\0';
		NewActor.MeterialName = tmp2;

		NewActorStructs.push_back(NewActor);
		delete[] tmp1;
		delete[] tmp2;
	}

	ifs.close();
	return NewActorStructs;
}


void ProcessMapInfo::WriteAllFile(GameEnginePath _Path, std::map<int, SponeMapActor> _AllStruct)
{
	std::ofstream ofs;
	ofs.open(_Path.GetFullPath(), std::ios::out);
	// bin to text clear
	ClearFile(_Path.GetFullPath() + "read.csv");	//std::filesystem::remove(_Path.GetFullPath() + "read.csv");
	for (std::pair<int, SponeMapActor> _StructInfo : _AllStruct)
	{
		WriteFile(_Path, _StructInfo.second);
	}
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
	//ofs.write((char*)&_Value.ActorIndex, sizeof(int));
	ofs.write((char*)&_Value.MeshType, sizeof(int));
	ofs.write((char*)&_Value.LocRot, sizeof(float4::ZERO));
	ofs.write((char*)&_Value.LocPos, sizeof(float4::ZERO));
	ofs.write((char*)&_Value.ScaleRatio, sizeof(float));
	ofs.write((char*)&_Value.FBXNameLen, sizeof(int));
	ofs.write(_Value.FBXName.c_str(), _Value.FBXNameLen);
	ofs.write((char*)&_Value.MeterialLen, sizeof(int));
	ofs.write(_Value.MeterialName.c_str(), _Value.MeterialLen);

	//ofs.write((char*)&_Value, sizeof(struct SponeMapActor));
	ofs.close();
	SaveToText(_Value, _Path); // 이어쓰기 하는 방법
	return;
}
void ProcessMapInfo::CpyFile(GameEnginePath _Path, const std::string& FileName)
{
	std::ifstream in;
	in.open(_Path.GetFullPath(), std::ios_base::in | std::ios::binary);
	if (in.fail())
	{
		MsgAssert("파일을 읽는데 실패하였습니다");
		in.close();
		return;
	}
	// 파일의 전체 크기를 확인한다
	in.seekg(0, std::ios::end);
	int length = static_cast<int>(in.tellg());

	// 파일의 전체 크기만큼 메모리에 로드한다
	in.seekg(0, std::ios::beg);
	char* buf = new char[length];
	in.read(buf, length);
	in.close();
	
	// 메모리에 저장된 파일 데이터를 다른 파일에 저장한다
	std::string NewPath = GameEnginePath::GetFolderPath(_Path.GetFullPath()) + FileName;
	if ("" == FileName)
	{
		NewPath = GameEnginePath::GetFolderPath(_Path.GetFullPath()) + "TMP\\" + GameEngineTime::GetCurTime() + _Path.GetFileName();
	}
	std::ofstream out;
	out.open(NewPath, std::ios_base::out | std::ios::binary);
	if (out.fail())
	{
		MsgAssert("파일을 여는데 실패하였습니다");
		out.close();
		return;
	}
	out.write(buf, length);

	delete[] buf;
	out.close();
}
void ProcessMapInfo::ClearFile(GameEnginePath _Path)
{
	std::ofstream clearf;
	clearf.open(_Path.GetFullPath(), std::ios_base::out);
	clearf.close();
}

void ProcessMapInfo::CpyAndClear(GameEnginePath _Path)
{
	std::string NewPath = "Cpy" + _Path.GetFileName();
	CpyFile(_Path, NewPath);
	ClearFile(_Path);
}

void ProcessMapInfo::CreatPathFile(GameEnginePath _Path)
{
	if (false == _Path.IsExists())
	{
		std::ofstream ofs;
		ofs.open(_Path.GetFullPath(), std::ios::out);
		ofs.close();
		return;
	}
}

void ProcessMapInfo::SaveToText(const SponeMapActor& _Value, GameEnginePath _Load)
{
	std::string ToText;

	GameEngineFile file = GameEngineFile(std::string_view(_Load.GetFullPath() + "read.csv"));
	{
		//MeshType
		ToText += GameEngineString::ToString(_Value.MeshType);
		ToText += ",";
		// LocRot
		ToText += GameEngineString::ToString(_Value.LocRot.x);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocRot.y);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocRot.z);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocRot.w);
		ToText += ",";
		//LocPos
		ToText += GameEngineString::ToString(_Value.LocPos.x);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocPos.y);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocPos.z);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocPos.w);
		ToText += ",";
		//LocScale Ratio
		ToText += GameEngineString::ToString(_Value.ScaleRatio);
		ToText += ",";
		//FBXNameLen
		ToText += GameEngineString::ToString(static_cast<int>(_Value.FBXNameLen));
		ToText += ",";
		//FBXName
		ToText += _Value.FBXName;
		ToText += ",";
		//MeterialLen
		ToText += GameEngineString::ToString(static_cast<int>(_Value.MeterialLen));
		ToText += ",";
		//MeterialName
		ToText += _Value.MeterialName;
		ToText += "\n";
	}

	file.SaveTextAppend(ToText);

}

std::vector<SponeMapActor> ProcessMapInfo::ReadFromText(GameEnginePath _Path)
{
	std::vector<SponeMapActor> NewActorStructs;
	GameEngineFile file = GameEngineFile(_Path);
	std::string Data;
	Data.reserve(file.GetFileSize());
	Data = file.GetString();

	std::istringstream ss(Data);
	std::string SubString;

	while (getline(ss, SubString, '\n'))
	{

		SponeMapActor NewStruct;
		std::istringstream s2(SubString);
		std::string Source;
		// meshtype
		getline(s2, Source, ',');
		NewStruct.MeshType = stoi(Source);
		// LocRot
		getline(s2, Source, ',');
		NewStruct.LocRot.x = stof(Source);
		getline(s2, Source, ',');
		NewStruct.LocRot.y = stof(Source);
		getline(s2, Source, ',');
		NewStruct.LocRot.z = stof(Source);
		getline(s2, Source, ',');
		NewStruct.LocRot.w = stof(Source);
		// LocPos
		getline(s2, Source, ',');
		NewStruct.LocPos.x = stof(Source);
		getline(s2, Source, ',');
		NewStruct.LocPos.y = stof(Source);
		getline(s2, Source, ',');
		NewStruct.LocPos.z = stof(Source);
		getline(s2, Source, ',');
		NewStruct.LocPos.w = stof(Source);
		// Ratio
		getline(s2, Source, ',');
		NewStruct.ScaleRatio = stof(Source);
		// fbx name
		getline(s2, Source, ',');
		NewStruct.FBXNameLen = stoi(Source);
		getline(s2, Source, ',');
		NewStruct.FBXName = Source;
		//Meterial name
		getline(s2, Source, ',');
		NewStruct.MeterialLen = stoi(Source);
		getline(s2, Source, ',');
		NewStruct.MeterialName = Source;
		NewActorStructs.push_back(NewStruct);
	}
	return NewActorStructs;
}