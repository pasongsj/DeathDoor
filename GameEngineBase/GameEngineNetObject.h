#pragma once
#include "GameEngineNet.h"

// 서버입장에서는 유저든
// 내가 가진 몬스터든 결론적으로 본다면 결국 오브젝트일뿐이다.
// 몬스터들은 

enum class NetControlType
{
	None,
	UserControl,
	ServerControl,
};

// 설명 :
class GameEngineNetObject
{
public:
	static bool IsNetObject(int _Id)
	{
		return AllNetObjects.contains(_Id);
	}


	// constrcuter destructer
	GameEngineNetObject();
	~GameEngineNetObject();

	// delete Function
	GameEngineNetObject(const GameEngineNetObject& _Other) = delete;
	GameEngineNetObject(GameEngineNetObject&& _Other) noexcept = delete;
	GameEngineNetObject& operator=(const GameEngineNetObject& _Other) = delete;
	GameEngineNetObject& operator=(GameEngineNetObject&& _Other) noexcept = delete;

	static int CreateServerID()
	{
		return ++AtomicObjectID;
	}

	void InitNetObject(int _ObjectID, GameEngineNet* _Net);

	void SetControl(NetControlType _ControlType)
	{
		ControlType = _ControlType;
	}

	NetControlType  GetControlType()
	{
		return ControlType;
	}

	int GetNetObjectID()
	{
		return ObjectID;
	}

	bool IsNet()
	{
		return nullptr != Net;
	}

	GameEngineNet* GetNet()
	{
		return Net;
	}

	void PushPacket(std::shared_ptr<GameEnginePacket> _Packet);

protected:

private:
	static std::atomic<int> AtomicObjectID;
	static std::mutex ObjectLock;
	static std::map<int, GameEngineNetObject*> AllNetObjects;

	NetControlType ControlType = NetControlType::None;
	int ObjectID = -1;

	GameEngineNet* Net = nullptr;

	std::list<std::shared_ptr<GameEnginePacket>> Packets;
};

