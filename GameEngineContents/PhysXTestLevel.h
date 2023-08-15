#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 :
class PhysXTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PhysXTestLevel();
	~PhysXTestLevel();

	// delete Function
	PhysXTestLevel(const PhysXTestLevel& _Other) = delete;
	PhysXTestLevel(PhysXTestLevel&& _Other) noexcept = delete;
	PhysXTestLevel& operator=(const PhysXTestLevel& _Other) = delete;
	PhysXTestLevel& operator=(PhysXTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	// Foundation을 생성하는데 필요한 변수
	physx::PxDefaultAllocator		m_Allocator;
	physx::PxDefaultErrorCallback	m_ErrorCallback;

	physx::PxFoundation* m_pFoundation = nullptr;

	physx::PxPhysics* m_pPhysics = nullptr;

	physx::PxDefaultCpuDispatcher* m_pDispatcher = nullptr;
	physx::PxScene* m_pScene = nullptr;
	physx::PxMaterial* m_pMaterial = nullptr;

	physx::PxPvd* m_pPvd = nullptr;
	// 클래스 초기화
	void Initialize();

	void Simulate(bool _Value = true);

	void Release();
};

