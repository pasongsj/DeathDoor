#include "PrecompileHeader.h"
#include "Dust.h"
#include "DustRenderer.h"

Dust::Dust()
{
}

Dust::~Dust()
{
}

void Dust::Start()
{
	float4 UVDir1 = { -1.0f, 1.0f };
	UVDir1 = UVDir1.NormalizeReturn();

	float4 UVDir2 = { -1.0f, -1.0f};
	UVDir2 = UVDir2.NormalizeReturn();

	float4 UVDir3 = { 1.0f, 1.0f };
	UVDir3 = UVDir3.NormalizeReturn();

	float4 UVDir4 = { 1.0f, -1.0f };
	UVDir4 = UVDir4.NormalizeReturn();

	Dust1 = CreateComponent<DustRenderer>();
	Dust1->GetTransform()->SetWorldScale({ 1600, 900 });
	Dust1->SetUVScale(1600, 900);
	Dust1->SetMoveDir(UVDir1.x, UVDir1.y);

	Dust2 = CreateComponent<DustRenderer>();
	Dust2->GetTransform()->SetWorldScale({ 1600, 900 });
	Dust2->SetUVScale(800, 450);
	Dust2->SetMoveDir(UVDir2.x, UVDir2.y);
	
	Dust3 = CreateComponent<DustRenderer>();
	Dust3->GetTransform()->SetWorldScale({ 1600, 900 });
	Dust3->SetUVScale(400, 225);
	Dust3->SetMoveDir(UVDir3.x, UVDir3.y);

	Dust4 = CreateComponent<DustRenderer>();
	Dust4->GetTransform()->SetWorldScale({ 1600, 900 });
	Dust4->SetUVScale(160, 90);
	Dust4->SetMoveDir(UVDir3.x, UVDir3.y);
}

void Dust::Update(float _Delta)
{

	Dust1->DustMove(_Delta, 0.04f);
	Dust2->DustMove(_Delta, 0.03f);
	Dust3->DustMove(_Delta, 0.02f);
}
