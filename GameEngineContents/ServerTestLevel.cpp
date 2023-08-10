#include "PrecompileHeader.h"
#include "ServerTestLevel.h"

#include "TestObject.h"
#include "ServerWindow.h"

ServerTestLevel::ServerTestLevel() 
{
}

ServerTestLevel::~ServerTestLevel() 
{
}

void ServerTestLevel::Start()
{
	CreateActor<TestObject>();
}

void ServerTestLevel::Update(float _DeltaTime)
{
}

void ServerTestLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	ServerWindow::ServerGUI->On();
}

void ServerTestLevel::LevelChangeEnd()
{
	ServerWindow::ServerGUI->Off();
}
