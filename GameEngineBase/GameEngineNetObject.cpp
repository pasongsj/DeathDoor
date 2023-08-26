#include "PrecompileHeader.h"
#include "GameEngineNetObject.h"

std::atomic<int> GameEngineNetObject::AtomicObjectID;
std::mutex GameEngineNetObject::ObjectLock;
std::map<int, GameEngineNetObject*> GameEngineNetObject::AllNetObjects;

GameEngineNetObject::GameEngineNetObject()
{
}

GameEngineNetObject::~GameEngineNetObject()
{
}

void GameEngineNetObject::InitNetObject(int _ObjectID, GameEngineNet* _Net)
{
	ObjectID = _ObjectID;
	ObjectLock.lock();
	AllNetObjects.insert(std::pair<int, GameEngineNetObject*>(ObjectID, this));
	ObjectLock.unlock();

	Net = _Net;
}

void GameEngineNetObject::PushPacket(std::shared_ptr<GameEnginePacket> _Packet)
{
	Packets.push_back(_Packet);
}

void GameEngineNetObject::SendAllPacket(float DeltaTime)
{
	static float SendInterval = 0.0f;
	SendInterval += DeltaTime;
	if (SendInterval <= 1.0f / 60.0f)
	{
		return;
	}

	SendInterval -= 1.0f / 60.0f;
	for (std::pair<int,GameEngineNetObject*> NetObj : AllNetObjects)
	{
		GameEngineNetObject* CurObj = (NetObj.second);
		if (true == CurObj->IsNet())
		{
			CurObj->SendNetPacket();
		}
	}
}
