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
	PlayerMesh->SetFBXMesh(Type, "MeshTexture");
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
	Status = GetKeyInput();
	
	switch (Status)
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

void PlayerBase::IdleStart()
{
}

void PlayerBase::MoveStart()
{
}

void PlayerBase::ThrowStart()
{
}

void PlayerBase::CutStart()
{
}

void PlayerBase::DieStart()
{
}

bool PlayerBase::IdleUpdate(float _Delta)
{
	if(1 /*업데이트 중이면*/)
	{
		return false;
	}
	else
	{
		//업데이트가 끝나면
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

