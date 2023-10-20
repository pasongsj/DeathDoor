#include "PreCompileHeader.h"
#include "PlayerTestLevel.h"
#include "PhysXCapsuleComponent.h"

#include "Player.h"
#include "MonsterAnimationTest.h"
#include "EnemyFirePlant.h"

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

	//LevelInit(); <<이걸로 통합됐어요
	//CreateUI();
	SetPostPrecessEffect();

	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -1000.0f });

	CreateActor<MonsterAnimationTest>();
}

void PlayerTestLevel::LevelChangeEnd()
{
}
