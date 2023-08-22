#include "PreCompileHeader.h"
#include "MapEditorLevel.h"

#include "MapEditorWindow.h"

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
	GetMainCamera()->GetTransform()->SetLocalRotation({ 90.0f, 0.0f, 0.0f });

	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 2000.0f, 0.0f });
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
