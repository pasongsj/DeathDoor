#include "PreCompileHeader.h"
#include "PlayerAttackBomb.h"

#include "ContentFBXRenderer.h"
#include "PhysXSphereComponent.h"

#include "GrayScaleEffect.h"
#include "DustParticle.h"

PlayerAttackBomb::PlayerAttackBomb()
{
}

PlayerAttackBomb::~PlayerAttackBomb()
{
}

void PlayerAttackBomb::Start()
{
	// Render
	AttackRenderer = CreateComponent< ContentFBXRenderer>();
	AttackRenderer->SetFBXMesh("SphereDefault.fbx", "NoLight");
	AttackRenderer->GetTransform()->SetLocalScale(PLAYER_ATT_BOMB_RENDER_SCALE);
	// PhysX
	CreatePhysXAttComp<PhysXSphereComponent>(PLAYER_ATT_BOMB_PHYSX_SCALE, PhysXFilterGroup::PlayerBomb);
	SetDestTarget(PhysXFilterGroup::MonsterDynamic);

	AttackRenderer->SetColor(float4{ 1.0f, 0.1f, 0.2f }, 5.0f);
	PhysXComp->SetDynamicPivot(float4::DOWN * 100.0f);
	PhysXComp->CreateSubShape(SubShapeType::SPHERE, float4::ONE * 500.0f);
}
//void PlayerAttackBomb::Death()
//{
//	
//
//	//GameEngineObjectBase::Death();
//}
void PlayerAttackBomb::Bomb()
{

	GameEngineSound::Play("Player_BombExplosion.mp3");
	SetShoot(0);
	AttackRenderer->Off();

	BombTime = GetLiveTime() + 1.0f;
	PhysXComp->AttachShape();

	std::weak_ptr<GrayScaleEffect> Effect = GetLevel()->GetLastTarget()->CreateEffect<GrayScaleEffect>();
	GameEngineLevel* Level = GetLevel();
	Level->TimeEvent.AddEvent(0.2f, [Level, Effect](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {Level->GetLastTarget()->ReleaseEffect(Effect.lock()); });
	
	//isCollisionBomb = true;
	return;
}


void PlayerAttackBomb::Update(float _DeltaTime)
{
	if (false == IsShoot() || nullptr == PhysXComp || nullptr == PhysXComp->GetDynamic())
	{
		return;
	}
	if(true == AttackRenderer->IsUpdate())
	{
		if (true == CheckCollision(PhysXFilterGroup::Obstacle) || (PhysXFilterGroup::None != DestTarget && true == CheckCollision(DestTarget)))
		{
			Bomb();
			return;
		}
	}
	else 
	{
		if (GetLiveTime() > BombTime)
		{
			Death();
			GameEngineSound::Play("Splash.mp3");
			return;
		}
	}

	//if (false == isCollisionBomb && PhysXFilterGroup::None != DestTarget && 
	//	(true == CheckCollision(DestTarget) || true == CheckCollision(PhysXFilterGroup::Obstacle)))
	//{
	//	if (true == AttackRenderer->IsUpdate())
	//	{
	//		GameEngineSound::Play("Player_BombExplosion.mp3");
	//	}
	//	SetShoot(0);
	//	AttackRenderer->Off();
	//	BombTime = GetLiveTime() + 1.0f;
	//	PhysXComp->AttachShape();
	//	std::weak_ptr<GrayScaleEffect> Effect = GetLevel()->GetLastTarget()->CreateEffect<GrayScaleEffect>();
	//	GameEngineLevel* Level = GetLevel();
	//	Level->TimeEvent.AddEvent(0.2f, [Level, Effect](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {Level->GetLastTarget()->ReleaseEffect(Effect.lock()); });
	//	isCollisionBomb = true;
	//	return;
	//}
	//if (BombTime != 0.0f && GetLiveTime() > BombTime)
	//{
	//	Death();
	//	GameEngineSound::Play("Splash.mp3");
	//	return;
	//}
	if (GetLiveTime() > GetFireTime() + 5.0f)
	{
		Death();
		return;
	}
	
	PhysXComp->GetDynamic()->setLinearVelocity({ 0,0,0 });
	PhysXComp->SetMoveSpeed(GetDir() * GetShootSpeed());
	isPhysXCollision = 0;

	if(true == AttackRenderer->IsUpdate())
	{
		CreateParticle(_DeltaTime);
	}
}


void PlayerAttackBomb::CreateParticle(float _DeltaTime)
{
	ParticleCount += _DeltaTime;

	if (ParticleCount >= 0.01f)
	{
		ParticleCount = 0.0f;

		std::shared_ptr<DustParticle> NewParticle = CreateComponent<DustParticle>();
		NewParticle->SetColor(float4{ 1.0f, 0.1f, 0.2f } * 5.0f);
		NewParticle->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
		NewParticle->GetTransform()->SetLocalScale({ 50.0f, 50.0f, 50.0f });
		NewParticle->SetWorldMove();
		NewParticle->SetFadeOut(true);
	}
}