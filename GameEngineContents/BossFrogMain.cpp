#include "PreCompileHeader.h"
#include "BossFrogMain.h"
#include "EnemyAttackBox.h"

BossFrogMain::BossFrogMain()
{
}

BossFrogMain::~BossFrogMain()
{
}

void BossFrogMain::InitAnimation()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();
	EnemyRenderer->SetFBXMesh("FROG_MESH.FBX", "ContentAniMeshDeffered");
	// 인트로 애니메이션
	EnemyRenderer->CreateFBXAnimation("INTRO_JUMP", "FROG_JUMP.fbx", { 1.0f / 30, false }); // intro
	EnemyRenderer->SetAnimationStartFunc("INTRO_JUMP", 45, [this]
		{
			CalMoveAmount(GetTilePos(2, 1), 1.2f);
			m_pCapsuleComp->RigidSwitch(false);
			SetStateCheckerOn();
			IntroDone = true;
		});
	EnemyRenderer->SetAnimationStartFunc("INTRO_JUMP", 70, [this]
		{
			MoveSpeed = float4::ZERO;
		});
	// 아이들
	EnemyRenderer->CreateFBXAnimation("IDLE", "FROG_IDLE.fbx", { 1.0f / 30, true });
	// 물로 빠지는 애니메이션
	EnemyRenderer->CreateFBXAnimation("DAMEGED_LOOP", "FROG_DAMEGED_LOOP.fbx", { 1.0f / 30, true ,-1,-1,0.3f});
	// 점프 시작
	EnemyRenderer->CreateFBXAnimation("IDLE_TO_JUMP", "FROG_POGO_START.fbx", { 1.0f / 30, false,-1,72,0.0f,0.0f }); // 땅에서 콩콩이 시작(1회)
	EnemyRenderer->SetAnimationStartFunc("IDLE_TO_JUMP", 44, [this]
		{
			CalMoveAmount(GetNextPostition(), 1.071428f);
			m_pCapsuleComp->RigidSwitch(false);
		});// 44~74
	EnemyRenderer->SetAnimationStartFunc("IDLE_TO_JUMP", 72, [this]
		{
			MoveSpeed = float4::ZERO;
		});
	EnemyRenderer->CreateFBXAnimation("SWIM_TO_JUMP", "FROG_SMASH_START.fbx", { 1.0f / 30, false,17,49,0.0f,0.0f });// 물에서 올라옴 + 콩콩이 1회
	EnemyRenderer->SetAnimationStartFunc("SWIM_TO_JUMP", 18, [this]
		{
			float height = -180.0f - (GetTransform()->GetWorldPosition().y);
			CalMoveAmount(GetTransform()->GetWorldPosition(), 5.0f, height);
			m_pCapsuleComp->RigidSwitch(false);
		});

	EnemyRenderer->SetAnimationStartFunc("SWIM_TO_JUMP", 24, [this]
		{
			if (GetTransform()->GetWorldPosition().y < -181.0f)
			{
				float4 FrogPos = GetTransform()->GetWorldPosition();
				FrogPos.y = -180.0f;
				m_pCapsuleComp->SetWorldPosWithParent(FrogPos);
			}
			float4 nextpos = GetNextPostition();
			if (nextpos == float4::ZERONULL)
			{
				OnlySmash = true;
				SetNextState(BossFrogMainState::JUMP_END);
			}
			else
			{
				CalMoveAmount(nextpos, 1.2f);
			}
		});
	EnemyRenderer->SetAnimationStartFunc("SWIM_TO_JUMP", 49, [this]
		{
			MoveSpeed = float4::ZERO;
		});
	// 점프 반복
	EnemyRenderer->CreateFBXAnimation("JUMP_LOOP", "FROG_POGO_BOUNCE.fbx", { 1.0f / 30, true });
	EnemyRenderer->SetAnimationStartFunc("JUMP_LOOP", 2, [this]
		{
			float4 CurTileindex = GetTileIndex(GetTransform()->GetWorldPosition());
			if (true == IsTile(CurTileindex.iy(), CurTileindex.ix()))
			{
				DestroyTile(CurTileindex.iy(), CurTileindex.ix());
			}
			float4 NextPos = GetNextPostition();
			if(NextPos == float4::ZERONULL)
			{
				OnlySmash = true;
				SetNextState(BossFrogMainState::JUMP_END);
			}
			else
			{
				CalMoveAmount(NextPos, 1.5f);
			}
		});// 44~74
	EnemyRenderer->SetAnimationStartFunc("JUMP_LOOP", 22, [this]
		{
			MoveSpeed = float4::ZERO;
		});
	EnemyRenderer->SetAnimationStartFunc("JUMP_LOOP", 23, [this] {JumpCount++; });
	// 점프 끝 - 스메시
	EnemyRenderer->CreateFBXAnimation("JUMP_END", "FROG_POGO_END.fbx", { 1.0f / 30, false ,-1,-1,0.0f,0.0f}); // 점프 + 스매쉬
	EnemyRenderer->SetAnimationStartFunc("JUMP_END", 2, [this]
		{
			float4 CurTileindex = GetTileIndex(GetTransform()->GetWorldPosition());
			DestroyTile(CurTileindex.iy(), CurTileindex.ix());

			float4 NextPos = GetNextPostition();
			if(NextPos != float4::ZERONULL)
			{
				CalMoveAmount(NextPos, 0.88f);
				m_pCapsuleComp->RigidSwitch(false);
			}
		});
	EnemyRenderer->SetAnimationStartFunc("JUMP_END", 36, [this]
		{
			MoveSpeed = float4::ZERO;
			m_pCapsuleComp->RigidSwitch(true);
			SetStateCheckerOn();

			SmashAttack = GetLevel()->CreateActor<EnemyAttackBox>();
			SmashAttack->SetScale(float4{ 300.0f,100.0f,300.0f });
			float4 forward = GetTransform()->GetWorldForwardVector();
			SmashAttack->SetTrans(forward, GetTransform()->GetWorldPosition() + forward * 300.0f);

		});
	EnemyRenderer->SetAnimationStartFunc("JUMP_END", 40, [this]
		{
			AllTileReset();
			m_pCapsuleComp->TurnOnGravity();
			if (nullptr != SmashAttack)
			{
				SmashAttack->Death();
			}
			SmashAttack = nullptr;
		});
	//
	// 물 내부에서 수영
	EnemyRenderer->CreateFBXAnimation("SWIM", "FROG_SWIM.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("SWIM_EDIT", "FROG_SWIM_EDIT.fbx", { 1.0f / 30, true, -1, -1, 1.0f / 30 , 0.0f});

	EnemyRenderer->SetGlowToUnit(12, 0);
	EnemyRenderer->SetUnitColor(12, 0, { 244.0f / 255.0f, 74.0f / 255.0f, 96.0f / 255.0f , 1.0f }, 5.0f);

	EnemyRenderer->GetTransform()->SetLocalScale(float4::ONE * 50.0f);
	EnemyRenderer->GetTransform()->SetLocalRotation(float4{90.0f,0.0f,0.0f});
	EnemyRenderer->ChangeAnimation("INTRO_JUMP");
}

float4 BossFrogMain::GetNextPostition()
{
	float4 CurTileIndex = GetTileIndex(GetTransform()->GetWorldPosition());
	float4 PlayerIndex = GetTileIndex(GetPlayerPosition());
	float4 DiffTile = PlayerIndex - CurTileIndex;
	DiffTile *= 2;

	int _X = (DiffTile.ix() == 0) ? 1 : (DiffTile.ix() / abs(DiffTile.ix()));
	int _Y = (DiffTile.iy() == 0) ? 1 : (DiffTile.iy() / abs(DiffTile.iy()));


	std::vector<std::pair<float4, int>> CheckRout;

	if (abs(DiffTile.x) > abs(DiffTile.y))
	{

		CheckRout.push_back(std::make_pair(CurTileIndex + float4{ static_cast<float>(_X), 0.0f, 0.0f }, 225 + 90 * -_X));
		CheckRout.push_back(std::make_pair(CurTileIndex + float4{ 0.0f, static_cast<float>(_Y), 0.0f }, 135 + 90 * _Y));
		CheckRout.push_back(std::make_pair(CurTileIndex + float4{ static_cast<float>(-_X), 0.0f, 0.0f }, 225 + 90 * _X));
		CheckRout.push_back(std::make_pair(CurTileIndex + float4{ 0.0f, static_cast<float>(-_Y), 0.0f }, 135 + 90 * -_Y));

	}
	else
	{
		CheckRout.push_back(std::make_pair(CurTileIndex + float4{ 0.0f, static_cast<float>(_Y), 0.0f }, 135 + 90 * _Y));
		CheckRout.push_back(std::make_pair(CurTileIndex + float4{ static_cast<float>(_X), 0.0f, 0.0f }, 225 + 90 * -_X));
		CheckRout.push_back(std::make_pair(CurTileIndex + float4{ 0.0f, static_cast<float>(-_Y), 0.0f }, 135 + 90 * -_Y));
		CheckRout.push_back(std::make_pair(CurTileIndex + float4{ static_cast<float>(-_X), 0.0f, 0.0f }, 225 + 90 * _X));

	}

	float4 resultTile = CurTileIndex;

	for (const std::pair < float4, int>& checktile : CheckRout)
	{
		if (true == IsTile(checktile.first.iy(), checktile.first.ix()))
		{
			resultTile = checktile.first;
			m_pCapsuleComp->SetRotation(float4{ 0.0f, static_cast<float>(checktile.second),0.0f });
			return GetTilePos(resultTile.iy(), resultTile.ix());
		}
	}

	return float4::ZERONULL;
	
}

void BossFrogMain::Start()
{
	EnemyBase::Start();
	BossFrog::Start();
	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(float4{ 0.0f,251.0f,250.0f });//float4{ 0.0f,150.0f,90.0f }
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
		m_pCapsuleComp->SetRotation(GetTransform()->GetWorldRotation() + float4{ 0.0f, 135.0f,0.0f });
		if (nullptr != Player::MainPlayer)
		{
			m_pCapsuleComp->SetFilter(*Player::MainPlayer->GetPhysXComponent()->GetController());
		}
	}
	SetEnemyHP(3);

	if (false == GameEngineInput::IsKey("PressK"))
	{
		GameEngineInput::CreateKey("PressK", 'K');
	}
}

void BossFrogMain::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("PressK"))
	{
		SetNextState(BossFrogMainState::DAMAGED);
	}
	FSMObjectBase::Update(_DeltaTime);
}
bool BossFrogMain::CheckHit()
{
	if (true == CheckCollision(PhysXFilterGroup::PlayerSkill))// 플레이어로부터 공격을 받는다면 
	{
		float Degree = float4::GetAngleVectorToVectorRad360(GetPlayerDir(), GetTransform()->GetWorldForwardVector());
		Degree*= GameEngineMath::RadToDeg;
		if (abs(Degree) > 135.0f)
		{
			return true;
		}
	}
	return false;
}

void BossFrogMain::SetFSMFUNC()
{
	InitFSM(BossFrogMainState::MAX);

	SetChangeFSMCallBack([this]
		{
		});

	SetFSM(BossFrogMainState::IDLE,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{
			MoveUpdate();
			if (true == CheckHit())
			{
				SetNextState(BossFrogMainState::DAMAGED);
				return;
			}
			if (GetStateDuration()> IdleStateDuration)
			{
				SetNextState(BossFrogMainState::IDLE_JUMP_START);
			}
		},
		[this]
		{
		}
	);
	
	SetFSM(BossFrogMainState::INTRO,
		[this]
		{
			EnemyRenderer->ChangeAnimation("INTRO_JUMP");
		},
		[this](float Delta)
		{
			if(false == IntroDone)
			{
				std::shared_ptr<GameEngineCamera> MainCam = GetLevel()->GetMainCamera();
				float4 NextCamPos = GetTransform()->GetWorldPosition() + float4{ 2000.0f,0.0f, -2000.0f };
				//NextCamPos.z += 1000.0f;
				MainCam->GetTransform()->SetWorldPosition(float4::LerpClamp(MainCam->GetTransform()->GetWorldPosition(), NextCamPos,Delta));
				MainCam->GetTransform()->SetWorldRotation(float4::LerpClamp(MainCam->GetTransform()->GetWorldRotation(), float4{ 0.0f,-45.0f,0.0f }, Delta));

			}



			if (false == GetStateChecker() && true == CheckHit())
			{
				SetNextState(BossFrogMainState::DAMAGED);
				return;
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(BossFrogMainState::IDLE);
			}
			MoveUpdate();
		},
		[this]
		{
			
		}
	);
	
	SetFSM(BossFrogMainState::SWIM,
		[this]
		{
			EnemyRenderer->ChangeAnimation("SWIM_EDIT");
			m_pCapsuleComp->SetRotation(GetTransform()->GetWorldRotation() + float4{ 0.0f, 180.0f,0.0f });
			CalMoveAmount(UnderWaterCenter, 2.0f);
		},
		[this](float Delta)
		{
			
			MoveUpdate();
			if (false == GetStateChecker() && GetStateDuration() > 0.5f)
			{
				MoveSpeed = float4::ZERO;
			}
			if (false == GetStateChecker() && GetStateDuration() > 1.5f)
			{
				SelectedPos = GetPlayerPosition();
				SelectedPos.y = -720.0f;
				float4 Tile = GetTileIndex(SelectedPos);
				ShakeTile(Tile.iy(), Tile.ix(), 1.0f);
				SetStateCheckerOn();
			}
			if (true == GetStateChecker() && GetStateDuration() > 2.5f) // 땅이 부글부글 거리는 타이밍
			{
				SetNextState(BossFrogMainState::SWIM_JUMP_START);
			}
		},
		[this]
		{
			MoveSpeed = float4::ZERO;
		}
	);
	
	SetFSM(BossFrogMainState::DAMAGED,
		[this]
		{
			m_pCapsuleComp->TurnOnGravity();
			EnemyRenderer->ChangeAnimation("DAMEGED_LOOP");
			CalMoveAmount(GetWaterPoint(), 1.1f, -300.0f);
			switch (Phase)
			{
			case 1:
				EnemyRenderer->SetGlowToUnit(23, 0);
				EnemyRenderer->SetUnitColor(23, 0, float4::RED, 0.5f);				
				EnemyRenderer->SetGlowToUnit(24, 0);
				EnemyRenderer->SetUnitColor(24, 0, float4::RED, 0.5f);
				break;		   
			case 2:
				EnemyRenderer->SetGlowToUnit(25, 0);
				EnemyRenderer->SetUnitColor(25, 0, float4::RED, 0.5f);
				EnemyRenderer->SetGlowToUnit(26, 0);
				EnemyRenderer->SetUnitColor(26, 0, float4::RED, 0.5f);
				EnemyRenderer->SetGlowToUnit(27, 0);
				EnemyRenderer->SetUnitColor(27, 0, float4::RED, 0.5f);
				break;
			case 3:
				EnemyRenderer->SetGlowToUnit(21, 0);
				EnemyRenderer->SetUnitColor(21, 0, float4::RED, 0.5f);
				EnemyRenderer->SetGlowToUnit(22, 0);
				EnemyRenderer->SetUnitColor(22, 0, float4::RED, 0.5f);
				break;
			default:
				
				break;
			}
		},
		[this](float Delta)
		{
			MoveUpdate();
			if (false == GetStateChecker() && GetStateDuration() > 0.5f)
			{
				switch (Phase)
				{
				case 1:
					EnemyRenderer->UnitOff(23, 0);
					EnemyRenderer->UnitOff(24, 0);
					break;
				case 2:
					EnemyRenderer->UnitOff(25, 0);
					EnemyRenderer->UnitOff(26, 0);
					EnemyRenderer->UnitOff(27, 0);
					break;
				case 3:
					EnemyRenderer->UnitOff(21, 0);
					EnemyRenderer->UnitOff(22, 0);
					break;
				default:
					break;
				}
				SetStateCheckerOn();
			}
			if (GetStateDuration() > 1.0f)
			{
				if (Phase >= 3)
				{
					SetFrogDeath();
					m_pCapsuleComp->SetWorldPosWithParent(WPointNorth);
					Off();
				}
				else
				{
					SetNextState(BossFrogMainState::SWIM);
				}
			}
		},
		[this]
		{
			Phase++;
			MoveSpeed = float4::ZERO;
		}
	);
	
	SetFSM(BossFrogMainState::IDLE_JUMP_START,
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE_TO_JUMP");
			m_pCapsuleComp->TurnOffGravity();
		},
		[this](float Delta)
		{
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(BossFrogMainState::JUMP_LOOP);
			}
			MoveUpdate();
		},
		[this]
		{
		}
	);	

	SetFSM(BossFrogMainState::SWIM_JUMP_START,
		[this]
		{
			EnemyRenderer->ChangeAnimation("SWIM_TO_JUMP");
			m_pCapsuleComp->SetWorldPosWithParent(SelectedPos);
			m_pCapsuleComp->TurnOffGravity();

		},
		[this](float Delta)
		{
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(BossFrogMainState::JUMP_LOOP);
			}
			MoveUpdate();
		},
		[this]
		{
		}
	);
	
	SetFSM(BossFrogMainState::JUMP_LOOP,
		[this]
		{
			EnemyRenderer->ChangeAnimation("JUMP_LOOP");
			JumpCount = 0;
		},
		[this](float Delta)
		{
			int CurHP = GetEnemyHP();
			MoveUpdate();
			if (JumpCount >= 2 + Phase)
			{
				SetNextState(BossFrogMainState::JUMP_END);
				return;
			}
		},
		[this]
		{
		}
	);
	
	SetFSM(BossFrogMainState::JUMP_END,
		[this]
		{
			if (true == OnlySmash)
			{
				EnemyRenderer->ChangeAnimation("JUMP_END",false,3);

			}
			else
			{
				EnemyRenderer->ChangeAnimation("JUMP_END");

			}

		},
		[this](float Delta)
		{
			MoveUpdate();
			if (true == GetStateChecker() && true == CheckHit())
			{
				SetNextState(BossFrogMainState::DAMAGED);
				return;
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(BossFrogMainState::IDLE);
			}
		},
		[this]
		{
			if (nullptr != SmashAttack)
			{
				SmashAttack->Death();
			}
			SmashAttack = nullptr;
			OnlySmash = false;
		}
	);

}
void BossFrogMain::MoveUpdate()
{
	m_pCapsuleComp->SetMoveSpeed(MoveSpeed);
}
void BossFrogMain::CalMoveAmount(const float4& Dest, float MoveTime, float Yaxis)
{
	float4 MoveAmount = Dest - GetTransform()->GetWorldPosition();
	MoveAmount.y = Yaxis;
	MoveSpeed = MoveAmount * MoveTime;
}
