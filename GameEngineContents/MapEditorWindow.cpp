#include "PrecompileHeader.h"
#include "MapEditorWindow.h"
#include "TestObject.h"
#include "Player.h"



#include "ProcessMapInfo.h"
#include "MapEditGlobalValue.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>
	std::map<std::string, int> typeconvertor = { {"GameEngineActor",static_cast<int>(ContentsActorType::GameEngineActor)},
{"TestObject",static_cast<int>(ContentsActorType::TestObject)},{"Player",static_cast<int>(ContentsActorType::Player)} };

MapEditorWindow* MapEditorWindow::EditorGUI;

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


		const char* items[] = { "GameEngineActor", "TestObject","Player"};
		static const char* current_item = NULL;
		ImGui::Text("CreateActor");
		if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(items[n], is_selected))
					ActorType = items[n];
					if (is_selected)
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
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
			if ("GameEngineActor" == ActorType)
			{
				if (nullptr == GameEngineFBXMesh::Find(FBXName))
				{
					MsgTextBox("FBX매쉬를 선택하지 않았습니다");
					return;
				}
				CurActor = Level->CreateActor<GameEngineActor>();
				std::shared_ptr<GameEngineFBXRenderer> pRenderer = CurActor->CreateComponent< GameEngineFBXRenderer>();
				pRenderer->SetFBXMesh(FBXName, MeterialName);
			}
			else if ("TestObject" == ActorType)
			{
				CurActor = Level->CreateActor<TestObject>();
			}
			else if ("Player" == ActorType)
			{
				CurActor = Level->CreateActor<Player>();
			}
			else
			{
				return;
			}
			++lastindex;

			recvUnit = std::to_string(UnitScale);
			CurStruct.ActorIndex = lastindex;
			CurStruct.ActorOrder = 0; // 임시
			CurStruct.ActorType = typeconvertor[ActorType];;
			CurStruct.FBXName = FBXName;
			CurStruct.FBXNameLen = FBXName.size();
			CurStruct.IsMoveable = false; // 임시
			ResetValue();
		}
		////



		ImGui::Separator();
		ImGui::Text("Access Index File");
		ImGui::InputText("##AccessIndex", &AccessIndex[0], AccessIndex.size());
		if (ImGui::Button("Access") && Level.get() != GetLevel())
		{
			if ('0' != AccessIndex[0] && 0 == atoi(AccessIndex.c_str()))
			{
				MsgTextBox("숫자를 입력하세요");
				return;
			}
			else if (EditorActorInfo.end() == EditorActorInfo.find(stoi(AccessIndex)))
			{
				MsgTextBox("이 index에 해당하는 액터가 존재하지 않습니다");
				return;
			}
			else
			{
				CurActor = EditorActorInfo[stoi(AccessIndex)];
				CurStruct = EditorSturctInfo[stoi(AccessIndex)];
			}
		}
	}
	else
	{

		ImGui::Text("CurActorIndex :");
		ImGui::SameLine();
		ImGui::Text(std::to_string(CurStruct.ActorIndex).c_str());
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
				bool is_selected = (Select == NetTypes[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(NetTypes[n], is_selected))
					CurStruct.IsMoveable = ("ServerActor" == NetTypes[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
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

			int CurIndex = CurStruct.ActorIndex;
			EditorActorInfo.erase(CurIndex);
			EditorSturctInfo.erase(CurIndex);
			SaveActors();
			CurActor->Death();
			CurActor = nullptr;
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
		if (true == GameEngineInput::IsPress("EditX"))
		{
			if (true == GameEngineInput::IsDown("LeftClick"))
			{
				CurActor->GetTransform()->AddLocalScale(float4{ -1.0f ,0 });
			}
			else if (true == GameEngineInput::IsDown("RightClick"))
			{
				CurActor->GetTransform()->AddLocalScale(float4{ 1.0f ,0 });

			}
		}
		else if (true == GameEngineInput::IsPress("EditY"))
		{
			if (true == GameEngineInput::IsDown("LeftClick"))
			{
				CurActor->GetTransform()->AddLocalScale(float4{ 0, -1.0f ,0 });
			}
			else if (true == GameEngineInput::IsDown("RightClick"))
			{
				CurActor->GetTransform()->AddLocalScale(float4{ 0,1.0f ,0 });

			}
		}
		else if (true == GameEngineInput::IsPress("EditZ"))
		{
			if (true == GameEngineInput::IsDown("LeftClick"))
			{
				CurActor->GetTransform()->AddLocalScale(float4{ 0,0, -1.0f });
			}
			else if (true == GameEngineInput::IsDown("RightClick"))
			{
				CurActor->GetTransform()->AddLocalScale(float4{ 0,0, 1.0f });

			}
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

		if (ImGui::Button("Change Rotion"))
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
	enum class ContentsActorType
	{
		GameEngineActor,
		TestObject,
		Player
	};
	if (CurStruct.ActorIndex == lastindex)
	{
		CurStruct.LocScale = CurActor->GetTransform()->GetLocalScale();
		CurStruct.LocRot = CurActor->GetTransform()->GetLocalRotation();
		CurStruct.LocPos = CurActor->GetTransform()->GetLocalPosition();
		CurStruct.ScaleRatio = stof(Ratio);
		ProcessMapInfo::WriteFile(FilePath, CurStruct);
	}
	else
	{
		ProcessMapInfo::WriteAllFile(FilePath, EditorSturctInfo);
	}
}

void MapEditorWindow::ReadActor(std::shared_ptr<GameEngineLevel> Level)
{

	std::vector<SponeMapActor> AllInfo = ProcessMapInfo::OpenFile(FilePath);
	std::shared_ptr<GameEngineActor> LoadActor = nullptr;
	for (SponeMapActor _str : AllInfo)
	{
		int readindex = _str.ActorIndex;

		if (static_cast<int>(ContentsActorType::GameEngineActor) == static_cast<int>(_str.ActorType))
		{
			if (nullptr == GameEngineFBXMesh::Find(_str.FBXName))
			{
				MsgTextBox("FBX매쉬를 선택하지 않았습니다");
				return;
			}
			LoadActor = Level->CreateActor<GameEngineActor>();
			std::shared_ptr<GameEngineFBXRenderer> pRenderer = LoadActor->CreateComponent< GameEngineFBXRenderer>();
			pRenderer->SetFBXMesh(_str.FBXName, MeterialName);
		}
		else if (static_cast<int>(ContentsActorType::TestObject) == static_cast<int>(_str.ActorType))
		{
			LoadActor = Level->CreateActor<TestObject>();
		}
		else if (static_cast<int>(ContentsActorType::Player) == static_cast<int>(_str.ActorType))
		{
			LoadActor = Level->CreateActor<Player>();
		}
		else
		{
			return;
		}
		LoadActor->SetOrder(static_cast<int>(_str.ActorIndex));
		LoadActor->GetTransform()->SetLocalScale(_str.LocScale);
		LoadActor->GetTransform()->SetLocalRotation(_str.LocRot);
		LoadActor->GetTransform()->SetLocalPosition(_str.LocPos);
		//ratio
		//IsMoveable
		if (EditorActorInfo.end() != EditorActorInfo.find(readindex))
		{
			MsgTextBox("동일한 인덱스에 액터가 존재합니다");
			return;
		}
		EditorSturctInfo[readindex] = _str;
		EditorActorInfo[readindex] = LoadActor;
		recvUnit = std::to_string(_str.ScaleRatio);
		lastindex = lastindex > readindex ? lastindex : readindex + 1;
		LoadActor = nullptr;
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
	PinedActor = nullptr;
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
	if (ImGui::Button("Input Path"))
	{
		FilePath.SetPath(FilePath.GetFullPath() +"\\" + FileName);
		ProcessMapInfo::CreatPathFile(FilePath);
		if (false == FilePath.IsExists())
		{
			MsgAssert("파일이 생성되지 않았습니다;");
			return;
		}
		//if (nullptr == PinedActor)
		//{
		//	PinedActor = Level->CreateActor<GameEngineActor>(99);
		//	std::shared_ptr<GameEngineFBXRenderer> Mesh = PinedActor->CreateComponent< GameEngineFBXRenderer>();
		//	Mesh->SetFBXMesh("ActorFrozenBlock.fbx", "MeshTexture");
		//}
		IsSetFilePath = true;
		ReadActor(Level);
		return;
	}
}

void MapEditorWindow::Explorer(std::string& _Value)
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Mesh");
	std::string Initpath = NewDir.GetPath().GetFullPath();
	std::wstring strFolderPath = GameEngineString::AnsiToUniCode(Initpath);


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
	_Value = GameEngineString::UniCodeToAnsi(filename);
}
