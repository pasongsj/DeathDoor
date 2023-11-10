#include "PreCompileHeader.h"
#include "PlayerTestLevel.h"
#include "PhysXCapsuleComponent.h"

#include "Player.h"
#include "MonsterAnimationTest.h"
#include "EnemyFirePlant.h"
#include "BossFrogSoul.h"

PlayerTestLevel::PlayerTestLevel()
{
}

PlayerTestLevel::~PlayerTestLevel()
{
}

void PlayerTestLevel::Start()
{
}

void PlayerTestLevel::Update(float _DeltaTime)
{
	int  a = 0;
}


void PlayerTestLevel::LevelChangeStart()
{
	CreateScene();

	CreateActor<GameEngineLight>();

	//LevelInit(); 
	//CreateUI();

	CreateIMGUIDebugRenderTarget();
	SetPostPrecessEffect({ 800, 450, 800, 450 });

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -500.0f });

	CreateActor<MonsterAnimationTest>();
}

void PlayerTestLevel::LevelChangeEnd()
{
}
