#include "PrecompileHeader.h"
#include "MapEditorWindow.h"
#include "TestObject.h"
#include "Player.h"
#include "SinkBox_4x4.h"
#include "SinkBox_8x8.h"

#include "ProcessMapInfo.h"
#include "MapEditGlobalValue.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>



//여기
	std::map<std::string, int> typeconvertor = { 
		{"GameEngineActor",static_cast<int>(ContentsActorType::GameEngineActor)},
		{"TestObject",static_cast<int>(ContentsActorType::TestObject)},
		{"Player",static_cast<int>(ContentsActorType::Player)},
		{"SinkBox_4x4", static_cast<int>(ContentsActorType::SinkBox_4x4)},
		{"SinkBox_8x8", static_cast<int>(ContentsActorType::SinkBox_8x8)} 
	};
	
	std::map<int, std::string> typeconvertorItoS = { 
		{static_cast<int>(ContentsActorType::GameEngineActor),"GameEngineActor"},
		{static_cast<int>(ContentsActorType::TestObject),"TestObject"},
		{static_cast<int>(ContentsActorType::Player),"Player"},
		{static_cast<int>(ContentsActorType::SinkBox_4x4), "SinkBox_4x4"},
		{static_cast<int>(ContentsActorType::SinkBox_8x8),"SinkBox_8x8"} 
	};


MapEditorWindow* MapEditorWindow::EditorGUI;

void MapEditorWindow::CreateSetCurActor(int _ActorType, std::shared_ptr<class GameEngineLevel> Level)
{
	if (static_cast<int>(ContentsActorType::GameEngineActor) == _ActorType)
	{
		if (nullptr == GameEngineFBXMesh::Find(FBXName))
		{
			MsgAssert("FBX매쉬를 선택하지 않았습니다");
			return;
		}
		CurActor = Level->CreateActor<GameEngineActor>();
		std::shared_ptr<GameEngineFBXRenderer> pRenderer = CurActor->CreateComponent< GameEngineFBXRenderer>();
		pRenderer->SetFBXMesh(FBXName, MeterialName);
	}
	else if (static_cast<int>(ContentsActorType::TestObject) == _ActorType)
	{
		CurActor = Level->CreateActor<TestObject>();
	}
	else if (static_cast<int>(ContentsActorType::Player) == _ActorType)
	{
		CurActor = Level->CreateActor<Player>();
	}
	else if (static_cast<int>(ContentsActorType::SinkBox_4x4) == _ActorType)
	{
		CurActor = Level->CreateActor<SinkBox_4x4>();
	}
	else if (static_cast<int>(ContentsActorType::SinkBox_8x8) == _ActorType)
	{
		CurActor = Level->CreateActor<SinkBox_8x8>();
	}
	else
	{
		return;
	}
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
	if (Level.get() == GetLevel())
	{
		return;
	}

	ImGui::Text("Current Path : %s", FilePath.GetFullPath().c_str());
	if (false == IsSetFilePath)
	{
		SetReadWriteFilePath(Level);
		return;
	}

	ImGui::Separator();
	if (false == ReadCSV)
	{
		if(ImGui::Button("Read Actor File") && Level.get() != GetLevel())
		{
			ReadActor(Level);
			return;
		}
		ImGui::SameLine();
	}


	if (nullptr == CurActor)
	{

		if (ImGui::Button("Clear Actor File") && Level.get() != GetLevel())
		{
			ClearActors();
			return;
		}
		ImGui::Separator();


		//여기
		const char* items[] = { "GameEngineActor", "TestObject","Player","SinkBox_4x4", "SinkBox_8x8"};
		static const char* current_item = NULL;
		ImGui::Text("CreateActor");
		if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				if (ImGui::Selectable(items[n]))
				{
					current_item = items[n];
					ActorType = items[n];
				}

				//bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your /objects
				//if (ImGui::Selectable(items[n], is_selected))
				//	ActorType = items[n];
				//if (is_selected)
				//	ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)

			}

			ImGui::EndCombo();
		}


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
		if (ImGui::Button("Create") && Level.get() != GetLevel())
		{
			//여기
			CreateSetCurActor(typeconvertor[ActorType], Level);
			
			CurIndex = lastindex++;
			ResetValue();
		}
		////



		ImGui::Separator();
		ImGui::Text("Access Index File");
		ImGui::InputInt("##AccessIndex", &CurIndex);
		if (ImGui::Button("Access") && Level.get() != GetLevel())
		{
			if (EditorActorInfo.end() == EditorActorInfo.find(CurIndex))
			{
				MsgTextBox("이 index에 해당하는 액터가 존재하지 않습니다");
				return;
			}
			else
			{
				CurActor = EditorActorInfo[CurIndex];
				ActorType = typeconvertorItoS[EditorSturctInfo[CurIndex].ActorType];
				//ActorOrder = 0;// 임시
				Ratio = std::to_string(EditorSturctInfo[CurIndex].ScaleRatio);
				CurNetType = EditorSturctInfo[CurIndex].IsMoveable;
				FBXName = EditorSturctInfo[CurIndex].FBXName;
			}
		}
	}
	else
	{

		ImGui::Text("CurActorIndex : %d, NextNewIndex : %d", CurIndex,lastindex);
		//
		ImGui::Separator();
		//
		EditTransform();

		ImGui::Separator();

		static const char* Select = NULL;
		const char* NetTypes[] = {"LocalActor",  "ServerActor" };
		ImGui::Text("Net Type - is moveable?");
		if (ImGui::BeginCombo("##combo", Select)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(NetTypes); n++)
			{
				if (ImGui::Selectable(NetTypes[n]))
				{
					Select = NetTypes[n];
					CurNetType = NetTypes[n];
				}
				//bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your /objects
				//if (ImGui::Selectable(items[n], is_selected))
				//	ActorType = items[n];
				//if (is_selected)
				//		ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)

			}
			ImGui::EndCombo();
		}
		ImGui::Separator();
		if (ImGui::Button("ResetTrans") && Level.get() != GetLevel())
		{
			CurActor->GetTransform()->SetLocalScale(float4::ONE);
			CurActor->GetTransform()->SetLocalRotation(float4::ZERO);
			CurActor->GetTransform()->SetLocalPosition(float4::ZERO);
			ResetValue();
		}
		if (ImGui::Button("Save") && Level.get() != GetLevel())
		{
			SaveActors();
			CurActor = nullptr;
		}
		if (ImGui::Button("Remove") && Level.get() != GetLevel())
		{

			//int CurIndex = CurStruct.ActorIndex;
			if(EditorActorInfo.end() != EditorActorInfo.find(CurIndex))
			{
				EditorActorInfo.erase(CurIndex);
				EditorSturctInfo.erase(CurIndex);
			}
			CurActor->Death();
			CurActor = nullptr;
			SaveActors();
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
			float rat = stof(Ratio);
			if (true == GameEngineInput::IsDown("LeftClick"))
			{
				rat -= 0.1f;
			}
			else if (true == GameEngineInput::IsDown("RightClick"))
			{
				rat += 0.1f;
			}
			CurActor->GetTransform()->SetLocalScale(float4::ONE * rat);
			Ratio = std::to_string(rat);
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
	ImGui::InputText("##UnitScale", &recvUnit[0], recvUnit.size());
	ImGui::SameLine();
	if (ImGui::Button("Change Unit"))
	{
		if (recvUnit.size() > 0)
		{
			UnitScale = std::stof(recvUnit);
		}
	}

	EditTransformMouseControl();
	TransformData Trans = CurActor->GetTransform()->GetTransDataRef();


	ImGui::Separator();

	{
		//scale
		ImGui::Text("LocalRatio :%f", Trans.LocalScale.x / 1.0f);
		ImGui::InputText("Scale Ratio", &Ratio[0], Ratio.size());
		if (ImGui::Button("Change Scale"))
		{
			float Rat = std::stof(Ratio);
			CurActor->GetTransform()->SetLocalScale(float4{ Rat, Rat, Rat });
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

		if (true == isChangeRot)
		{
			RevRotationX = std::to_string(Trans.LocalRotation.x);
			RevRotationY = std::to_string(Trans.LocalRotation.y);
			RevRotationZ = std::to_string(Trans.LocalRotation.z);
		}

		ImGui::InputText("RotX", &RevRotationX[0], RevRotationX.size());

		ImGui::InputText("RotY", &RevRotationY[0], RevRotationY.size());

		ImGui::InputText("RotZ", &RevRotationZ[0], RevRotationZ.size());

		if (ImGui::Button("Change Rotation"))
		{
			CurActor->GetTransform()->SetLocalRotation(float4{ std::stof(RevRotationX),std::stof(RevRotationY) ,std::stof(RevRotationZ) });
			CurRot = CurActor->GetTransform()->GetLocalRotation();
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


		if (true == isChangePos)
		{
			RevPositionX = std::to_string(Trans.LocalPosition.x);
			RevPositionY = std::to_string(Trans.LocalPosition.y);
			RevPositionZ = std::to_string(Trans.LocalPosition.z);
		}

		ImGui::InputText("PosX", &RevPositionX[0], RevPositionX.size());

		ImGui::InputText("PosY", &RevPositionY[0], RevPositionY.size());

		ImGui::InputText("PosZ", &RevPositionZ[0], RevPositionZ.size());

		if (ImGui::Button("Change Position") )
		{
			CurActor->GetTransform()->SetLocalPosition(float4{ std::stof(RevPositionX),std::stof(RevPositionY) ,std::stof(RevPositionZ) });
		}
	}

}



void MapEditorWindow::SaveActors()
{
	if(nullptr != CurActor)
	{
		SponeMapActor Struct;
		Struct.ActorType = typeconvertor[ActorType];
		Struct.ActorOrder = 0;
		Struct.ScaleRatio = CurActor->GetTransform()->GetLocalScale().x / 1.0f;
		Struct.LocRot = CurActor->GetTransform()->GetLocalRotation();
		Struct.LocPos = CurActor->GetTransform()->GetLocalPosition();
		Struct.IsMoveable = CurNetType;
		Struct.FBXNameLen = static_cast<UINT>(FBXName.size());
		Struct.FBXName = FBXName;

		EditorActorInfo[CurIndex] = CurActor;
		EditorSturctInfo[CurIndex] = Struct;
	}
	ProcessMapInfo::WriteAllFile(FilePath, EditorSturctInfo);

}

void MapEditorWindow::ReadActor(std::shared_ptr<GameEngineLevel> Level)
{
	//여기
	std::vector<SponeMapActor> AllInfo = ProcessMapInfo::OpenFile(FilePath);
	for (SponeMapActor _str : AllInfo)
	{
		FBXName = _str.FBXName;
		CreateSetCurActor(_str.ActorType, Level);

		CurActor->SetOrder(static_cast<int>(_str.ActorOrder));
		CurActor->GetTransform()->SetLocalScale(float4::ONE * _str.ScaleRatio);
		CurActor->GetTransform()->SetLocalRotation(_str.LocRot);
		CurActor->GetTransform()->SetLocalPosition(_str.LocPos);

		EditorSturctInfo[lastindex] = _str;
		EditorActorInfo[lastindex] = CurActor;
		//recvUnit = std::to_string(_str.ScaleRatio);
		Ratio = std::to_string(_str.ScaleRatio);
		CurActor = nullptr;
		lastindex++;
	}
	ReadCSV = true;
}


void MapEditorWindow::ResetValue()
{
	CurRot = float4::ZERO;
	CurPos = float4::ZERO;
	recvUnit = "1000.000000";//1000.000000
	UnitScale = 10.0f;

	Ratio = "1.000000";

	RevRotationX = "0000.000000";
	RevRotationY = "0000.000000";
	RevRotationZ = "0000.000000";

	RevPositionX = "0000.000000";
	RevPositionY = "0000.000000";
	RevPositionZ = "0000.000000";
}


void MapEditorWindow::ReleaseMapEditor()
{
	CurActor = nullptr;
	//PinedActor = nullptr;
	EditorActorInfo.clear();
	EditorSturctInfo.clear();
}


void MapEditorWindow::ClearActors()
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
