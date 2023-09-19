#include "PreCompileHeader.h"

#include "PhysXCapsuleComponent.h"
#include "Boss_OldCrow.h"

Boss_OldCrow::Boss_OldCrow() 
{

}

Boss_OldCrow::~Boss_OldCrow() 
{

}

void Boss_OldCrow::Start()
{
	EnemyBase::Start();

	std::shared_ptr<GameEngineComponent> Pivot = CreateComponent<GameEngineComponent>();
	BossRender->GetTransform()->SetParent(Pivot->GetTransform());

	Pivot->GetTransform()->AddLocalRotation({90, 0, 0});

	// physx
	{
		float4 scale = BossRender->GetMeshScale() * BossRender->GetTransform()->GetWorldScale() / BossRender->GetTransform()->GetLocalScale();
		// scale *= 2.0f;
		physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);
		m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(vscale);
	}

	SetFSMFUNC();
	SetNextState(Boss_OldCrowState::IDLE);
}

void Boss_OldCrow::Update(float _DeltaTime)
{
	FSMObjectBase::Update(_DeltaTime);
}

void Boss_OldCrow::InitPattern()
{
	std::shared_ptr<std::map<short, std::vector<short>>> PatternInit;

	//	PATTERN1, // 대쉬, 대쉬
	//	PATTERN2, // 점프
	//	PATTERN3, // 사슬, 사슬, 점프
	//	PATTERN4, // 사슬, 사슬, 연속사슬, 점프
	//	PATTERN5, // SmallCrow 소환
	//	PATTERN6, // EGG 소환 
	//	PATTERNCOUNT //패턴 총 개수

	//Pattern1
	{
		std::vector<short> Pattern1 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::STARTDASH), static_cast<short>(Boss_OldCrowState::STARTDASH) };

		PatternInit->insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN1), Pattern1));
	}
	
	//Pattern2
	{
		std::vector<short> Pattern2 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::JUMP)};

		PatternInit->insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN2), Pattern2));
	}

	//Pattern3
	{
		std::vector<short> Pattern3 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::MEGADASHPREP), static_cast<short>(Boss_OldCrowState::MEGADASHPREP),  static_cast<short>(Boss_OldCrowState::JUMP) };

		PatternInit->insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN3), Pattern3));
	}

	//Pattern4
	{
		std::vector<short> Pattern4 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::MEGADASHPREP), static_cast<short>(Boss_OldCrowState::MEGADASHPREP), static_cast<short>(Boss_OldCrowState::MEGADASH2PREP), static_cast<short>(Boss_OldCrowState::JUMP) };

		PatternInit->insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN4), Pattern4));
	}

	//Pattern5
	{
		std::vector<short> Pattern5 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::SCREAMMINI) };

		PatternInit->insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN5), Pattern5));
	}

	//Pattern6
	{
		std::vector<short> Pattern6 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::EGG) };

		PatternInit->insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN6), Pattern6));
	}
}