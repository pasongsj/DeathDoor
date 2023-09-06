#pragma once
#include "ParticleRenderer.h"
#include "ParticleStruct.h"

#include <GameEngineCore/GameEngineActor.h>

class ParticleManager : public GameEngineActor
{

public:

	ParticleManager();
	~ParticleManager();

	ParticleManager(const ParticleManager& _Other) = delete;
	ParticleManager(ParticleManager&& _Other) noexcept = delete;
	ParticleManager& operator=(const ParticleManager& _Other) = delete;
	ParticleManager& operator=(ParticleManager&& _Other) noexcept = delete;

	//파티클 매쉬 세팅
	void SetMeshName(const std::string_view _Name)
	{
		MeshName = _Name;
	}

	//파티클 생성을 켜는 것
	void ParticleOn()
	{
		isOn = true;
	}

	//파티클 생성을 일시적으롬 멈추는 것 
	void ParticleOff()
	{
		isOn = false;
	}

	//일회용으로 설정
	//Start에서 이 설정을 켜고, 방출 개수(MaxParticle) 만큼 방출이 완료되면 더이상 방출하지 않고 액터가 Death함.
	void SetDisposable()
	{
		isDisposable = true;
	}

protected:
	//액터 내부에서 방출시간을 재는 용도
	float EmitCount = 0.0f;
	
	//현재파티클개수
	int CurParticle = 0;

	//지금까지 만들어진 총 개수
	int ParticleCount = 0;

	bool isOn = false;
	bool isDisposable = false;
	bool isFull = false;

	std::string_view MeshName;
	std::vector<std::shared_ptr<ParticleRenderer>> ParticleList;
private:
};

