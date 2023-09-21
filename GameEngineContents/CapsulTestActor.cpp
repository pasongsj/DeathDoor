#include "PreCompileHeader.h"
#include "CapsulTestActor.h"

CapsulTestActor::CapsulTestActor() 
{
}

CapsulTestActor::~CapsulTestActor() 
{
}

void CapsulTestActor::Start()
{
	std::shared_ptr<GameEngineFBXRenderer> Renderer = CreateComponent<GameEngineFBXRenderer>();
	Renderer->SetFBXMesh("capsule1x1x2NEWMESH.FBX", "MeshTexture");
	Renderer->GetTransform()->SetLocalScale(float4{ 1000.0f,1000.0f,1000.0f });
	Renderer->GetAllRenderUnit()[0][0]->ShaderResHelper.SetTexture("DiffuseTex", "CenterLevelBG.png");
	//BlurUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	//Renderer->SetMaterial("CenterLevelBG.png");
}