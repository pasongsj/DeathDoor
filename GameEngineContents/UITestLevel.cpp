#include "PrecompileHeader.h"
#include "UITestLevel.h"
#include "Mouse.h"
#include "SkillSlot.h"
#include "HpBar.h"
#include "MpBar.h"

UITestLevel::UITestLevel()
{
}

UITestLevel::~UITestLevel()
{
}

void UITestLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -40.0f });
	GetMainCamera()->GetTransform()->SetLocalRotation({ 0.0f, -30.0f, 0.0f });

	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Mesh");
	NewDir.Move("UI");

	std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".FBX" });

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFBXMesh::Load(Files[i].GetFullPath());
	}

	//CreateActor<Mouse>();
	CreateActor<SkillSlot>();
	CreateActor<HpBar>();
	CreateActor<MpBar>();
}

void UITestLevel::Update(float _DeltaTime)
{
}

void UITestLevel::LevelChangeStart()
{
}

void UITestLevel::LevelChangeEnd()
{
}
