#include "PrecompileHeader.h"
#include "TestLevel.h"

#include "TestObject.h"
#include "Player.h"
#include "ServerWindow.h"

TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start()
{
	CreateActor<Player>();
}

void TestLevel::Update(float _DeltaTime)
{

}

void TestLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

}

void TestLevel::LevelChangeEnd()
{
}
