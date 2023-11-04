#include "PreCompileHeader.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "BossFrogFat.h"
#include "BossFrogBomb.h"
#include "PhysXBoxComponent.h"

BossFrogFat::BossFrogFat()
{
}

BossFrogFat::~BossFrogFat()
{
}




void BossFrogFat::Start()
{
	EnemyBase::Start();
	BossFrog::Start();
	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(float4{0.0f,1000.0f,400.0f});
		m_pCapsuleComp->TurnOffGravity();
		m_pCapsuleComp->SetRotation(GetTransform()->GetWorldRotation() + float4{ 0.0f, 135.0f,0.0f });
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
		if (nullptr != Player::MainPlayer)
		{
			m_pCapsuleComp->SetFilter(*Player::MainPlayer->GetPhysXComponent()->GetController());
			m_pCapsuleComp->RigidSwitch(false);
		}
		m_pCapsuleComp->SetWorldPosWithParent(BossFrog::WPointNorth);
		m_pCapsuleComp->CreateSubShape(SubShapeType::BOX, float4{ 800.0f,200.0f,200.0f }, float4{ 0.0f, 100.0f, 400.0f });
	}

	if (false == GameEngineInput::IsKey("PressK"))
	{
		GameEngineInput::CreateKey("PressK", 'K');
	}
}
float4 BossFrogFat::GetRandomTileIndex()
{
	int cnt = 0;
	while (true)
	{
		if (cnt > 50)
		{
			return float4::ZERONULL;
		}
		int y = GameEngineRandom::MainRandom.RandomInt(0, 4);
		int x = GameEngineRandom::MainRandom.RandomInt(0, 4);
		if (true == IsTile(y, x))
		{
			return float4{ static_cast<float>(x),static_cast<float>(y) };
		}
		cnt++;
	}
}

float4 BossFrogFat::GetRandomTilePos()
{
	float4 index = GetRandomTileIndex();
	if (index == float4::ZERONULL)
	{
		return index;
	}
	return GetTilePos(index.iy(), index.ix());
}


void BossFrogFat::Update(float _DeltaTime)
{
	AnimationBoneData BoneData = EnemyRenderer->GetBoneData("_FROG_SEPTRE_BONE");
	WeaponRenderer->GetTransform()->SetLocalPosition(WeaponPivotPos + BoneData.Pos);
	WeaponRenderer->GetTransform()->SetLocalRotation(WeaponPivotRot + BoneData.RotEuler);

	
	FSMObjectBase::Update(_DeltaTime);
}

void BossFrogFat::InitAnimation()
{
	EnemyRenderer = CreateComponent<ContentFBXRenderer>();
	EnemyRenderer->SetFBXMesh("FROG_FAT_MESH.FBX", "ContentAniMeshDeffered");


	EnemyRenderer->CreateFBXAnimation("DIE_LAND", "FROG_FAT_DIE_LAND.fbx", { 1.0f / 30, false });					//����
	EnemyRenderer->CreateFBXAnimation("DIE_STANDING", "FROG_FAT_DIE_STANDING.fbx", { 1.0f / 30, false });

	EnemyRenderer->CreateFBXAnimation("JUMP_SCREAM", "FROG_FAT_JUMP_SCREAM.fbx", { 1.0f / 30, false });				   //��Ʈ��
	EnemyRenderer->SetAnimationStartFunc("JUMP_SCREAM", 47, [this]
		{
			JumpStartPoint = OnGroundCenter;
			JumpEndPoint = FatPointSouth;
			CalJumpPoint();
			ResetStateDuration();
			isJumpTime = true;
		});
	EnemyRenderer->SetAnimationStartFunc("JUMP_SCREAM", 77, [this]
		{
			isJumpTime = false;
		});
	EnemyRenderer->CreateFBXAnimation("IDLE", "FROG_FAT_IDLE.fbx", { 1.0f / 30, true });
	
	EnemyRenderer->CreateFBXAnimation("FAT_JUMP", "FROG_FAT_JUMP.fbx", { 1.0f / 30, false });						   //�ٴ� to �� «Ǫ
	EnemyRenderer->SetAnimationStartFunc("FAT_JUMP", 36, [this]// 40~70 ������ ���� // 1�ʰ� ����
		{
			ResetStateDuration();
			isJumpTime = true;
		});
	EnemyRenderer->SetAnimationStartFunc("FAT_JUMP", 66, [this]
		{
			isJumpTime = false;
		});

	EnemyRenderer->CreateFBXAnimation("TILT_JUMP", "FROG_FAT_TILT_JUMP.fbx", { 1.0f / 30, false });					   //�� to �ٴ� ��� ���� �ʴ�
	EnemyRenderer->SetAnimationStartFunc("TILT_JUMP", 14, [this]
		{
			ResetStateDuration();
			isJumpTime = true;
		});
	EnemyRenderer->SetAnimationStartFunc("TILT_JUMP", 40, [this]
		{
			isJumpTime = false;
		});
	EnemyRenderer->CreateFBXAnimation("SHOOT", "FROG_FAT_SHOOT.fbx", { 2.0f / 30, true});							   //���ʿ��� 6�� ����
	EnemyRenderer->SetAnimationStartFunc("SHOOT", 0, [this]
		{
			++LoopCnt;
		});
	EnemyRenderer->SetAnimationStartFunc("SHOOT", 8 , [this]
		{
			std::shared_ptr< BossFrogBomb> Bomb = GetLevel()->CreateActor< BossFrogBomb>();
			float4 StartP = GetTransform()->GetWorldPosition();
			StartP.y = 100.0f;
			float4 Destindex = GetRandomTileIndex();
			Bomb->SetTargetTile(StartP, Destindex);
		});
	EnemyRenderer->CreateFBXAnimation("TURN", "FROG_FAT_TURN.fbx", { 1.0f / 30, false ,-1,-1,1.0f / 30,0.0f });
	EnemyRenderer->SetAnimationStartFunc("TURN", 56, [this] 
		{
			SetStateCheckerOn();
		});
	EnemyRenderer->CreateFBXAnimation("TILT", "FROG_FAT_TILT.fbx", { 1.0f / 30, false ,17,-1,0.0f});							   //�� ���
	EnemyRenderer->SetAnimationStartFunc("TILT", 35, [this]
		{
			FieldRotationStart();
		});
	EnemyRenderer->CreateFBXAnimation("TILT_GRABBED", "FROG_FAT_TILT_GRABBED.fbx", { 1.0f / 30, false ,-1,-1,0.0f});			   //������
	EnemyRenderer->CreateFBXAnimation("GRABBED_IDLE", "FROG_FAT_TILT_GRABBED.fbx", { 1.0f / 30, false ,1,8,0.0f});			   //������
	
	EnemyRenderer->CreateFBXAnimation("SUCK", "FROG_FAT_SUCK.fbx", { 1.0f / 30, false });							   //�����ʿ��� ���� 5�� ����

	EnemyRenderer->SetAnimationStartFunc("SUCK", 40, [this]
		{
			SuckTile();
		});
	EnemyRenderer->SetAnimationStartFunc("SUCK", 55, [this]
		{
			SuckTile();
		});
	EnemyRenderer->SetAnimationStartFunc("SUCK", 65, [this]
		{
			SuckTile();
		});

	EnemyRenderer->SetAnimationStartFunc("SUCK", 75, [this]
		{
			SuckTile();
		});

	EnemyRenderer->SetAnimationStartFunc("SUCK", 85, [this]
		{
			SuckTile();
		});


	EnemyRenderer->CreateFBXAnimation("SUCK_BOMB", "FROG_FAT_SUCK_BOMB.fbx", { 1.0f / 30, false });					   //���� �� ��ź ����
	EnemyRenderer->CreateFBXAnimation("SUCK_BOMB_GETUP", "FROG_FAT_SUCK_BOMB_GETUP.fbx", { 1.0f / 30, false });		   //���� ���� �� �Ͼ
	EnemyRenderer->CreateFBXAnimation("SUCK_BOMB_LOOP", "FROG_FAT_SUCK_BOMB_LOOP.fbx", { 1.0f / 30, true });		   //���� ����
	

	JumpStartPoint = FatPointNorth;
	JumpEndPoint = OnGroundCenter;
	CalJumpPoint();


	EnemyRenderer->ChangeAnimation("FAT_JUMP");
	EnemyRenderer->GetTransform()->SetLocalScale(float4::ONE * 130.0f);

	WeaponRenderer = CreateComponent<ContentFBXRenderer>();
	WeaponRenderer->SetFBXMesh("FROG_WEAPONMESH.FBX", "ContentMeshDeffered");
	WeaponRenderer->GetTransform()->SetParent(EnemyRenderer->GetTransform());
	WeaponRenderer->GetTransform()->SetLocalScale(float4::ONE * 1.4f);
	WeaponRenderer->SetGlowToUnit(1, 0);
	WeaponRenderer->SetUnitColor(1, 0, { 244.0f / 255.0f, 74.0f / 255.0f, 96.0f / 255.0f , 1.0f }, 5.0f);

}
void BossFrogFat::SuckTile()
{
	float4 index = GetRandomTileIndex();
	if (index == float4::ZERONULL)
	{
		return;
	}
	ShakeTile(index.iy(), index.ix(), 1.0f);
}

void BossFrogFat::CalJumpPoint()
{
	JumpP3 = JumpEndPoint;
	JumpP3.y += 450;
	JumpP2 = JumpStartPoint * 0.1f + JumpEndPoint * 0.9f;
	JumpP2.y = JumpP3.y;
}


void BossFrogFat::SetFSMFUNC()
{
	InitFSM(BossFrogFatState::MAX);

	SetChangeFSMCallBack([this]
		{
		});

	SetFSM(BossFrogFatState::INTRO, // ��Ʈ�� 1.5f
		[this]
		{
		},
		[this](float Delta)
		{
			if (true == isJumpTime)
			{
				m_pCapsuleComp->SetWorldPosWithParent(float4::Bazier4LerpClamp(JumpStartPoint, JumpP2, JumpP3, JumpEndPoint, GetStateDuration()));
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				if (false == GetStateChecker())
				{
					EnemyRenderer->ChangeAnimation("JUMP_SCREAM");
					SetStateCheckerOn();
				}
				else
				{
					SetNextState(BossFrogFatState::IDLE);
				}
			}

		},
		[this]
		{
		}
	);

	SetFSM(BossFrogFatState::IDLE, // «Ǫ �� ��� idleŸ��
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{
			if (false == isTurned && true == CheckHit())
			{
				AllTileReset();
			}
			if (GetStateDuration() > 1.0f && false == isTurned)
			{
				SetNextState(BossFrogFatState::TURN);
			}
		},
		[this]
		{
		}
	);
	SetFSM(BossFrogFatState::GRABBED_IDLE, // «Ǫ �� ��� idleŸ��
		[this]
		{
			EnemyRenderer->ChangeAnimation("GRABBED_IDLE", true, -1, 0.0f);
			m_pCapsuleComp->AttachShape();
		},
		[this](float Delta)
		{
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				if (0 < LoopCnt)
				{
					SetNextState(BossFrogFatState::JUMP_TO_GROUND);
					LoopCnt = 0;
				}
				else
				{
					if (true == isRightPattern)
					{
						SetNextState(BossFrogFatState::TILT);
					}
					else
					{
						SetNextState(BossFrogFatState::SHOOT);
					}

				}
			}
		},
		[this]
		{
			m_pCapsuleComp->DetachShape();
		}
	);

	SetFSM(BossFrogFatState::JUMP_TO_WATER,// ��->��
		[this]
		{
			EnemyRenderer->ChangeAnimation("FAT_JUMP");
			JumpStartPoint = OnGroundCenter;
			if (isRightPattern)
			{
				JumpEndPoint = FatPointSouth;
			}
			else
			{
				JumpEndPoint = FatPointNorth;
			}
			CalJumpPoint();
		},
		[this](float Delta)
		{
			if (true == isJumpTime)
			{
				m_pCapsuleComp->SetWorldPosWithParent(float4::Bazier4LerpClamp(JumpStartPoint, JumpP2, JumpP3, JumpEndPoint, GetStateDuration()));
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(BossFrogFatState::IDLE);
			}
		},
		[this]
		{
			isTurned = false;
			m_pCapsuleComp->RigidSwitch(true);
		}
	);
	
	SetFSM(BossFrogFatState::JUMP_TO_GROUND,// ��->��
		[this]
		{
			EnemyRenderer->ChangeAnimation("TILT_JUMP");
			JumpStartPoint = GetTransform()->GetWorldPosition();
			JumpEndPoint = GetPlayerPosition();
			CalJumpPoint();
			m_pCapsuleComp->RigidSwitch(false);
		},
		[this](float Delta)
		{
			if (true == isJumpTime)
			{
				m_pCapsuleComp->SetWorldPosWithParent(float4::Bazier4LerpClamp(JumpStartPoint, JumpP2, JumpP3, JumpEndPoint, GetStateDuration()* 1.153846f));
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(BossFrogFatState::JUMP_TO_WATER);
			}
		},
		[this]
		{
			isRightPattern = !isRightPattern;
		}
	);

	SetFSM(BossFrogFatState::TURN,//�� «Ǫ �� ��
		[this]
		{
			EnemyRenderer->ChangeAnimation("TURN");
			isTurned = true;
		},
		[this](float Delta)
		{
			if (false == GetStateChecker() && true == CheckHit())
			{
				AllTileReset();
			}
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(BossFrogFatState::GRABBED_IDLE);
			}
		},
		[this]
		{
			m_pCapsuleComp->SetRotation(GetTransform()->GetLocalRotation() + float4{0.0f,180.0f,0.0f});

		}
	);


	SetFSM(BossFrogFatState::TILT, // tilt�� suck
		[this]
		{
			EnemyRenderer->ChangeAnimation("TILT", false, -1, 1.0f / 30);
			m_pCapsuleComp->AttachShape();
		},
		[this](float Delta)
		{
			if (GetStateDuration() > 1.0f)
			{
				SetNextState(BossFrogFatState::SUCK);
			}
		},
		[this]
		{
			m_pCapsuleComp->DetachShape();

		}
	);
	SetFSM(BossFrogFatState::SUCK, // tilt�� suck 3�ʿ� ����� 4�ʿ�
		[this]
		{
			LoopCnt = 0;
			EnemyRenderer->ChangeAnimation("SUCK");

		},
		[this](float Delta)
		{
			if (true == CheckHit()) // �ӽ�(��ź�� �¾Ҵٸ�)
			{
				FieldRotationEnd();
				SetNextState(BossFrogFatState::SUCK_BOMB);
			}
			if (false == GetStateChecker() && GetStateDuration() > 3.0f)
			{
				FieldRotationEnd();
				SetStateCheckerOn();
			}
			else if (true == EnemyRenderer->IsAnimationEnd()/*true == GetStateChecker() && GetStateDuration() > 4.0f*/)
			{
				SetNextState(BossFrogFatState::JUMP_TO_GROUND);
				return;
			}
		},
		[this]
		{
		}
	);

	SetFSM(BossFrogFatState::SHOOT, // ��ź ������
		[this]
		{
			LoopCnt = 0;
			EnemyRenderer->ChangeAnimation("SHOOT", false, -1, 3.0f / 30);
			m_pCapsuleComp->AttachShape();

		},
		[this](float Delta)
		{
			if (LoopCnt >=6)
			{
				SetNextState(BossFrogFatState::GRABBED_IDLE);
			}
		},
		[this]
		{
			m_pCapsuleComp->DetachShape();
		}
	);

	SetFSM(BossFrogFatState::SUCK_BOMB, // ���� ���� ��
		[this]
		{
			EnemyRenderer->ChangeAnimation("SUCK_BOMB");
			
		},
		[this](float Delta)
		{
			if (true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(BossFrogFatState::SUCK_BOMB_END);
				return;
			}
		},
		[this]
		{
		}
	);
	SetFSM(BossFrogFatState::SUCK_BOMB_END, // ���� ���� ��
		[this]
		{
			EnemyRenderer->ChangeAnimation("SUCK_BOMB_LOOP");
		},
		[this](float Delta)
		{
			if (false == GetStateChecker() && GetStateDuration() > 2.0f)
			{
				EnemyRenderer->ChangeAnimation("SUCK_BOMB_GETUP");
				SetStateCheckerOn();
			}
			else if (true == GetStateChecker() && true == EnemyRenderer->IsAnimationEnd())
			{
				SetNextState(BossFrogFatState::JUMP_TO_GROUND);
			}
		},
		[this]
		{
		}
	);

}
