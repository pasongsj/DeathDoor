#include "PreCompileHeader.h"
#include "MapEditorLevel.h"

#include "MapEditorWindow.h"
#include <GameEngineCore/GameEngineLight.h>

MapEditorLevel::MapEditorLevel()
{
}

MapEditorLevel::~MapEditorLevel()
{
}
void MapEditorLevel::Start()
{
	SetLevelType(PacketLevelType::MapEditorLevel);

	// 오피스
	// float4 { 35.0f, 0.0f, 0.0f };
	// float4 { 2800.0f, 230.0f, -6300.0f };

	// 포트리스 
	// 


	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation(float4{ 45 , 0 , 0 });
	GetMainCamera()->GetTransform()->SetLocalPosition(float4{ -450, 1700, -1200 });
	
	CreateActor<GameEngineLight>();
}

void MapEditorLevel::Update(float _DeltaTime)
{
	float4 Pos = GetMainCamera()->GetTransform()->GetLocalPosition();
}

void MapEditorLevel::LevelChangeStart()
{
	MapEditorWindow::EditorGUI->On();

}

void MapEditorLevel::LevelChangeEnd()
{
	MapEditorWindow::EditorGUI->Off();
}
