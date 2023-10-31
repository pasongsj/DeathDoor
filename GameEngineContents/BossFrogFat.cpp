#include "PreCompileHeader.h"
#include "BossFrogFat.h"

BossFrogFat::BossFrogFat()
{
}

BossFrogFat::~BossFrogFat()
{
}


const float4 FatPointNorth = float4{ -4790,-610,4800 };
const float4 FatPointSouth = float4{ -2400,-610,2450 };

void BossFrogFat::Start()
{
	EnemyBase::Start();
	BossFrog::Start();
	// physx
	{
		m_pCapsuleComp = CreateComponent<PhysXControllerComponent>();
		m_pCapsuleComp->SetPhysxMaterial(1.f, 1.f, 0.f);
		m_pCapsuleComp->CreatePhysXActors(PHYSXSCALE_MAGE * 3.0f);
		m_pCapsuleComp->TurnOffGravity();
		m_pCapsuleComp->SetRotation(GetTransform()->GetWorldRotation() + float4{ 0.0f, 135.0f,0.0f });
		m_pCapsuleComp->SetFilterData(PhysXFilterGroup::MonsterDynamic);
		if (nullptr != Player::MainPlayer)
		{
			m_pCapsuleComp->SetFilter(*Player::MainPlayer->GetPhysXComponent()->GetController());
			m_pCapsuleComp->RigidSwitch(false);
		}
		m_pCapsuleComp->SetWorldPosWithParent(BossFrog::WPointNorth);
	}

	if (false == GameEngineInput::IsKey("PressK"))
	{
		GameEngineInput::CreateKey("PressK", 'K');
	}
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


	EnemyRenderer->CreateFBXAnimation("DIE_LAND", "FROG_FAT_DIE_LAND.fbx", { 1.0f / 30, false });					//¿£µù
	EnemyRenderer->CreateFBXAnimation("DIE_STANDING", "FROG_FAT_DIE_STANDING.fbx", { 1.0f / 30, false });

	EnemyRenderer->CreateFBXAnimation("JUMP_SCREAM", "FROG_FAT_JUMP_SCREAM.fbx", { 1.0f / 30, false });				   //ÀÎÆ®·Î
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
	
	EnemyRenderer->CreateFBXAnimation("FAT_JUMP", "FROG_FAT_JUMP.fbx", { 1.0f / 30, false });						   //¹Ù´Ú to ¹° Â«Çª
	EnemyRenderer->SetAnimationStartFunc("FAT_JUMP", 36, [this]// 40~70 ÇÁ·¹ÀÓ Á¡ÇÁ // 1ÃÊ°£ Á¡ÇÁ
		{
			ResetStateDuration();
			isJumpTime = true;
		});
	EnemyRenderer->SetAnimationStartFunc("FAT_JUMP", 66, [this]
		{
			isJumpTime = false;
		});

	EnemyRenderer->CreateFBXAnimation("TILT_JUMP", "FROG_FAT_TILT_JUMP.fbx", { 1.0f / 30, false });					   //¹° to ¹Ù´Ú Àâ°í Á¡ÇÁ ²Ê´ç
	EnemyRenderer->SetAnimationStartFunc("TILT_JUMP", 14, [this]
		{
			ResetStateDuration();
			isJumpTime = true;
		});
	EnemyRenderer->SetAnimationStartFunc("TILT_JUMP", 40, [this]
		{
			isJumpTime = false;
		});
	EnemyRenderer->CreateFBXAnimation("SHOOT", "FROG_FAT_SHOOT.fbx", { 2.0f / 30, true});							   //¿ÞÂÊ¿¡¼­ 6¹ø ´øÁü
	EnemyRenderer->SetAnimationStartFunc("SHOOT", 0, [this]
		{
			++LoopCnt;
		});
	EnemyRenderer->CreateFBXAnimation("TURN", "FROG_FAT_TURN.fbx", { 1.0f / 30, false ,-1,-1,1.0f / 30,0.0f });
	
	EnemyRenderer->CreateFBXAnimation("TILT", "FROG_FAT_TILT.fbx", { 1.0f / 30, false ,17,-1,0.0f});							   //¶¥ Àâ±â
	EnemyRenderer->SetAnimationStartFunc("TILT", 35, [this]
		{
			FieldRotationStart();
		});
	EnemyRenderer->CreateFBXAnimation("TILT_GRABBED", "FROG_FAT_TILT_GRABBED.fbx", { 1.0f / 30, false ,-1,-1,0.0f});			   //´©¸£±â
	EnemyRenderer->CreateFBXAnimation("GRABBED_IDLE", "FROG_FAT_TILT_GRABBED.fbx", { 1.0f / 30, false ,1,8,0.0f});			   //´©¸£±â
	
	EnemyRenderer->CreateFBXAnimation("SUCK", "FROG_FAT_SUCK.fbx", { 1.0f / 30, true });							   //¿À¸¥ÂÊ¿¡¼­ ¹ßÆÇ 5°³ ¸ÔÀ½
	EnemyRenderer->CreateFBXAnimation("SUCK_BOMB", "FROG_FAT_SUCK_BOMB.fbx", { 1.0f / 30, false });					   //ÈíÀÔ Áß ÆøÅº ¸ÔÀ½
	EnemyRenderer->CreateFBXAnimation("SUCK_BOMB_GETUP", "FROG_FAT_SUCK_BOMB_GETUP.fbx", { 1.0f / 30, false });		   //´«¾Ë ºùºù ÈÄ ÀÏ¾î³²
	EnemyRenderer->CreateFBXAnimation("SUCK_BOMB_LOOP", "FROG_FAT_SUCK_BOMB_LOOP.fbx", { 1.0f / 30, true });		   //´«±ò ºùºù
	

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

	SetFSM(BossFrogFatState::INTRO, // ÀÎÆ®·Î 1.5f
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

	SetFSM(BossFrogFatState::IDLE, // Â«Çª ÈÄ Àá±ñ idleÅ¸ÀÓ
		[this]
		{
			EnemyRenderer->ChangeAnimation("IDLE");
		},
		[this](float Delta)
		{
			if (GetStateDuration() > 1.0f && false == isTurned)
			{
				SetNextState(BossFrogFatState::TURN);
			}
		},
		[this]
		{
		}
	);
	SetFSM(BossFrogFatState::GRABBED_IDLE, // Â«Çª ÈÄ Àá±ñ idleÅ¸ÀÓ
		[this]
		{
			EnemyRenderer->ChangeAnimation("GRABBED_IDLE", true, -1, 0.0f);
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
		}
	);

	SetFSM(BossFrogFatState::JUMP_TO_WATER,// ¶¥->¹°
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
		}
	);
	
	SetFSM(BossFrogFatState::JUMP_TO_GROUND,// ¹°->¶¥
		[this]
		{
			EnemyRenderer->ChangeAnimation("TILT_JUMP");
			JumpStartPoint = GetTransform()->GetWorldPosition();
			JumpEndPoint = GetPlayerPosition();
			CalJumpPoint();
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

	SetFSM(BossFrogFatState::TURN,//¹° Â«Çª ÈÄ ÅÏ
		[this]
		{
			EnemyRenderer->ChangeAnimation("TURN");
			isTurned = true;
		},
		[this](float Delta)
		{
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


	SetFSM(BossFrogFatState::TILT, // tilt¿Í suck
		[this]
		{
			EnemyRenderer->ChangeAnimation("TILT", false, -1, 1.0f / 30);

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
		}
	);
	SetFSM(BossFrogFatState::SUCK, // tilt¿Í suck 3ÃÊ¿¡ ¼¼¿ì°í 4ÃÊ¿¡
		[this]
		{
			EnemyRenderer->ChangeAnimation("SUCK");
		},
		[this](float Delta)
		{
			if (true == GameEngineInput::IsDown("PressK")) // ÀÓ½Ã(ÆøÅº¿¡ ¸Â¾Ò´Ù¸é)
			{
				FieldRotationEnd();
				SetNextState(BossFrogFatState::SUCK_BOMB);
			}
			if (false == GetStateChecker() && GetStateDuration() > 3.0f)
			{
				FieldRotationEnd();
				SetStateCheckerOn();
			}
			else if (true == GetStateChecker() && GetStateDuration() > 4.0f)
			{
				SetNextState(BossFrogFatState::JUMP_TO_GROUND);
				return;
			}
		},
		[this]
		{
		}
	);

	SetFSM(BossFrogFatState::SHOOT, // ÆøÅº ´øÁö±â
		[this]
		{
			LoopCnt = 0;
			EnemyRenderer->ChangeAnimation("SHOOT", false, -1, 3.0f / 30);
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
		}
	);

	SetFSM(BossFrogFatState::SUCK_BOMB, // ÆÐÅÏ ÆÄÈÑ ½Ã
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
	SetFSM(BossFrogFatState::SUCK_BOMB_END, // ÆÐÅÏ ÆÄÈÑ ½Ã
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

