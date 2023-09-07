#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 설명 : 벽배치용 액터
class Transform_Wall : public GameEngineActor
{
public:
	// constrcuter destructer
	Transform_Wall();
	~Transform_Wall();

	// delete Function
	Transform_Wall(const Transform_Wall& _Other) = delete;
	Transform_Wall(Transform_Wall&& _Other) noexcept = delete;
	Transform_Wall& operator=(const Transform_Wall& _Other) = delete;
	Transform_Wall& operator=(Transform_Wall&& _Other) noexcept = delete;

	inline std::shared_ptr<class PhysXBoxComponent> GetPhysXComponent() const
	{
		return m_pComp;
	}

	// 변동없을 경우 xyz축 중에서 배율에 변경이 없을 경우 1 입력 
	void Set_MeshRatio(float4& _Ratio);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitComponent();

	std::shared_ptr<class GameEngineFBXRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class PhysXBoxComponent > m_pComp = nullptr;
};
