#include "PrecompileHeader.h"
#include "UITestLevel.h"
#include "Mouse.h"
#include "SkillSlot.h"
#include "HpBar.h"
#include "MpBar.h"

#include "MyTest.h"
#include "Player.h"

#include <GameEngineCore/GameEngineCoreWindow.h>

std::shared_ptr<class GameEngineLight> UITestLevel::NewLight;

UITestLevel::UITestLevel()
{
}

UITestLevel::~UITestLevel()
{
}

void UITestLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -1000.0f });
	//GetMainCamera()->GetTransform()->SetLocalPosition({ 0.0f, 600.0f, -1000.0f });
	//GetMainCamera()->GetTransform()->SetLocalRotation({ 45.0f, 0.0f, 0.0f });

	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	NewLight = CreateActor<GameEngineLight>();

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

	CreateScene();

	GameEngineCoreWindow::AddDebugRenderTarget(0, "AllRenderTarget", GetMainCamera()->GetCamAllRenderTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(1, "LightRenderTarget", GetMainCamera()->GetDeferredLightTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(2, "MainCameraForwardTarget", GetMainCamera()->GetCamForwardTarget());
	GameEngineCoreWindow::AddDebugRenderTarget(3, "DeferredTarget", GetMainCamera()->GetCamDeferrdTarget());

	//CreateActor<SkillSlot>();
	//CreateActor<HpBar>();
	//CreateActor<MpBar>();
}

void UITestLevel::Update(float _DeltaTime)
{
}

void UITestLevel::LevelChangeStart()
{
	CreateActor<MyTest>();
	//CreateActor<Mouse>();


}

void UITestLevel::LevelChangeEnd()
{
}
