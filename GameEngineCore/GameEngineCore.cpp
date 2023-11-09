#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEngineBase\GameEngineThread.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineBase\GameEngineTime.h>
#include "GameEngineDevice.h"
#include "GameEngineVideo.h"
#include "GameEngineGUI.h"
#include "GameEngineLevel.h"

#include <GameEngineContents/PhysXManager.h>
#include <GameEngineBase/GameEngineNetObject.h>

GameEngineThreadJobQueue GameEngineCore::JobQueue;

std::map<std::string, std::shared_ptr<GameEngineLevel>> GameEngineCore::LevelMap;
std::shared_ptr<GameEngineLevel> GameEngineCore::MainLevel = nullptr;
std::shared_ptr<GameEngineLevel> GameEngineCore::NextLevel = nullptr;

std::shared_ptr<class GameEngineLevel> GameEngineCore::CurLoadLevel = nullptr;
std::function<void()> GameEngineCore::RcvPacket = nullptr;


float GameEngineCore::UpdateTime = 0.f;



GameEngineCore::GameEngineCore() 
{
}

GameEngineCore::~GameEngineCore() 
{
}

void GameEngineCore::Release()
{
	NextLevel = nullptr;
	MainLevel = nullptr;
	CurLoadLevel = nullptr;
	LevelMap.clear();
}

void GameEngineCore::EngineStart(std::function<void()> _ContentsStart)
{
	// 코어이니셜라이즈
	// Rect Box

	if (false == GameEngineInput::IsKey("GUISwitch"))
	{
		GameEngineInput::CreateKey("GUISwitch", VK_F8);
	}
	

	JobQueue.Initialize("EngineJobQueue");

	GameEngineDevice::Initialize();

	CoreResourcesInit();
	PhysXManager::GetInst()->Init();
	GameEngineGUI::Initialize();

	if (nullptr == _ContentsStart)
	{
		MsgAssert("시작 컨텐츠가 존재하지 않습니다.");
	}
	_ContentsStart();
}

void GameEngineCore::EngineUpdate() 
{
	if (nullptr != NextLevel)
	{
		std::shared_ptr<GameEngineLevel> PrevLevel = MainLevel;

		if (nullptr != MainLevel)
		{
			MainLevel->LevelChangeEnd();
			MainLevel->ActorLevelChangeEnd();
			MainLevel->ReleaseLevelRenderTarget(); // 생성했던 렌더타겟 삭제
		}

		MainLevel = NextLevel;

		if (nullptr != MainLevel)
		{
			CurLoadLevel = MainLevel;
			PhysXManager::GetInst()->ChangeScene(MainLevel->GetName()); // PhysX Scene변경 없으면 null로 만들어서 사용불가
			MainLevel->LevelChangeStart();
			MainLevel->InitLevelRenderTarget(); // 렌더타겟 실제로 생성
			MainLevel->ActorLevelChangeStart(); 
		}

		NextLevel = nullptr;
		GameEngineTime::GlobalTime.Reset();
	}

	if (nullptr == MainLevel)
	{
		MsgAssert("아무런 레벨도 동작하지 않고 있습니다.");
		return;
	}

	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();

	if (TimeDeltaTime<=0.f) // PhysX는 Simulate시 시간이 0 이면 오류를 뿜어서 리턴
	{
		return;
	}


#ifdef _DEBUG

	if (TimeDeltaTime > 1 / 30.0f)
	{
		TimeDeltaTime = 1 / 30.0f;
	}
#endif // _DEBUG

	UpdateTime += TimeDeltaTime;

	PhysXManager::GetInst()->Simulate(TimeDeltaTime); // PhysX Simulate는 DeltaTime으로 돌게함

	//if (1.f/120.f > UpdateTime) // EngineUpdate는 120프레임으로 돌게함
	//{
	//	return;
	//}

	TimeDeltaTime = UpdateTime;
	UpdateTime = 0.f;

	if (nullptr != RcvPacket)
	{
		RcvPacket();
	}
	GameEngineInput::Update(TimeDeltaTime);
	GameEngineSound::SoundUpdate();

	// 업데이트가 일어나는 동안 로드가 된애들

	MainLevel->TimeEvent.Update(TimeDeltaTime);
	MainLevel->AccLiveTime(TimeDeltaTime);
	MainLevel->Update(TimeDeltaTime);
	MainLevel->ActorUpdate(TimeDeltaTime);
	// CurLoadLevel = nullptr;

	// 서버에 패킷을 보내는 위치 (server packet send)
	GameEngineNetObject::SendAllPacket(TimeDeltaTime);
	//MainLevel->SendActorPacket(TimeDeltaTime);

	GameEngineVideo::VideoState State = GameEngineVideo::GetCurState();
	if (State != GameEngineVideo::VideoState::Running)
	{
		GameEngineDevice::RenderStart();
		MainLevel->Render(TimeDeltaTime);
		GameEngineDevice::RenderEnd();
	}

	MainLevel->ActorRelease();
}

void GameEngineCore::EngineEnd(std::function<void()> _ContentsEnd)
{
	if (nullptr == _ContentsEnd)
	{
		MsgAssert("끝 컨텐츠가 존재하지 않습니다.");
	}

	_ContentsEnd();
	PhysXManager::GetInst()->Release();
	GameEngineGUI::Release();

	LevelMap.clear();
	CoreResourcesEnd();
	Release();
	

	GameEngineDevice::Release();
	GameEngineWindow::Release();

}

void GameEngineCore::Start(HINSTANCE _instance,  std::function<void()> _Start, std::function<void()> _End, float4 _Pos, float4 _Size)
{
	GameEngineDebug::LeakCheck();

	if (false == GameEngineInput::IsKey("EngineMouseLeft"))
	{
		GameEngineInput::CreateKey("EngineMouseLeft", VK_LBUTTON);
		GameEngineInput::CreateKey("EngineMouseRight", VK_RBUTTON);
	}

	GameEngineWindow::WindowCreate(_instance, "Death's Door", _Size, _Pos);
	GameEngineWindow::WindowLoop(std::bind(GameEngineCore::EngineStart, _Start), GameEngineCore::EngineUpdate, std::bind(GameEngineCore::EngineEnd, _End));
}

std::shared_ptr<GameEngineLevel> GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (LevelMap.end() == LevelMap.find(UpperName))
	{
		MsgAssert("존재하지 않는 레벨로 체인지 하려고 했습니다.");
		return nullptr;
	}

	NextLevel = LevelMap[UpperName];
	
	return NextLevel;
}

void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level,const std::string_view& _Name) 
{
	_Level->SetName(_Name);
	CurLoadLevel = _Level;
	_Level->Level = _Level.get();
	_Level->Start();
	CurLoadLevel = nullptr;
}

