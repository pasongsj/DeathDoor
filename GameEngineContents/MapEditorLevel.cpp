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

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation({ 35.0f, 0.0f, 0.0f });
	GetMainCamera()->GetTransform()->SetLocalPosition( float4{ 2800 , 230 , -6300 });
	
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
