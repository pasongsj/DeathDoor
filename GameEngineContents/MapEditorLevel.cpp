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
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
}

void MapEditorLevel::Update(float _DeltaTime)
{
}

void MapEditorLevel::LevelChangeStart()
{
	MapEditorWindow::EditorGUI->On();

}

void MapEditorLevel::LevelChangeEnd()
{
	MapEditorWindow::EditorGUI->Off();
}
