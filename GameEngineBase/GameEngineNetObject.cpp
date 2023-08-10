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



// 서버의 관리를 받겠다는것
void GameEngineNetObject::InitServerObject()
{
	ObjectID = ++AtomicObjectID;
	ObjectLock.lock();
	AllNetObjects.insert(std::pair<int, GameEngineNetObject*>(ObjectID, this));
	ObjectLock.unlock();
	ControlType = NetControlType::UserControl;
}

void GameEngineNetObject::InitClientObject(int _ObjectID)
{
	ObjectID = _ObjectID;
	ObjectLock.lock();
	AllNetObjects.insert(std::pair<int, GameEngineNetObject*>(ObjectID, this));
	ObjectLock.unlock();
	ControlType = NetControlType::ServerControl;
}