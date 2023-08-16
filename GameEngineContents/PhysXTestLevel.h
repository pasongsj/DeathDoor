#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 :
class PhysXTestLevel : public GameEngineLevel
{
	class CustomErrorCallback : public physx::PxErrorCallback
	{
	private:
		void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override
		{
			MsgAssert(message);
		}
	};

	friend class PhysXTestActor;
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

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
	
private:
	// Foundation을 생성하는데 필요한 변수
	physx::PxDefaultAllocator		m_Allocator;
	//physx::PxDefaultErrorCallback	m_ErrorCallback;
	CustomErrorCallback m_ErrorCallback;


	physx::PxPhysics* m_pPhysics = nullptr;
	physx::PxScene* m_pScene = nullptr;
	physx::PxMaterial* m_pMaterial = nullptr;
	physx::PxFoundation* m_pFoundation = nullptr;
	physx::PxDefaultCpuDispatcher* m_pDispatcher = nullptr;

	//physx::PxPvd* m_pPvd = nullptr;

	void Initialize();

	void Simulate(bool _Value = true);

	void Release();

};

