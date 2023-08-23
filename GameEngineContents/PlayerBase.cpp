#include "PreCompileHeader.h"
#include "PlayerBase.h"

//이 클래스를 상속받아서, 종류에 따라 다르게 메쉬가 세팅될거임

//부메랑은 플레이어가 weak_ptr로 받아서 멤버변수로 보유하고 있어야 하나?
//던질때마다 새로 Create하는건지, 계속 주워서 재활용하는건지 생각해야됨

PlayerBase::PlayerBase()
{
}

PlayerBase::~PlayerBase()
{
}

void PlayerBase::SetMesh()
{
	if (Type == "")
	{
		return;
	}

	PlayerMesh = CreateComponent<GameEngineFBXRenderer>();
	//PlayerMesh->SetFBXMesh(Type + ".fbx", "MeshAniTexture");
	//PlayerMesh->CreateFBXAnimation("WalkOne", "Banana.fbx");
	//PlayerMesh->CreateFBXAnimation();
}

void PlayerBase::SetCollision()
{
	//메쉬의 크기에 따라 가변적으로 변하게 해야하는데,
	//아마 모든 플레이어 메쉬가 크기가 같을 듯?
	//나중에 확인하고 만들기로.
}

void PlayerBase::CreateKey()
{
	if (1 /*이동키가 없다면*/)
	{
		//이동키 생성
	}
	
	if (1 /*공격키가 없다면*/)
	{
		//공격키 생성
	}

	//등등 키 생성
}

int PlayerBase::GetKeyInput()
{	
	//키입력에 따라 static_cast<int>(MoveTypes) 반환
	return -1;
}	
	
void PlayerBase::StatusUpdate()
{
	int KetStatus = GetKeyInput();
	
	switch (KetStatus)
	{
	case static_cast<int>(MoveTypes::Idle):

		if (isPlayerUpdate(MoveTypes::Idle).has_value() == false)
		{
			IdleStart();
			UpdateList[Status] = std::bind(&PlayerBase::IdleUpdate, this, std::placeholders::_1);
		}
		break;

	case static_cast<int>(MoveTypes::Move):

		if (isPlayerUpdate(MoveTypes::Move).has_value() == false)
		{
			MoveStart();
			UpdateList[Status] = std::bind(&PlayerBase::MoveUpdate, this, std::placeholders::_1);
		}
		break;

	case static_cast<int>(MoveTypes::Throw):

		if (isPlayerUpdate(MoveTypes::Throw).has_value() == false)
		{
			ThrowStart();
			UpdateList[Status] = std::bind(&PlayerBase::ThrowUpdate, this, std::placeholders::_1);
		}
		break;

	case static_cast<int>(MoveTypes::Cut):

		if (isPlayerUpdate(MoveTypes::Cut).has_value() == false)
		{
			CutStart();
			UpdateList[Status] = std::bind(&PlayerBase::CutUpdate, this, std::placeholders::_1);
		}
		break;

	case static_cast<int>(MoveTypes::Die):

		if (isPlayerUpdate(MoveTypes::Die).has_value() == false)
		{
			DieStart();
			UpdateList[Status] = std::bind(&PlayerBase::DieUpdate, this, std::placeholders::_1);
		}
		break;

	}
}

void PlayerBase::PlayerUpdate(float _Delta)
{
	if (UpdateList.size() == 0)
	{
		return;
	}

	std::map<int, std::function<bool(float)>>::iterator StartFunc = UpdateList.begin();
	std::map<int, std::function<bool(float)>>::iterator EndFunc = UpdateList.end();

	while (StartFunc != EndFunc)
	{
		std::function<bool(float)> Func = StartFunc->second;

		if (Func != nullptr && Func(_Delta) == true)
		{
			StartFunc = UpdateList.erase(StartFunc);
			continue;
		}

		StartFunc++;
	}
}

std::optional<std::function<bool(float)>> PlayerBase::isPlayerUpdate(int _MoveTypes)
{
	if (UpdateList.find(_MoveTypes) != UpdateList.end())
	{
		return UpdateList[_MoveTypes];
	}
	else
	{
		return std::nullopt;
	}
}

void PlayerBase::GetItem()
{
	//아이템 충돌체가 있는 액터에서, 충돌검사후 이 함수를 호출
	//호출되면, ItemQueue에 해당 아이템의 Enum을 Push
	
	//이후, ItemQueue의 front에 있는 Enum에 따라, Throw혹은 Cut이 Switch문으로 다르게 동작
}

void PlayerBase::IdleStart()
{
	Status = static_cast<int>(MoveTypes::Idle);

	//상태에 진입할 때 설정해야할 기초상태로 초기화
}

void PlayerBase::MoveStart()
{
	Status = static_cast<int>(MoveTypes::Move);
}

void PlayerBase::ThrowStart()
{
	Status = static_cast<int>(MoveTypes::Throw);
}

void PlayerBase::CutStart()
{
	Status = static_cast<int>(MoveTypes::Cut);
}

void PlayerBase::DieStart()
{
	Status = static_cast<int>(MoveTypes::Die);
}

bool PlayerBase::IdleUpdate(float _Delta)
{
	if(1 /*업데이트 중이면*/)
	{
		return false;
	}
	else
	{
		//업데이트가 끝나는 순간
		return true;
		//true를 반환하면, PlayerUpdate에서 Erase하면서 업데이트 멈춤.
	}
}

bool PlayerBase::MoveUpdate(float _Delta)
{
	return false;
}

bool PlayerBase::ThrowUpdate(float _Delta)
{
	return false;
}

bool PlayerBase::CutUpdate(float _Delta)
{
	return false;
}

bool PlayerBase::DieUpdate(float _Delta)
{
	return false;
}

