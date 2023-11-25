#include "PreCompileHeader.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "PhysXCapsuleComponent.h"
#include "PhysXControllerComponent.h"
#include "Boss_OldCrow.h"
#include "Player.h"
#include "Boss_OldCrowChain.h"
#include "Boss_OldCrowCrowHead.h"

#include "Boss_OldCrowCrowHead.h"
#include "FeatherParticle.h"
#include "DustParticle.h"
#include "ContentLevel.h"
#include "FadeWhite.h"


Boss_OldCrow::Boss_OldCrow() 
{

}

Boss_OldCrow::~Boss_OldCrow() 
{
	MainBGM.Stop();
}

void Boss_OldCrow::Start()
{
	EnemyBase::Start();
	InitPattern();
	SetNextState(Boss_OldCrowState::INTROANIMATION);

	//InitAniamtion();

	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(float4{ 0.0f, 300.0f, 250.0f });
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
		
		if (nullptr != Player::MainPlayer)
		{
			m_pCapsuleComp->SetFilter(*Player::MainPlayer->GetPhysXComponent()->GetController());
		}

		m_pCapsuleComp->CreateSubShape(SubShapeType::BOX, float4{ 250, 200, 200 }, float4{ 0, 0, 100 });
		m_pCapsuleComp->SetSubShapeFilter(PhysXFilterGroup::MonsterSkill);
		m_pCapsuleComp->AttachShape();
	}

	if (false == GameEngineInput::IsKey("PressK"))
	{
		GameEngineInput::CreateKey("PressK", 'K');
	}
	if (false == GameEngineInput::IsKey("PressL"))
	{
		GameEngineInput::CreateKey("PressL", 'L');
	}

	float4 Scale = EnemyRenderer->GetMeshScale();

	SetEnemyHP(BOSS_OLDCROW_HP);
	IsDeath = false;

	ChainsInit();
	EnemyRenderer->SetCrackMask("OldCrowCrackMask.png");

	SetMainBGM();

	IntroDone = false;

	std::shared_ptr<FadeWhite>pWhite = GetLevel()->CreateActor<FadeWhite>();
	pWhite->FadeIn();
	pWhite->FadeUpdate();
}

void Boss_OldCrow::Update(float _DeltaTime)
{
	if (false == DeathCheck() && true == CheckHit())
	{
		GetDamaged();
		PlayRandomDamagedSound();

		if (true == TestMode)
		{
			SetEnemyHP(BOSS_OLDCROW_HP);
		}
	}

	if (true == DeathCheck() && false == IsDeath)
	{
		IsDeath = true;
		SetDeathState();
		MainBGM.SoundFadeOut(1.0f, 0.0f, true);
	}

	if (true == IntroDone)
	{
		if (false == GetLevel()->GetMainCamera()->IsFreeCamera())
		{
			float4 nextPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
			nextPos.y += 2000.0f;
			nextPos.z -= 2000.0f * tanf((90.0f - m_CameraRot.x) * GameEngineMath::DegToRad);
			GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(float4::LerpClamp(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition(), nextPos, _DeltaTime * 3.0f));
			GetLevel()->GetMainCamera()->GetTransform()->SetWorldRotation(float4::LerpClamp(GetLevel()->GetMainCamera()->GetTransform()->GetWorldRotation(), m_CameraRot, _DeltaTime * 3.0f));
		}
	}
	else
	{
		float4 CamPos = float4{ 0.0f , 250.0f, 300.0f };
		float4 CamRot = float4{ 0.0f, 0.0f, 0.0f };
		GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(CamPos);
		GetLevel()->GetMainCamera()->GetTransform()->SetWorldRotation(CamRot);
	}

	if (GameEngineInput::IsDown("PressL"))
	{
		TestMode = !TestMode;
		TestModeNumber = 0;

	}

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
	if (true == TestMode)
	{
		if (GameEngineInput::IsDown("PressK"))
		{
			switch (TestModeNumber)
			{
			case 0:
				SetNextState(Boss_OldCrowState::DASHSTART);
				break;
			case 1:
				SetNextState(Boss_OldCrowState::MEGADASHPREP);
				break;
			case 2:
				SetNextState(Boss_OldCrowState::MEGADASH2PREP);
				break;
			case 3:
				SetNextState(Boss_OldCrowState::JUMP);
				break;
			case 4:
				SetNextState(Boss_OldCrowState::SCREAMMINI);
				break;
			case 5:
				SetNextState(Boss_OldCrowState::EGG);
				break;
			default:
				break;
			}

			++TestModeNumber;

			if (TestModeNumber > 5)
			{
				TestModeNumber = 0;
			}
		}
	}
	else
	{
		int RandomPatternInt = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(Boss_OldCrowPattern::PATTERNCOUNT) - 1); //랜덤 패턴 int

		Boss_OldCrowPattern RandomPattern = Boss_OldCrowPattern(RandomPatternInt);
		Boss_OldCrowState RandomState = Boss_OldCrowState(Patterns[static_cast<short>(RandomPattern)][0]);

		PatternNum = static_cast<short>(RandomPatternInt);
		CurrentPatternNum = 0;

		//Test용 스테이트 세팅 
		//PatternNum = 5;
		//RandomState = Boss_OldCrowState(Patterns[PatternNum][0]);

		//if (4 == PatternNum && Boss_OldCrowState::INTROANIMATION == GetCurState<Boss_OldCrowState>())
		//{
		//	SetRandomPattern();
		//	return;
		//}

		SetNextState(RandomState);
	}
	
}

void Boss_OldCrow::SetNextPatternState()
{
	++CurrentPatternNum;

	//시연회용 
	if (true == TestMode)
	{
		m_pCapsuleComp->SetWorldPosWithParent(float4{ 0, 0, 1500 });
		
		//임의로 회전값 초기화
		{
			Dir = float4::BACK;

			float4 CalRot = float4::ZERO;
			CalRot.y = float4::GetAngleVectorToVectorDeg360(float4::FORWARD, Dir);

			m_pCapsuleComp->SetRotation(-CalRot);

			CurrentDir = Dir;
		}

		SetNextState(Boss_OldCrowState::IDLE);
		CurrentPatternNum = Patterns[PatternNum].size();

		return;
	}

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

	m_pCapsuleComp->SetRotation(-CalRot);
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
	CreateCrowHead();

	//플레이어 스펠 코스트 추가
	AddPlayerSpellCost();
}

void Boss_OldCrow::CreateCrowHead()
{
	std::shared_ptr<Boss_OldCrowCrowHead> CrowHead = GetLevel()->CreateActor<Boss_OldCrowCrowHead>();

	float Angle = GameEngineRandom::MainRandom.RandomFloat(0, 359);
	float4 Dir = float4::ZERO;

	Dir.y = Angle;
	Dir.x = -45.0f;

	CrowHead->SetCrowHead(GetTransform()->GetWorldPosition(), Dir, m_pCapsuleComp);
}

void Boss_OldCrow::SetDeathState()
{
	Boss_OldCrowState CurState = GetCurState<Boss_OldCrowState>();

	switch (CurState)
	{
	case Boss_OldCrowState::DASH:
	case Boss_OldCrowState::TURN:
	case Boss_OldCrowState::MEGADASH:
	case Boss_OldCrowState::MEGADASH2:
		SetNextState(Boss_OldCrowState::DEATHWHILERUNNING);
		break;
	default :
		SetNextState(Boss_OldCrowState::DEATHWHILEUPRIGHT);
		break;
	}

}

void Boss_OldCrow::CreateFeatherParticle()
{
	std::shared_ptr<FeatherParticle> New = CreateComponent<FeatherParticle>();

	float X = GameEngineRandom::MainRandom.RandomFloat(-100, 100);
	float Z = GameEngineRandom::MainRandom.RandomFloat(-100, 100);

	New->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4{ X, 100.0f, Z });
}

void Boss_OldCrow::CreateDustParticle()
{
	std::shared_ptr<DustParticle> Particle = CreateComponent<DustParticle>();
	Particle->GetTransform()->SetParent(GetLevel()->DynamicThis<ContentLevel>()->GetPivotActor()->GetTransform());
	Particle->SetFadeOut(true);
	
	float X =GameEngineRandom::MainRandom.RandomFloat(-300.0f, 300.0f);
	float Z =GameEngineRandom::MainRandom.RandomFloat(-300.0f, 300.0f);
	
	float4 CrowPos = GetTransform()->GetWorldPosition();

	while(CrowPos.XYZDistance({ X, 0.0f, Z }) <= 150.0f)
	{
		X = GameEngineRandom::MainRandom.RandomFloat(-300.0f, 300.0f);
		Z = GameEngineRandom::MainRandom.RandomFloat(-300.0f, 300.0f);
	}

	Particle->GetTransform()->SetWorldPosition(float4{ GetTransform()->GetWorldPosition().x + X, 40.0f, GetTransform()->GetWorldPosition().z + Z });
	Particle->GetTransform()->SetWorldScale({ 80.0f, 80.0f });
	Particle->GetTransform()->SetWorldRotation({ 90.0f, 0.0f });

	Particle->BillboardingOff();
	Particle->SetColor({ 0.05f, 0.05f, 0.05f, -1.0f });
	Particle->SetFadeSpeed(1.0f);
}

void Boss_OldCrow::PlayRandomTurnSound()
{
	int RandomInt = GameEngineRandom::MainRandom.RandomInt(0, 1);

	if (0 == RandomInt)
	{
		GameEngineSound::Play("OldCrow_Turn.mp3");
	}
	else
	{
		GameEngineSound::Play("OldCrow_Turn2.mp3");
	}
}

void Boss_OldCrow::PlayRandomDamagedSound()
{
	int RandomInt = GameEngineRandom::MainRandom.RandomInt(0, 1);

	if (0 == RandomInt)
	{
		GameEngineSound::Play("OldCrow_GetDamage.mp3");
	}
	else
	{
		GameEngineSound::Play("OldCrow_GetDamage2.mp3");
	}
}

void Boss_OldCrow::SetMainBGM()
{
	MainBGM = GameEngineSound::Play("Death'sDoor-OldCrow.mp3");
	MainBGM.SetLoop();
	MainBGM.SetLoopPoint(0, 93);
	MainBGM.SetPause(true);
}

void Boss_OldCrow::LevelChangeStart()
{
	GetLevel()->GetMainCamera()->GetTransform()->SetLocalRotation(m_CameraRot);
	GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPos);

	TestModeNumber = 0;
	TestMode = true;
}