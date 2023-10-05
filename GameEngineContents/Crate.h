#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class CrateType
{
	NORMAL,
	SMALL,
};



// 액터 생성시 enum type 지정

// 설명 :
class Crate : public GameEngineActor
{
public:
	// constrcuter destructer
	Crate();
	~Crate();

	// delete Function
	Crate(const Crate& _Other) = delete;
	Crate(Crate&& _Other) noexcept = delete;
	Crate& operator=(const Crate& _Other) = delete;
	Crate& operator=(Crate&& _Other) noexcept = delete;

	inline std::shared_ptr<class PhysXBoxComponent> GetPhysXComponent() const
	{
		return m_pPhysXComponent;
	}

	inline void SetType(CrateType _Type)
	{
		m_eType = _Type;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent> m_pPhysXComponent = nullptr;

	CrateType m_eType = CrateType::NORMAL;
};
