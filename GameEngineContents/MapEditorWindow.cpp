#include "PrecompileHeader.h"
#include "MapEditorWindow.h"
#include "TestObject.h"
#include "Player.h"
#include "SinkBox_4x4.h"
#include "SinkBox_8x8.h"

#include "ProcessMapInfo.h"
#include "MapEditGlobalValue.h"
#include "GameContentsMapActor.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>

MapEditorWindow* MapEditorWindow::EditorGUI;

void MapEditorWindow::CreateSetCurActor(int _ActorType, std::shared_ptr<class GameEngineLevel> Level)
{
	if (nullptr == GameEngineFBXMesh::Find(FBXName))
	{
		MsgAssert("FBX매쉬를 선택하지 않았습니다");
		return;
	}
	CurActor = Level->CreateActor<GameContentsMapActor>();
	std::shared_ptr< GameContentsMapActor> MapActor = CurActor->DynamicThis< GameContentsMapActor>();
	if (nullptr != MapActor->Renderer)
	{
		MsgAssert("잘못생성된 액터입니다.");
	}
	MapActor->Renderer = MapActor->CreateComponent< GameEngineFBXRenderer>();
	std::shared_ptr<GameEngineFBXRenderer> pRenderer = CurActor->CreateComponent< GameEngineFBXRenderer>();
	pRenderer->SetFBXMesh(FBXName, MeterialName);
}

MapEditorWindow::MapEditorWindow()
{
	EditorGUI = this;
}

MapEditorWindow::~MapEditorWindow()
{
}

void MapEditorWindow::Start()
{
	MapEditorWindow::EditorGUI->Off();

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	FilePath.SetPath(Dir.GetPlusFileName("ContentResources\\MapInfo").GetFullPath());
	if (false == GameEngineInput::IsKey("LeftCtrl"))
	{
		GameEngineInput::CreateKey("LeftCtrl", VK_LCONTROL);
	}
	if (false == GameEngineInput::IsKey("EditX"))
	{
		GameEngineInput::CreateKey("EditX", 'X');
	}	
	if (false == GameEngineInput::IsKey("EditY"))
	{
		GameEngineInput::CreateKey("EditY", 'Y');
	}	
	if (false == GameEngineInput::IsKey("EditZ"))
	{
		GameEngineInput::CreateKey("EditZ", 'Z');
	}
	if (false == GameEngineInput::IsKey("LeftClick"))
	{
		GameEngineInput::CreateKey("LeftClick", VK_LBUTTON);
	}	
	if (false == GameEngineInput::IsKey("RightClick"))
	{
		GameEngineInput::CreateKey("RightClick", VK_RBUTTON);
	}

}

void MapEditorWindow::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{

	ImGui::Text("Current Path : %s", FilePath.GetFullPath().c_str());
	if (false == IsSetFilePath)
	{
		SetReadWriteFilePath(Level);
		return;
	}

	ImGui::Separator();
	if (false == ReadCSV)
	{
		if (ImGui::Button("Read Actor File"))
		{
			ReadActor(Level);
			return;
		}
		ImGui::SameLine();
	}
	
	if (nullptr == CurActor)
	{
		SettingCurActor(Level);
	}
	else
	{
		EditCurActor(Level);
	}

}

void MapEditorWindow::EditCurActor(std::shared_ptr<class GameEngineLevel> Level)
{
	ImGui::Text("CurActorIndex : %d, NextNewIndex : %d", CurIndex, lastindex);
	ImGui::Separator();
	ShowFBXINfo();

	EditTransform();
	ImGui::Separator();


	if (ImGui::Button("ResetTrans"))
	{
		CurActor->GetTransform()->SetLocalScale(float4::ONE);
		CurActor->GetTransform()->SetLocalRotation(float4::ZERO);
		CurActor->GetTransform()->SetLocalPosition(float4::ZERO);
		ResetValue();
	}
	if (ImGui::Button("Save") )
	{
		SaveActors();
		CurActor = nullptr;
	}
	if (ImGui::Button("Remove") )
	{
		if (EditorActorInfo.end() != EditorActorInfo.find(CurIndex))
		{
			EditorActorInfo.erase(CurIndex);
			EditorSturctInfo.erase(CurIndex);
		}
		CurActor->Death();
		CurActor = nullptr;
		SaveActors();
	}
}
void MapEditorWindow::ShowFBXINfo()
{
	//std::shared_ptr< GameEngineFBXMesh> CurMesh = GameEngineFBXMesh::Find(FBXName);
	//if (nullptr == CurMesh)
	//{
	//	MsgAssert("매쉬가 세팅되지 않은 액터입니다");
	//}
	//ImGui::Text("FBX Mesh info");
	//ImGui::Text("Scale : %f %f %f", CurMesh->GetMeshInfosCount());
	//ImGui::Text("Rot : %f %f %f", CurMesh->GetMeshInfosCount());
	//ImGui::Text("Rot : %f %f %f", CurMesh->GetMeshInfosCount());
	//ImGui::Separator();

}


void MapEditorWindow::SettingCurActor(std::shared_ptr<class GameEngineLevel> Level)
{
	if (nullptr == CurActor)
	{

		if (ImGui::Button("Clear Actor File") )
		{
			ClearCurFile();
			return;
		}
		ImGui::Separator();

		ImGui::Text("CreateActor");


		///
		//ImGui::InputText("##ActorType", &ActorType[0], ActorType.size());
		ImGui::InputText("##FBXName", &FBXName[0], FBXName.size());
		ImGui::SameLine();
		if (ImGui::Button("FbxLoad"))
		{
			Explorer(FBXName);
		}
		ImGui::InputText("##MeterialName", &MeterialName[0], MeterialName.size());

		ImGui::SameLine();
		if (ImGui::Button("Create"))
		{
			//여기
			CreateSetCurActor(0, Level);

			CurIndex = lastindex++;
			ResetValue();
		}
		////



		ImGui::Separator();
		ImGui::Text("Access Index File");
		ImGui::InputInt("##AccessIndex", &CurIndex);
		if (ImGui::Button("Access")  )
		{
			if (EditorActorInfo.end() == EditorActorInfo.find(CurIndex))
			{
				MsgTextBox("이 index에 해당하는 액터가 존재하지 않습니다");
				return;
			}
			else
			{
				CurActor = EditorActorInfo[CurIndex];
				//ActorType = 0;
				Ratio = EditorSturctInfo[CurIndex].ScaleRatio;
				FBXName = EditorSturctInfo[CurIndex].FBXName;
			}
		}
	}
}

void MapEditorWindow::EditTransformMouseControl()
{
	

	switch (CurOption)
	{
	case EditOption::Scale:
	{
		ImGui::Text("Change Mode : Scale");

		if(true == GameEngineInput::IsPress("LeftCtrl"))
		{
			//float rat = stof(Ratio);
			if (true == GameEngineInput::IsDown("LeftClick"))
			{
				Ratio -= 0.1f;
			}
			else if (true == GameEngineInput::IsDown("RightClick"))
			{
				Ratio += 0.1f;
			}
			CurActor->GetTransform()->SetLocalScale(float4::ONE * Ratio);
			//Ratio = std::to_string(rat);
		}
		
		break;
	}
	case EditOption::Rot:
	{
		ImGui::Text("Change Mode : Rotation");
		if (true == GameEngineInput::IsPress("EditX"))
		{
			if (true == GameEngineInput::IsDown("LeftClick"))
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ -UnitScale ,0 });
			}
			else if (true == GameEngineInput::IsDown("RightClick"))
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ UnitScale ,0 });

			}
		}
		else if (true == GameEngineInput::IsPress("EditY"))
		{
			if (true == GameEngineInput::IsDown("LeftClick"))
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ 0, -UnitScale ,0 });
			}
			else if (true == GameEngineInput::IsDown("RightClick"))
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ 0,UnitScale ,0 });

			}
		}
		else if (true == GameEngineInput::IsPress("EditZ"))
		{
			if (true == GameEngineInput::IsDown("LeftClick"))
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ 0,0, -UnitScale });
			}
			else if (true == GameEngineInput::IsDown("RightClick"))
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ 0,0, UnitScale });

			}
		}
		break;
	}
	case EditOption::Pos:
	{
		ImGui::Text("Change Mode : Position");

		if (true == GameEngineInput::IsPress("EditX"))
		{
			if (true == GameEngineInput::IsDown("LeftClick"))
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ -UnitScale ,0 });
			}
			else if (true == GameEngineInput::IsDown("RightClick"))
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ UnitScale ,0 });

			}
		}
		else if (true == GameEngineInput::IsPress("EditY"))
		{
			if (true == GameEngineInput::IsDown("LeftClick"))
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ 0, -UnitScale ,0 });
			}
			else if (true == GameEngineInput::IsDown("RightClick"))
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ 0,UnitScale ,0 });

			}
		}
		else if (true == GameEngineInput::IsPress("EditZ"))
		{
			if (true == GameEngineInput::IsDown("LeftClick"))
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ 0,0, -UnitScale });
			}
			else if (true == GameEngineInput::IsDown("RightClick"))
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ 0,0, UnitScale });

			}
		}
		break;
	}
	default:
		break;
	}

	if (ImGui::Button("Scale Mode"))
	{
		CurOption = EditOption::Scale;
	}
	ImGui::SameLine();
	if (ImGui::Button("Rotation Mode"))
	{
		CurOption = EditOption::Rot;

	}
	ImGui::SameLine();

	if (ImGui::Button("Position Mode"))
	{
		CurOption = EditOption::Pos;

	}
	
}




void MapEditorWindow::EditTransform()
{
	ImGui::Text("TransformData");
	ImGui::Text("Unit Scale : %f", UnitScale);
	ImGui::InputFloat("##UnitScale", &NextUnitScale);
	//ImGui::InputText("##UnitScale", &recvUnit[0], recvUnit.size());
	ImGui::SameLine();
	if (ImGui::Button("Change Unit"))
	{
		UnitScale = NextUnitScale;
	}

	EditTransformMouseControl();
	TransformData Trans = CurActor->GetTransform()->GetTransDataRef();


	ImGui::Separator();

	{
		//scale
		ImGui::Text("LocalRatio :%f", Trans.LocalScale.x / 1.0f);
		ImGui::InputFloat("Scale Ratio", &Ratio);
		//ImGui::InputText("Scale Ratio", &Ratio[0], Ratio.size());
		if (ImGui::Button("Change Scale"))
		{
			//float Rat = std::stof(Ratio);
			CurActor->GetTransform()->SetLocalScale(float4::ONE * Ratio);
		}
	}
	ImGui::Separator();
	{
		// rotation
		ImGui::Text("LocalRotation :%f %f %f", Trans.LocalRotation.x, Trans.LocalRotation.y, Trans.LocalRotation.z);
		// rot button
		bool isChangeRot = false;
		if (ImGui::Button("-RotX") )
		{
			CurActor->GetTransform()->AddLocalRotation(float4{ -UnitScale ,0 });
			isChangeRot = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("+RotX"))
		{
			CurActor->GetTransform()->AddLocalRotation(float4{ UnitScale ,0 });
			isChangeRot = true;
		}
		ImGui::SameLine();

		if (ImGui::Button("-RotY"))
		{
			CurActor->GetTransform()->AddLocalRotation(float4{ 0, -UnitScale });
			isChangeRot = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("+RotY"))
		{
			CurActor->GetTransform()->AddLocalRotation(float4{ 0, UnitScale });
			isChangeRot = true;
		}
		ImGui::SameLine();

		if (ImGui::Button("-RotZ"))
		{
			CurActor->GetTransform()->AddLocalRotation(float4{ 0,0 - UnitScale });
			isChangeRot = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("+RotZ"))
		{
			CurActor->GetTransform()->AddLocalRotation(float4{ 0,0,UnitScale });
			isChangeRot = true;
		}

		//if (true == isChangeRot)
		//{
		//	RevRotationX = std::to_string(Trans.LocalRotation.x);
		//	RevRotationY = std::to_string(Trans.LocalRotation.y);
		//	RevRotationZ = std::to_string(Trans.LocalRotation.z);
		//}

		ImGui::InputFloat3("##ROT", (float*)&CurRot);

		//ImGui::InputText("RotX", &RevRotationX[0], RevRotationX.size());
		//
		//ImGui::InputText("RotY", &RevRotationY[0], RevRotationY.size());
		//
		//ImGui::InputText("RotZ", &RevRotationZ[0], RevRotationZ.size());

		if (ImGui::Button("Change Rotation"))
		{
			//CurActor->GetTransform()->SetLocalRotation(float4{ std::stof(RevRotationX),std::stof(RevRotationY) ,std::stof(RevRotationZ) });
			CurActor->GetTransform()->SetLocalRotation(CurRot);
			//CurRot = CurActor->GetTransform()->GetLocalRotation();
		}
	}
	ImGui::Separator();
	{
		//position
		ImGui::Text("LocalPosition :%f %f %f", Trans.LocalPosition.x, Trans.LocalPosition.y, Trans.LocalPosition.z);
		// pos button
		bool isChangePos = false;
		if (ImGui::Button("-PosX") )
		{
			CurActor->GetTransform()->AddLocalPosition(float4{ -UnitScale ,0 });
			isChangePos = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("+PosX"))
		{
			CurActor->GetTransform()->AddLocalPosition(float4{ UnitScale ,0 });
			isChangePos = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("-PosY"))
		{
			CurActor->GetTransform()->AddLocalPosition(float4{ 0, -UnitScale ,0 });
			isChangePos = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("+PosY"))
		{
			CurActor->GetTransform()->AddLocalPosition(float4{ 0, UnitScale ,0 });
			isChangePos = true;
		}
		ImGui::SameLine();

		if (ImGui::Button("-PosZ") )
		{
			CurActor->GetTransform()->AddLocalPosition(float4{ 0,0, -UnitScale });
			isChangePos = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("+PosZ"))
		{
			CurActor->GetTransform()->AddLocalPosition(float4{ 0,0,UnitScale });
			isChangePos = true;
		}


		//if (true == isChangePos)
		//{
		//	RevPositionX = std::to_string(Trans.LocalPosition.x);
		//	RevPositionY = std::to_string(Trans.LocalPosition.y);
		//	RevPositionZ = std::to_string(Trans.LocalPosition.z);
		//}

		ImGui::InputFloat3("##Pos", (float*)&CurPos);


		//ImGui::InputText("PosX", &RevPositionX[0], RevPositionX.size());
		//
		//ImGui::InputText("PosY", &RevPositionY[0], RevPositionY.size());
		//
		//ImGui::InputText("PosZ", &RevPositionZ[0], RevPositionZ.size());

		if (ImGui::Button("Change Position") )
		{
			//CurActor->GetTransform()->SetLocalPosition(float4{ std::stof(RevPositionX),std::stof(RevPositionY) ,std::stof(RevPositionZ) });
			CurActor->GetTransform()->SetLocalPosition(CurPos);
		}
	}

}


void MapEditorWindow::SaveActors()
{
	if(nullptr != CurActor)
	{
		SponeMapActor Struct;
		Struct.MeshType = 0; // 수정 필요
		Struct.ScaleRatio = CurActor->GetTransform()->GetLocalScale().x / 1.0f;
		Struct.LocRot = CurActor->GetTransform()->GetLocalRotation();
		Struct.LocPos = CurActor->GetTransform()->GetLocalPosition();
		Struct.FBXNameLen = static_cast<UINT>(FBXName.size());
		Struct.FBXName = FBXName;
		Struct.MeterialLen = static_cast<UINT>(MeterialName.size());
		Struct.MeterialName = MeterialName;

		EditorActorInfo[CurIndex] = CurActor;
		EditorSturctInfo[CurIndex] = Struct;
	}
	ProcessMapInfo::WriteAllFile(FilePath, EditorSturctInfo);

}

void MapEditorWindow::ReadActor(std::shared_ptr<GameEngineLevel> Level)
{
	GameEngineFile file = GameEngineFile(FilePath.GetFullPath());
	if (file.GetFileSize() == 0)
	{
		int a = 0;

		return;
	}
	
	std::vector<SponeMapActor> AllInfo = ProcessMapInfo::OpenFile(FilePath);
	for (SponeMapActor _str : AllInfo)
	{
		FBXName = _str.FBXName;
		MeterialName = _str.MeterialName;

		CreateSetCurActor(0, Level);

		CurActor->GetTransform()->SetLocalScale(float4::ONE * _str.ScaleRatio);
		CurActor->GetTransform()->SetLocalRotation(_str.LocRot);
		CurActor->GetTransform()->SetLocalPosition(_str.LocPos);

		EditorSturctInfo[lastindex] = _str;
		EditorActorInfo[lastindex] = CurActor;

		CurActor = nullptr;
		lastindex++;
	}
	ReadCSV = true;
}


void MapEditorWindow::ResetValue()
{
	CurRot = float4::ZERO;
	CurPos = float4::ZERO;
	//recvUnit = "1000.000000";//1000.000000
	UnitScale = 10.0f;

	Ratio = 1.0f;

	//RevRotationX = "0000.000000";
	//RevRotationY = "0000.000000";
	//RevRotationZ = "0000.000000";

	//RevPositionX = "0000.000000";
	//RevPositionY = "0000.000000";
	//RevPositionZ = "0000.000000";
}


void MapEditorWindow::ReleaseMapEditor()
{
	CurActor = nullptr;
	//PinedActor = nullptr;
	EditorActorInfo.clear();
	EditorSturctInfo.clear();
}


void MapEditorWindow::ClearCurFile()
{
	ProcessMapInfo::CpyAndClear(FilePath);

}

void MapEditorWindow::SetReadWriteFilePath(std::shared_ptr<class GameEngineLevel> Level)
{
	ImGui::InputText("##Path", &FileName[0], FileName.size());
	ImGui::SameLine();
	if (ImGui::Button("SetCsvFile"))
	{
		Explorer(FileName, FilePath.GetFullPath());
	}
	ImGui::TextColored(ImVec4(1.f,0.f,0.f,1.f), "Check \".csv\"");
	ImGui::SameLine();
	if (ImGui::Button("Input Path"))
	{
		FilePath.SetPath(FilePath.GetFullPath() +"\\" + FileName);
		ProcessMapInfo::CreatPathFile(FilePath);
		if (false == FilePath.IsExists())
		{
			MsgAssert("파일이 생성되지 않았습니다;");
			return;
		}

		IsSetFilePath = true;
		ReadActor(Level);
		return;
	}
}

void MapEditorWindow::Explorer(std::string& _Name, const std::string_view& _StartPath)
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Mesh");
	std::string Initpath = NewDir.GetPath().GetFullPath();
	std::wstring strFolderPath = GameEngineString::AnsiToUniCode(Initpath);

	if (_StartPath != "")
	{
		strFolderPath = GameEngineString::AnsiToUniCode(_StartPath);
	}

	OPENFILENAME ofn = {};


	wchar_t szFilePath[256] = {};
	wchar_t szFileName[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = NULL; //'\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = szFileName;
	ofn.nMaxFileTitle = 256;
	ofn.lpstrInitialDir = strFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST| OFN_NOCHANGEDIR;;

	if (false == GetSaveFileName(&ofn))
		return;

	std::wstring filename = szFileName;
	_Name = GameEngineString::UniCodeToAnsi(filename);
}
