#include "PreCompileHeader.h"
#include "BossFrogMain.h"


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
			SetStateCheckerOn();
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
		});// 44~74
	EnemyRenderer->SetAnimationStartFunc("IDLE_TO_JUMP", 72, [this]
		{
			MoveSpeed = float4::ZERO;
		});
	EnemyRenderer->CreateFBXAnimation("SWIM_TO_JUMP", "FROG_SMASH_START.fbx", { 1.0f / 30, false,-1,49,0.0f,0.0f });// 물에서 올라옴 + 콩콩이 1회
	EnemyRenderer->SetAnimationStartFunc("SWIM_TO_JUMP", 18, [this]
		{
			float height = -180.0f - GetTransform()->GetWorldPosition().y;
			CalMoveAmount(GetTransform()->GetWorldPosition(), 5.0f, height);
			float4 CurTile = GetTileIndex(GetTransform()->GetWorldPosition());
			DestroyTile(CurTile.iy(), CurTile.ix());
		});

	EnemyRenderer->SetAnimationStartFunc("SWIM_TO_JUMP", 24, [this]
		{
			CalMoveAmount(GetNextPostition(), 1.2f);
		});
	EnemyRenderer->SetAnimationStartFunc("SWIM_TO_JUMP", 49, [this]
		{
			MoveSpeed = float4::ZERO;
		});
	// 점프 반복
	EnemyRenderer->CreateFBXAnimation("JUMP_LOOP", "FROG_POGO_BOUNCE.fbx", { 1.0f / 30, true });
	EnemyRenderer->SetAnimationStartFunc("JUMP_LOOP", 2, [this]
		{
			DestroyTile(NextDestroyTile.first, NextDestroyTile.second);
			NextDestroyTile.first = -1, NextDestroyTile.second = -1;
			CalMoveAmount(GetNextPostition(), 1.5f);
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
			DestroyTile(NextDestroyTile.first, NextDestroyTile.second);
			NextDestroyTile.first = -1, NextDestroyTile.second = -1;
			CalMoveAmount(GetNextPostition(), 0.88f);
		});
	EnemyRenderer->SetAnimationStartFunc("JUMP_END", 36, [this]
		{
			MoveSpeed = float4::ZERO;
			m_pCapsuleComp->TurnOnGravity();
			SetStateCheckerOn();
		});
	EnemyRenderer->SetAnimationStartFunc("JUMP_END", 40, [this]
		{
			AllTileReset();

		});
	// 물 내부에서 수영
	EnemyRenderer->CreateFBXAnimation("SWIM", "FROG_SWIM.fbx", { 1.0f / 30, false });
	EnemyRenderer->CreateFBXAnimation("SWIM_EDIT", "FROG_SWIM_EDIT.fbx", { 1.0f / 30, false });

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

	std::vector<float4> CheckRout;
	if (abs(DiffTile.x) > abs(DiffTile.y))
	{
		CheckRout.push_back(CurTileIndex + float4{ DiffTile.x / abs(DiffTile.x), 0.0f, 0.0f });
		CheckRout.push_back(CurTileIndex + float4{ 0.0f, DiffTile.y / abs(DiffTile.y), 0.0f });
		CheckRout.push_back(CurTileIndex + float4{ -DiffTile.x / abs(DiffTile.x), 0.0f, 0.0f });
		CheckRout.push_back(CurTileIndex + float4{ 0.0f, -DiffTile.y / abs(DiffTile.y), 0.0f });

	}
	else
	{
		CheckRout.push_back(CurTileIndex + float4{ 0.0f, DiffTile.y / abs(DiffTile.y), 0.0f });
		CheckRout.push_back(CurTileIndex + float4{ DiffTile.x / abs(DiffTile.x), 0.0f, 0.0f });
		CheckRout.push_back(CurTileIndex + float4{ 0.0f, -DiffTile.y / abs(DiffTile.y), 0.0f });
		CheckRout.push_back(CurTileIndex + float4{ -DiffTile.x / abs(DiffTile.x), 0.0f, 0.0f });
	}

	float4 resultTile = CurTileIndex;

	for (const float4& checktile : CheckRout)
	{
		if (true == IsTile(checktile.iy(), checktile.ix()))
		{
			resultTile = checktile;
			NextDestroyTile = std::make_pair(resultTile.iy(), resultTile.ix());
			break;
		}
	}

	return GetTilePos(resultTile.iy(), resultTile.ix());
}

void BossFrogMain::Start()
{
	EnemyBase::Start();
	BossFrog::Start();
	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(float4{ 0.0f,150.0f,90.0f });//float4{ 0.0f,150.0f,90.0f }
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
		m_pCapsuleComp->SetRotation(GetTransform()->GetWorldRotation() + float4{ 0.0f, 135.0f,0.0f });
		m_pCapsuleComp->SetSlope(30.f);
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
			CalMoveAmount(GetPlayerPosition(), 0.5f);
		},
		[this](float Delta)
		{
			MoveUpdate();
			if (GetStateDuration() > 2.0f)
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
			CalMoveAmount(GetWaterPoint(), 1.0f, -100.0f);
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
					EnemyRenderer->SetRenderUnitControl(23, 0, false);
					EnemyRenderer->SetRenderUnitControl(24, 0, false);
					break;
				case 2:
					EnemyRenderer->SetRenderUnitControl(25, 0, false);
					EnemyRenderer->SetRenderUnitControl(26, 0, false);
					EnemyRenderer->SetRenderUnitControl(27, 0, false);
					break;
				case 3:
					EnemyRenderer->SetRenderUnitControl(21, 0, false);
					EnemyRenderer->SetRenderUnitControl(22, 0, false);
					break;
				default:
					break;
				}
				SetStateCheckerOff();
			}
			if (GetStateDuration() > 1.0f)
			{
				SetNextState(BossFrogMainState::SWIM);
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
			EnemyRenderer->ChangeAnimation("JUMP_END");
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
