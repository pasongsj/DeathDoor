#include "PreCompileHeader.h"
#include "PlayerTestLevel.h"
#include "PhysXCapsuleComponent.h"

#include "Player.h"
#include "MonsterAnimationTest.h"
#include "EnemyFirePlant.h"
#include "CapsulTestActor.h"

PlayerTestLevel::PlayerTestLevel()
{
}

PlayerTestLevel::~PlayerTestLevel()
{
}

void PlayerTestLevel::Start()
{
	CreateScene();
}

void PlayerTestLevel::Update(float _DeltaTime)
{
}


void PlayerTestLevel::LevelChangeStart()
{
	CreateActor<GameEngineLight>();

	GetMainCamera()->SetProjectionType(CameraType::Perspective);

	//GetMainCamera()->GetTransform()->SetLocalRotation({ 0.0f, 0.0f, 0 });
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -1000.0f });

	//CreateActor<MonsterAnimationTest>();
	CreateActor<CapsulTestActor>();
	//CreateActor<EnemyFirePlant>();
}

void PlayerTestLevel::LevelChangeEnd()
{
}
