#include "PreCompileHeader.h"

#include "BossLevelTestObject.h";
#include "Boss_OldCrow.h";

#include "BossTestLevel.h"



BossTestLevel::BossTestLevel() 
{
}

BossTestLevel::~BossTestLevel() 
{
}

void BossTestLevel::Start()
{

}

void BossTestLevel::Update(float _DeltaTime)
{
}


void BossTestLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Perspective);

	GetMainCamera()->GetTransform()->SetLocalRotation({ 90.0f, 0.0f, 0 });
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 500.0f, 0.0f });

	//std::shared_ptr<BossLevelTestObject> TestObject = CreateActor<BossLevelTestObject>();
	//TestObject->GetTransform()->SetLocalScale({ 100, 100, 100 });
	//TestObject->GetTransform()->SetLocalPosition({ 0, 0, -10 });

	std::shared_ptr<Boss_OldCrow> BossTestObject = CreateActor<Boss_OldCrow>();
	//BossTestObject->Init();
	//BossTestObject->GetTransform()->SetLocalPosition({ 0, 0, -10 });
}

void BossTestLevel::LevelChangeEnd()
{

}
