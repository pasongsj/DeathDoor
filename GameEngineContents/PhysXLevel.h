#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 :
class PhysXLevel : public GameEngineLevel
{
	class CustomErrorCallback : public physx::PxErrorCallback
	{
	private:
		void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override
		{
			std::string Code = "Code : " + std::to_string(code)
				+ "\nMsg : " + message
				+ "\nFile : " + file
				+ "\nLine : " + std::to_string(line);
			MsgAssert(Code);
		}
	};

	friend class PhysXActor;
	friend class PhysXPlane;
public:
	// constrcuter destructer
	PhysXLevel();
	~PhysXLevel();

	// delete Function
	PhysXLevel(const PhysXLevel& _Other) = delete;
	PhysXLevel(PhysXLevel&& _Other) noexcept = delete;
	PhysXLevel& operator=(const PhysXLevel& _Other) = delete;
	PhysXLevel& operator=(PhysXLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
	bool advance(physx::PxReal _DeltaTime);
private:
	// Foundation을 생성하는데 필요한 변수
	physx::PxDefaultAllocator		m_Allocator;
	//physx::PxDefaultErrorCallback	m_ErrorCallback;
	CustomErrorCallback m_ErrorCallback;

	float m_fStepSize = 0.f;
	float m_fWaitTime = 0.f;

	physx::PxPhysics* m_pPhysics = nullptr;
	physx::PxScene* m_pScene = nullptr;
	physx::PxMaterial* m_pMaterial = nullptr;
	physx::PxFoundation* m_pFoundation = nullptr;
	physx::PxDefaultCpuDispatcher* m_pDispatcher = nullptr;

	physx::PxCooking* m_pCooking = nullptr;
	physx::PxPvd* m_pPvd = nullptr;

	void Initialize();

	void Simulate(float _Deltatime);

	void Release();

};

