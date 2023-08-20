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
	std::filesystem::remove(_Path.GetFullPath() + "read.csv");
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
	BinToText(_Value, _Path); // 이어쓰기 하는 방법
	return;
}


void ProcessMapInfo::CpyAndClear(GameEnginePath _Path)
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
	std::ofstream clearf;
	clearf.open(_Path.GetFullPath(), std::ios_base::out);
	clearf.close();

	// 메모리에 저장된 파일 데이터를 다른 파일에 저장한다
	std::ofstream out;
	std::string NewPath = GameEnginePath::GetFolderPath(_Path.GetFullPath()) + "Cpy" + _Path.GetFileName();
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

void ProcessMapInfo::BinToText(const SponeMapActor& _Value, GameEnginePath _Load)
{
	std::string ToText;
	//GameEngineFile Beforefile = GameEngineFile(_Load.GetFullPath() + "read.csv");

	//if (std::filesystem::exists(_Load.GetFullPath() + "read.csv") && Beforefile.GetFileSize() != 0)
	//{
	//	ToText += Beforefile.GetString();
	//	std::filesystem::remove(_Load.GetFullPath() + "read.csv");
	//	
	//}

	GameEngineFile file = GameEngineFile(_Load.GetFullPath() + "read.csv");
	{
		ToText += "MeshType";
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.MeshType);
		ToText += "\n";
		ToText += "LocRot";
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocRot.x);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocRot.y);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocRot.z);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocRot.w);
		ToText += "\n";
		ToText += "LocPos";
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocPos.x);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocPos.y);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocPos.z);
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.LocPos.w);
		ToText += "\n";
		ToText += "ScaleRatio";
		ToText += ",";
		ToText += GameEngineString::ToString(_Value.ScaleRatio);
		ToText += "\n";
		ToText += "FBXNameLen";
		ToText += ",";
		ToText += GameEngineString::ToString(static_cast<int>(_Value.FBXNameLen));
		ToText += "\n";
		ToText += "FBXName";
		ToText += ",";
		ToText += _Value.FBXName;
		ToText += "\n";
		ToText += "MeterialLen";
		ToText += ",";
		ToText += GameEngineString::ToString(static_cast<int>(_Value.MeterialLen));
		ToText += "\n";
		ToText += "MeterialName";
		ToText += ",";
		ToText += _Value.MeterialName;
		ToText += "\n";
	}

	file.SaveTextAppend(ToText);

}

void ProcessMapInfo::TextToBin(std::vector<SponeMapActor>& _Value, GameEnginePath _Load)
{

	///완성 못함
	GameEngineFile file = GameEngineFile(_Load.GetFullPath());
	std::string AllData;
	if (std::filesystem::exists(_Load.GetFullPath()))
	{
		if (file.GetFileSize() != 0)
		{
			GameEngineSerializer Ser;
			Ser.BufferResize(file.GetFileSize());
			file.LoadText(Ser);
			AllData += Ser.GetString();			
		}
	}


	std::string Temp;
	int iDownCount = 0;
	int ResultCount = 0;

	SponeMapActor Actor;
	for (size_t i = 0; i < AllData.size(); i++)
	{
		if (i == 10)
		{
			int a = 0;
		}
		switch (AllData[i])
		{
		case ',':
		{
			if (ResultCount == 0)
			{
				Temp.clear();
				++ResultCount;
				break;
			}
			++ResultCount;
			switch (static_cast<SponeMapActorData>(iDownCount))
			{
			case SponeMapActorData::MeshType:
			{
				if (ResultCount != 1)
				{
					break;
				}
				Actor.MeshType = std::stoi(Temp);
			}
			break;
			case SponeMapActorData::LocRotx:
				Actor.LocRot.x = std::stof(Temp); ++iDownCount;
				break;
			case SponeMapActorData::LocRoty:
				Actor.LocRot.y = std::stof(Temp); ++iDownCount;
				break;
			case SponeMapActorData::LocRotz:
				Actor.LocRot.z = std::stof(Temp); ++iDownCount;
				break;
			case SponeMapActorData::LocRotw:
				Actor.LocRot.w = std::stof(Temp);
				break;
			case SponeMapActorData::LocPosx:
				Actor.LocPos.x = std::stof(Temp); ++iDownCount;
				break;
			case SponeMapActorData::LocPosy:
				Actor.LocPos.y = std::stof(Temp); ++iDownCount;
				break;
			case SponeMapActorData::LocPosz:
				Actor.LocPos.z = std::stof(Temp); ++iDownCount;
				break;
			case SponeMapActorData::LocPosw:
				Actor.LocPos.w = std::stof(Temp);
				break;
			case SponeMapActorData::ScaleRatio:
			{
				if (ResultCount != 1)
				{
					break;
				}
				Actor.ScaleRatio = std::stof(Temp);
			}
				break;
			case SponeMapActorData::TFBXNameLen: 
			{
				if (ResultCount != 1)
				{
					break;
				}
				Actor.FBXNameLen = std::stoi(Temp);
			}
				break;
			case SponeMapActorData::FBXName:
			{
				if (ResultCount != 1)
				{
					break;
				}
				Actor.FBXName = Temp;
			}
				break;
			case SponeMapActorData::MeterialLen:
			{
				if (ResultCount != 1)
				{
					break;
				}
				Actor.MeterialLen = std::stoi(Temp); 
			}
				break;
			case SponeMapActorData::MeterialName:
			{
				if (ResultCount != 1)
				{
					break;
				}
				Actor.MeterialName = Temp;
			}
				break;
			case SponeMapActorData::MAX:
			{
				iDownCount = 0;
				ResultCount = 0;
				Temp.clear();
			}
			break;
			}
		}
		break;
		
		case '\n':
		{
			++iDownCount;
			ResultCount = 0;
		}
		break;
		default:
			Temp += AllData[i];
			break;
		}
	}
	_Value.push_back(Actor);
}
