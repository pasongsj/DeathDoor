#include "PrecompileHeader.h"
#include "Boomerang.h"

Boomerang::Boomerang()
{
}

Boomerang::~Boomerang()
{
}


void Boomerang::Start()
{
}

void Boomerang::Update(float _DeltaTime)
{
	if (nullptr == AttackRenderer)
	{
		return;
	}
}

void Boomerang::SetBoomer(BoomerType Type, const float4& Position, const float4& Rotation)
{
	if (nullptr == AttackRenderer)
	{
		AttackRenderer = CreateComponent<ContentFBXRenderer>();
		AttackRenderer->SetFBXMesh("Boomerang.fbx", "ContentMeshDeffered");
		switch (Type)
		{
		case Boomerang::BoomerType::HEAD:
			//AttackRenderer->SetFBXMesh("handBoomer_HEAD.fbx", "ContentMeshDeffered");
			AttackRenderer->GetTransform()->SetLocalRotation(float4{-90.0f,-0.0f,90.0f});
		
			break;
		case Boomerang::BoomerType::LEFT:
			//AttackRenderer->SetFBXMesh("handBoomer_LEFT.fbx", "ContentMeshDeffered");
		
			break;
		case Boomerang::BoomerType::RIGHT:
			//AttackRenderer->SetFBXMesh("handBoomer_RIGHT.fbx", "ContentMeshDeffered");
			break;
		case Boomerang::BoomerType::MAX:
			break;
		default:
			break;
		}

		AttackRenderer->GetTransform()->SetWorldScale(float4::ONE * 70.0f);

	}
	AttackRenderer->GetTransform()->SetLocalPosition(Position);
	AttackRenderer->GetTransform()->SetWorldRotation(Rotation);
}
