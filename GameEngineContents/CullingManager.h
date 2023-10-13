#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 설명 :
class CullingManager : public GameEngineActor
{
public:
	// constrcuter destructer
	CullingManager();
	~CullingManager();

	// delete Function
	CullingManager(const CullingManager& _Other) = delete;
	CullingManager(CullingManager&& _Other) noexcept = delete;
	CullingManager& operator=(const CullingManager& _Other) = delete;
	CullingManager& operator=(CullingManager&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Culling();

	void LinkTrigger();
	void On_FirstTrigger();

	void CheckLink();
	std::vector<std::shared_ptr<class CullingTrigger>> m_vCullingTriggers = std::vector<std::shared_ptr<class CullingTrigger>>();
	std::vector<std::shared_ptr<class CullingObject>> m_vCullingObjects = std::vector<std::shared_ptr<class CullingObject>>();
};

// 규칙
// 1. 첫번째트리거의 컬링오브젝트는 시작부터 On 처리 해준다. 



// 컬링을 진행할 레벨은 
// 1. 스타트에서 CullingManager 를 생성 ( 각레벨은 CullingManager를.. 들고있는다? statc? ) 
// 2. 컬링을 적용할 렌더러 혹은,액터를 컬링 매니저에 세팅
// 3. 컬링 매니저가 nullptr이 아니라면. 레벨의 Update 에서 컬링매니저의 업데이트 함수 호출
// 4. 컬링매니저의 업데이트 함수에서는 컬링관련 함수 호출

// 맞나? 아니면. 컬링매니저는 static, 레벨 생성시 항상 만들고. 현재 레벨이 어떤 레벨이냐에 따라서 다르게 동작 