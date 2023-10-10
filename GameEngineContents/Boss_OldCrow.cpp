#include "PreCompileHeader.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "PhysXCapsuleComponent.h"
#include "Boss_OldCrow.h"
#include "Player.h"
#include "Boss_OldCrowChain.h"

Boss_OldCrow::Boss_OldCrow() 
{

}

Boss_OldCrow::~Boss_OldCrow() 
{

}

void Boss_OldCrow::Start()
{
	EnemyBase::Start();
	InitPattern();

	// physx
	{
		float4 scale = BossRender->GetMeshScale() * BossRender->GetTransform()->GetWorldScale() / BossRender->GetTransform()->GetLocalScale();
		// scale *= 2.0f;
		physx::PxVec3 vscale = physx::PxVec3(scale.x, scale.y, scale.z);
		m_pCapsuleComp = CreateComponent<PhysXCapsuleComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(vscale);
	}

	ChainsInit();

	SetFSMFUNC();

	SetNextState(Boss_OldCrowState::IDLE);
}

void Boss_OldCrow::Update(float _DeltaTime)
{
	FSMObjectBase::Update(_DeltaTime);
}

void Boss_OldCrow::InitPattern()
{
	//	PATTERN1, // 대쉬, 대쉬
	//	PATTERN2, // 점프
	//	PATTERN3, // 사슬, 사슬, 점프
	//	PATTERN4, // 사슬, 사슬, 연속사슬, 점프
	//	PATTERN5, // SmallCrow 소환
	//	PATTERN6, // EGG 소환 
	//	PATTERNCOUNT //패턴 총 개수

	//Pattern1
	{
		std::vector<short> Pattern1 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::DASHSTART), static_cast<short>(Boss_OldCrowState::DASHSTART) };

		Patterns.insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN1), Pattern1));
	}
	
	//Pattern2
	{
		std::vector<short> Pattern2 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::JUMP)};

		Patterns.insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN2), Pattern2));
	}

	//Pattern3
	{
		std::vector<short> Pattern3 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::MEGADASHPREP), static_cast<short>(Boss_OldCrowState::MEGADASHPREP),  static_cast<short>(Boss_OldCrowState::JUMP) };

		Patterns.insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN3), Pattern3));
	}

	//Pattern4
	{
		std::vector<short> Pattern4 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::MEGADASHPREP), static_cast<short>(Boss_OldCrowState::MEGADASHPREP), static_cast<short>(Boss_OldCrowState::MEGADASH2PREP), static_cast<short>(Boss_OldCrowState::JUMP) };

		Patterns.insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN4), Pattern4));
	}

	//Pattern5
	{
		std::vector<short> Pattern5 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::SCREAMMINI) };

		Patterns.insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN5), Pattern5));
	}

	//Pattern6
	{
		std::vector<short> Pattern6 = std::vector<short>{static_cast<short>(Boss_OldCrowState::EGG) };

		Patterns.insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN6), Pattern6));
	}

}

void Boss_OldCrow::SetRandomPattern()
{
	int RandomPatternInt = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(Boss_OldCrowPattern::PATTERNCOUNT) - 1); //랜덤 패턴 int

	Boss_OldCrowPattern RandomPattern = Boss_OldCrowPattern(RandomPatternInt);
	Boss_OldCrowState RandomState = Boss_OldCrowState(Patterns[static_cast<short>(RandomPattern)][0]);

	PatternNum = static_cast<short>(RandomPatternInt);
	CurrentPatternNum = 0;

	//Test용 스테이트 세팅 
	PatternNum = 2;
	RandomState = Boss_OldCrowState(Patterns[2][0]);

	SetNextState(RandomState);

	/*switch (RandomPattern)
	{
	case Boss_OldCrow::Boss_OldCrowPattern::PATTERN1:
		break;
	case Boss_OldCrow::Boss_OldCrowPattern::PATTERN2:
		break;
	case Boss_OldCrow::Boss_OldCrowPattern::PATTERN3:
		break;
	case Boss_OldCrow::Boss_OldCrowPattern::PATTERN4:
		break;
	case Boss_OldCrow::Boss_OldCrowPattern::PATTERN5:
		break;
	case Boss_OldCrow::Boss_OldCrowPattern::PATTERN6:
		break;
	default:
		MsgAssert("불가능한 보스 패턴입니다.");
		break;
	}*/
}

void Boss_OldCrow::SetNextPatternState()
{
	++CurrentPatternNum;

	if (CurrentPatternNum >= Patterns[PatternNum].size())
	{
		SetRandomPattern();
	}
	else
	{
		SetNextState(Boss_OldCrowState(Patterns[PatternNum][CurrentPatternNum]));
	}
}

void Boss_OldCrow::TurnCheck()
{
	float4 PlayerPos = Player::MainPlayer->GetPhysXComponent()->GetWorldPosition();
	PlayerPos.y = 0;

	float4 BossPos = m_pCapsuleComp->GetWorldPosition();
	BossPos.y = 0;

	float Distance = BossPos.XYZDistance(PlayerPos);
	float Angle = float4::GetAngleVectorToVectorDeg360(GetPlayerDir(), CurrentDir);

	if (Distance >= 300.0f && abs(float4::GetAngleVectorToVectorDeg360(GetPlayerDir(), CurrentDir)) > 60.0f) //거리가 a보다 멀고, 회전해야되는 크기가 b 이상이면
	{
		SetNextState(Boss_OldCrowState::TURN);
	}
}

void Boss_OldCrow::SetLerpDirection(float _DeltaTime)
{
	Dir = GetPlayerDir();

	if (CurrentDir == Dir)
	{
		return;
	}

	float4 LerpDir = float4::LerpClamp(CurrentDir, Dir, _DeltaTime);
	float4 CalRot = float4::ZERO;
	CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, LerpDir);

	m_pCapsuleComp->SetRotation( -CalRot);
	CurrentDir = LerpDir;
}

void Boss_OldCrow::ChainsInit()
{
	ChainsPivot = CreateComponent<GameEngineComponent>();
	ChainsPivot->GetTransform()->SetParent(m_pCapsuleComp->GetTransform());
	ChainsPivot->GetTransform()->AddLocalPosition({ 0, 100, 0 });

	Chains.reserve(200);

	for (int i = 0; i < ChainsCount; ++i)
	{
		std::shared_ptr<Boss_OldCrowChain> Chain = GetLevel()->CreateActor<Boss_OldCrowChain>();
		Chain->Setting(i);

		Chains.push_back(Chain);
	}

	for (int i = 0; i < 4; ++i)
	{
		std::vector<int> vector;

		UsingChainNumber.push_back(vector);
	}

	ChainSize = Chains[0]->GetRendererScale();
}

std::shared_ptr<Boss_OldCrowChain> Boss_OldCrow::GetChain()
{
	for (int i = 0; i < Chains.size(); ++i)
	{
		if (false == Chains[i]->GetChainState())
		{
			Chains[i]->OnRenderer();

			return Chains[i];
		}
	}

	std::shared_ptr<Boss_OldCrowChain> Chain = GetLevel()->CreateActor<Boss_OldCrowChain>();
	Chain->Setting(Chains.size());
	Chain->OnRenderer();

	Chains.push_back(Chain);

	return Chain;
}
