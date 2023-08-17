#include "PrecompileHeader.h"
#include "MapEditorWindow.h"
#include "TestObject.h"
#include "Player.h"



#include "ProcessMapInfo.h"
#include "MapEditGlobalValue.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>


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
	FilePath.SetPath(Dir.GetPlusFileName("ContentResources\\tmp\\test.csv").GetFullPath());

}

void MapEditorWindow::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{
	ImGui::Text("Unit Scale : %f", UnitScale);
	ImGui::InputText("##UnitScale", &recvUnit[0], recvUnit.size());
	ImGui::SameLine();
	if (ImGui::Button("Change Unit") && Level.get() != GetLevel())
	{
		if (recvUnit.size() > 0)
		{
			UnitScale = std::stof(recvUnit);
		}
	}

	ImGui::Separator();
	if (false == ReadCSV && ImGui::Button("Read Actor File") && Level.get() != GetLevel())
	{
		ReadActor(Level);
		ReadCSV = true;
		return;
	}
	ImGui::SameLine();
	if (ImGui::Button("Clear Actor File") && Level.get() != GetLevel())
	{
		ClearActors();
		return;
	}
	ImGui::Separator();


	if (nullptr == CurActor)
	{
		const char* items[] = { "GameEngineActor", "TestObject","Player"};
		static const char* current_item = NULL;

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




		ImGui::Text("CreateActor :");
		ImGui::SameLine();
		if (ImGui::Button("CreateActor") && Level.get() != GetLevel())
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
			ResetValue();
		}
	}
	else //(-1 != index)
	{
		ImGui::Text("CurActorIndex :");
		ImGui::SameLine();
		ImGui::Text(std::to_string(lastindex).c_str());
		//
		ImGui::Separator();
		//
		TransformData Trans = CurActor->GetTransform()->GetTransDataRef();
		ImGui::Text("TransformData");

		{
			//scale
			ImGui::Text("LocalRatio :%f", Trans.LocalScale.x / 1.0f);
			ImGui::InputText("Scale Ratio", &Ratio[0], Ratio.size());
			if (ImGui::Button("Change") && Level.get() != GetLevel())
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
			if (ImGui::Button("-RotX") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ -UnitScale ,0 });
				isChangeRot = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("+RotX") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ UnitScale ,0 });
				isChangeRot = true;
			}
			ImGui::SameLine();

			if (ImGui::Button("-RotY") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ 0, -UnitScale });
				isChangeRot = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("+RotY") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ 0, UnitScale });
				isChangeRot = true;
			}
			ImGui::SameLine();

			if (ImGui::Button("-RotZ") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ 0,0 - UnitScale });
				isChangeRot = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("+RotZ") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalRotation(float4{ 0,0,UnitScale });
				isChangeRot = true;
			}

			if (true == CurRot.IsZero() || true == isChangeRot)
			{
				CurRot = CurActor->GetTransform()->GetLocalRotation();
			}
			ImGui::SliderFloat3("Rotation", &CurRot.x, -360.0f, 360.0f);
			
			if (ImGui::Button("Change Slider Rotion") && Level.get() != GetLevel())
			{
				CurRot.w = 1;
				CurActor->GetTransform()->SetLocalRotation(CurRot);
			}
			ImGui::InputText("RotX", &RevRotationX[0], RevRotationX.size());

			ImGui::InputText("RotY", &RevRotationY[0], RevRotationY.size());

			ImGui::InputText("RotZ", &RevRotationZ[0], RevRotationZ.size());

			if (ImGui::Button("Change Rotion") && Level.get() != GetLevel())
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
			if (ImGui::Button("-PosX") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ -UnitScale ,0 });
				isChangePos = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("+PosX") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ UnitScale ,0 });
				isChangePos = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("-PosY") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ 0, -UnitScale ,0 });
				isChangePos = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("+PosY") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ 0, UnitScale ,0 });
				isChangePos = true;
			}
			ImGui::SameLine();

			if (ImGui::Button("-PosZ") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ 0,0, -UnitScale });
				isChangePos = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("+PosZ") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->AddLocalPosition(float4{ 0,0,UnitScale });
				isChangePos = true;
			}

			if (true == CurPos.IsZero() || true == isChangePos)
			{
				CurPos = CurActor->GetTransform()->GetLocalPosition();
			}
			ImGui::SliderFloat3("Position", &CurPos.x, -UnitScale * 100, UnitScale * 100);
			if (ImGui::Button("Change Slider Position") && Level.get() != GetLevel())
			{
				CurPos.w = 1;
				CurActor->GetTransform()->SetLocalPosition(CurPos);
			}


			ImGui::InputText("PosX", &RevPositionX[0], RevPositionX.size());

			ImGui::InputText("PosY", &RevPositionY[0], RevPositionY.size());

			ImGui::InputText("PosZ", &RevPositionZ[0], RevPositionZ.size());

			if (ImGui::Button("Change Position") && Level.get() != GetLevel())
			{
				CurActor->GetTransform()->SetLocalPosition(float4{ std::stof(RevPositionX),std::stof(RevPositionY) ,std::stof(RevPositionZ) });
			}
		}

		ImGui::Separator();

		//ImGui::Text("Save :");
		//ImGui::SameLine();

		if (ImGui::Button("ResetTrans") && Level.get() != GetLevel())
		{
			CurActor->GetTransform()->SetLocalScale(float4::ONE);
			CurActor->GetTransform()->SetLocalRotation(float4::ZERO);
			CurActor->GetTransform()->SetLocalPosition(float4::ZERO);
		}
		if (ImGui::Button("Save") && Level.get() != GetLevel())
		{
			SaveActors();
			CurActor = nullptr;
		}
		if (ImGui::Button("Remove") && Level.get() != GetLevel())
		{
			CurActor->Death();
			CurActor = nullptr;
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
	std::map<std::string, int> typeconvertor = { {"GameEngineActor",static_cast<int>(ContentsActorType::GameEngineActor)},
		{"TestObject",static_cast<int>(ContentsActorType::TestObject)},{"Player",static_cast<int>(ContentsActorType::Player)} };
	SponeMapActor CurActorSturct;
	CurActorSturct.ActorIndex = lastindex;
	CurActorSturct.ActorType = typeconvertor[ActorType];
	CurActorSturct.ActorOrder = 0; // 임시
	CurActorSturct.LocScale = CurActor->GetTransform()->GetLocalScale();
	CurActorSturct.LocRot = CurActor->GetTransform()->GetLocalRotation();
	CurActorSturct.LocPos = CurActor->GetTransform()->GetLocalPosition();
	CurActorSturct.ScaleRatio = stof(Ratio);
	CurActorSturct.IsMoveable = false;
	CurActorSturct.FBXName = FBXName;
	CurActorSturct.FBXNameLen = FBXName.size();
	//GameEngineDirectory Dir;
	//Dir.MoveParentToDirectory("ContentResources");
	//ProcessMapInfo::RWProcessInst->WriteFile(Dir.GetPlusFileName("ContentResources\\tmp\\test.csv").GetFullPath(), CurActorSturct);
	ProcessMapInfo::RWProcessInst->WriteFile(FilePath, CurActorSturct);
}

void MapEditorWindow::ReadActor(std::shared_ptr<GameEngineLevel> Level)
{
	//GameEngineDirectory Dir;
	//Dir.MoveParentToDirectory("ContentResources");
	//std::vector<SponeMapActor> AllInfo = ProcessMapInfo::RWProcessInst->OpenFile(Dir.GetPlusFileName("ContentResources\\tmp\\test.csv").GetFullPath());
	std::vector<SponeMapActor> AllInfo = ProcessMapInfo::RWProcessInst->OpenFile(FilePath);
	std::shared_ptr<GameEngineActor> LoadActor = nullptr;
	for (SponeMapActor _str : AllInfo)
	{
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
		++lastindex;
		LoadActor = nullptr;
	}
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
}


void MapEditorWindow::ClearActors()
{
	//GameEngineDirectory Dir;
	//Dir.MoveParentToDirectory("ContentResources");
	//Dir.GetPlusFileName("ContentResources\\tmp\\test.csv").GetFullPath();
	//ProcessMapInfo::RWProcessInst->CpyAndClear(Dir.GetPlusFileName("ContentResources\\tmp\\test.csv").GetFullPath());
	ProcessMapInfo::RWProcessInst->CpyAndClear(FilePath);
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
