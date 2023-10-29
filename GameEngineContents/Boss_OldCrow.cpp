#include "PreCompileHeader.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "PhysXCapsuleComponent.h"
#include "PhysXControllerComponent.h"
#include "Boss_OldCrow.h"
#include "Player.h"
#include "Boss_OldCrowChain.h"
#include "Boss_OldCrowCrowHead.h"

#include "Boss_OldCrowCrowHead.h"
#include "FeatherParticle.h"

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
	SetNextState(Boss_OldCrowState::IDLE);

	//InitAniamtion();

	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(float4{ 0.0f, 300.0f, 250.0f });
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
		
		m_pCapsuleComp->CreateSubShape(SubShapeType::BOX, float4{ 250, 200, 200 }, float4{ 0, 0, 100 });
		m_pCapsuleComp->SetSubShapeFilter(PhysXFilterGroup::MonsterSkill);
		m_pCapsuleComp->AttachShape();
	}

	float4 Scale = EnemyRenderer->GetMeshScale();

	SetEnemyHP(BOSS_OLDCROW_HP / 2);

	ChainsInit();
}

float Time = 0.0f;

void Boss_OldCrow::Update(float _DeltaTime)
{
	if (true == CheckCollision(PhysXFilterGroup::PlayerSkill))
	{
		GetDamaged();
	}

	FSMObjectBase::Update(_DeltaTime);

	Time += _DeltaTime;

	if (Time >= 0.05f)
	{
		if (GetTransform()->GetWorldPosition().y > 50.0f)
		{
			return;
		}

		Time = 0.0f;

		//대충 이런 식으로 만들면 됨. 
		std::shared_ptr<FeatherParticle> New = CreateComponent<FeatherParticle>();

		float X = GameEngineRandom::MainRandom.RandomFloat(-100, 100);
		float Z = GameEngineRandom::MainRandom.RandomFloat(-100, 100);
		
		New->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4{ X, 100.0f, Z});
	}
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
		std::vector<short> Pattern1 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::DASHSTART)};

		Patterns.insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN1), Pattern1));
	}
	
	//Pattern2
	{
		std::vector<short> Pattern2 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::JUMP)};

		Patterns.insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN2), Pattern2));
	}

	//Pattern3
	{
		std::vector<short> Pattern3 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::MEGADASHPREP), static_cast<short>(Boss_OldCrowState::MEGADASHPREPRANDOMPOS),  static_cast<short>(Boss_OldCrowState::JUMP) };

		Patterns.insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN3), Pattern3));
	}

	//Pattern4
	{
		std::vector<short> Pattern4 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::MEGADASHPREP), static_cast<short>(Boss_OldCrowState::MEGADASHPREPRANDOMPOS), static_cast<short>(Boss_OldCrowState::MEGADASH2PREP), static_cast<short>(Boss_OldCrowState::JUMP) };

		Patterns.insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN4), Pattern4));
	}

	//Pattern5
	{
		std::vector<short> Pattern5 = std::vector<short>{ static_cast<short>(Boss_OldCrowState::SCREAMMINI), static_cast<short>(Boss_OldCrowState::JUMP) };

		Patterns.insert(std::pair(static_cast<short>(Boss_OldCrowPattern::PATTERN5), Pattern5));
	}

	//Pattern6
	{
		std::vector<short> Pattern6 = std::vector<short>{static_cast<short>(Boss_OldCrowState::EGG), static_cast<short>(Boss_OldCrowState::JUMP) };

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
	//PatternNum = 5;
	//RandomState = Boss_OldCrowState(Patterns[PatternNum][0]);

	SetNextState(RandomState);
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

void Boss_OldCrow::SetDirection()
{
	Dir = GetPlayerDir();

	float4 CalRot = float4::ZERO;
	CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, Dir);

	m_pCapsuleComp->SetRotation(-CalRot);

	CurrentDir = Dir;
}

void Boss_OldCrow::SetMegaDashRandomPos()
{
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	PlayerPos.y = 0.0f;
	float4 RandomPos = GetRandomPos(2500.0f);
	RandomPos.y = 0.0f;
	Dir = PlayerPos - RandomPos;

	float4 CalRot = float4::ZERO;
	CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, Dir);

	CurrentDir = Dir;

	m_pCapsuleComp->SetWorldPosWithParent(RandomPos, -CalRot);
}

void Boss_OldCrow::ChainsInit()
{
	for (int i = 0; i < BOSS_OLDCROW_CHAINPIVOTCOUNT; ++i)
	{
		ChainsPivots.push_back(GetLevel()->CreateActor<GameEngineActor>());
		ChainsPivots[i]->GetTransform()->SetParent(nullptr);
	}

	Chains.reserve(BOSS_OLDCROW_CHAINCOUNT);

	for (int i = 0; i < BOSS_OLDCROW_CHAINCOUNT; ++i)
	{
		std::shared_ptr<Boss_OldCrowChain> Chain = GetLevel()->CreateActor<Boss_OldCrowChain>();

		Chains.push_back(Chain);

		Chains[i]->GetTransform()->SetParent(ChainsPivots[i]->GetTransform());
	}

	MegaDash2PatternTransformPivot = GetLevel()->CreateActor<GameEngineActor>();
	MegaDash2PatternTransformPivot->GetTransform()->SetParent(nullptr);

	for (int i = 0; i < BOSS_OLDCROW_CHAINCOUNT; ++i)
	{
		std::shared_ptr<GameEngineComponent> Transform1 = CreateComponent<GameEngineComponent>();
		Transform1->GetTransform()->SetParent(MegaDash2PatternTransformPivot->GetTransform());

		MegaDash2PatternTransforms1.push_back(Transform1);

		std::shared_ptr<GameEngineComponent> Transform2 = CreateComponent<GameEngineComponent>();
		Transform2->GetTransform()->SetParent(MegaDash2PatternTransformPivot->GetTransform());

		MegaDash2PatternTransforms2.push_back(Transform2);
	}
	
	// 0 ~ 3 Case 1, 4 ~ 7 Case 2
	{
		//회전
		float Value = 500.0f; 

		MegaDash2PatternTransforms1[0]->GetTransform()->SetLocalPosition(float4{ -Value * 6, 0, -Value });
		MegaDash2PatternTransforms1[0]->GetTransform()->SetLocalRotation(float4{ 0, 90, 0 });

		MegaDash2PatternTransforms1[1]->GetTransform()->SetLocalPosition(float4{ Value, 0, -Value * 6 });

		MegaDash2PatternTransforms1[2]->GetTransform()->SetLocalPosition(float4{ Value * 6, 0, Value });
		MegaDash2PatternTransforms1[2]->GetTransform()->SetLocalRotation(float4{ 0, -90, 0 });

		MegaDash2PatternTransforms1[3]->GetTransform()->SetLocalPosition(float4{ -Value, 0, Value * 6 });
		MegaDash2PatternTransforms1[3]->GetTransform()->SetLocalRotation(float4{ 0, 180, 0 });
	}
	{
		//일자
		float Value = 3000.0f; //X값 
		float Value2 = 700.0f; //Z간격

		MegaDash2PatternTransforms2[0]->GetTransform()->SetLocalPosition(float4{ -Value, 0, ( - Value2 / 2 ) * 3 });
		MegaDash2PatternTransforms2[0]->GetTransform()->SetLocalRotation(float4{ 0, 90, 0 });

		MegaDash2PatternTransforms2[1]->GetTransform()->SetLocalPosition(float4{ Value, 0, ( - Value2 / 2)});
		MegaDash2PatternTransforms2[1]->GetTransform()->SetLocalRotation(float4{ 0, -90, 0 });

		MegaDash2PatternTransforms2[2]->GetTransform()->SetLocalPosition(float4{ -Value, 0, Value2 / 2 });
		MegaDash2PatternTransforms2[2]->GetTransform()->SetLocalRotation(float4{ 0, 90, 0 });

		MegaDash2PatternTransforms2[3]->GetTransform()->SetLocalPosition(float4{ Value, 0, (Value2 / 2 )* 3 });
		MegaDash2PatternTransforms2[3]->GetTransform()->SetLocalRotation(float4{ 0, -90, 0 });
	}
}


float4 Boss_OldCrow::GetRandomPos(float _Value)
{
	float4 PlayerPos = Player::MainPlayer->GetPhysXComponent()->GetWorldPosition();
	PlayerPos.y = 0.0f;
	float4 RandomDir = { 0, 0, _Value };

	float Angle = GameEngineRandom::MainRandom.RandomFloat(0, 359);

	RandomDir.RotaitonYDeg(Angle);

	return PlayerPos + RandomDir;
}

void Boss_OldCrow::SettingChainPatternPivot()
{
	float Angle = GameEngineRandom::MainRandom.RandomFloat(0, 359);

	float4 Rotation = float4::ZERO;
	Rotation.y = Angle;

	MegaDash2PatternTransformPivot->GetTransform()->SetLocalRotation(Rotation);
}

void Boss_OldCrow::GetDamaged()
{
	//체력 닳는 이펙트

	//체력 닳으면 까마귀 생성
	std::shared_ptr<Boss_OldCrowCrowHead> CrowHead = GetLevel()->CreateActor<Boss_OldCrowCrowHead>();

	float Angle = GameEngineRandom::MainRandom.RandomFloat(0, 359);
	float4 Dir = float4::ZERO;

	Dir.y = Angle;
	Dir.x = -45.0f;

	CrowHead->SetCrowHead(GetTransform()->GetWorldPosition(), Dir);
}
