#include "PrecompileHeader.h"
#include "MapEditorWindow.h"
#include "TestObject.h"

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



	if (nullptr == CurActor)
	{
		ImGui::Text("CreateActor :");
		ImGui::SameLine();
		if (ImGui::Button("CreateActor") && Level.get() != GetLevel())
		{
			++lastindex;
			ResetValue();
			CurActor = Level->CreateActor<TestObject>();
			std::shared_ptr<GameEngineFBXRenderer> pRenderer = CurActor->CreateComponent< GameEngineFBXRenderer>();
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
			ImGui::SameLine();
			if (ImGui::Button("Change") && Level.get() != GetLevel())
			{
				float Rat = std::stof(Ratio);
				CurActor->GetTransform()->SetLocalScale(float4{ Rat, Rat, Rat });
			}
		}
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
			ImGui::SameLine();
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
				CurActor->GetTransform()->AddLocalPosition(float4{ 0,0 - UnitScale });
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
			ImGui::SameLine();
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

		ImGui::Text("Save :");
		ImGui::SameLine();
		if (ImGui::Button("Save") && Level.get() != GetLevel())
		{
			CurActor = nullptr;
		}
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
