#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineMaterial.h>
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineFBXMesh.h>
#include <GameEngineCore/GameEngineFBXAnimation.h>

void ContentsCore::ContentsResourcesCreate()
{
	// 텍스처 로드만 각 레벨별로 하고 정리하는 습관을 들이세요.
	

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("ContentsShader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineShader::AutoCompile(Files[i]);
		}
	}


	{
		D3D11_SAMPLER_DESC SamperData = {};
		SamperData.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		// 텍스처가 멀리있을때 뭉갤꺼냐
		// 안뭉갠다.
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::ReSetting("ENGINEBASE", SamperData);
	}

	{
		D3D11_SAMPLER_DESC SamperData = {};
		SamperData.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		// 텍스처가 멀리있을때 뭉갤꺼냐
		// 안뭉갠다.
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("WRAP", SamperData);
	}


	//알파블렌드
	{
		D3D11_BLEND_DESC Desc = { 0, };

		Desc.AlphaToCoverageEnable = false;
		Desc.IndependentBlendEnable = false;

		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		GameEngineBlend::Create("WaterBlend", Desc);
	}

	//{
	//	std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("My2DTexture");

	//	//Pipe->SetVertexBuffer("Rect");
	//	//Pipe->SetIndexBuffer("Rect");
	//	Pipe->SetVertexShader("MyShader.fx");
	//	Pipe->SetRasterizer("Engine2DBase");
	//	Pipe->SetPixelShader("MyShader.fx");
	//	Pipe->SetBlendState("AlphaBlend");
	//	Pipe->SetDepthState("EngineDepth");
	//}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("Fade");

		//Pipe->SetVertexBuffer("FullRect");
		//Pipe->SetIndexBuffer("FullRect");
		Pipe->SetVertexShader("FadeShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("FadeShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ContentMeshForward");

		Pipe->SetVertexShader("ContentMeshForward.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentMeshForward.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ContentMeshDeffered");

		Pipe->SetVertexShader("ContentMeshDeffered.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentMeshDeffered.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ContentAniMeshForward");

		Pipe->SetVertexShader("ContentAnitMeshForward.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentAnitMeshForward.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ContentAniMeshDeffered");

		Pipe->SetVertexShader("ContentAniMeshDeffered.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentAniMeshDeffered.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("Content2DTexture");

		Pipe->SetVertexShader("ContentTextureShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentTextureShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("HorizonBlur");

		Pipe->SetVertexShader("HorizonBlur.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("HorizonBlur.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("VerticalBlur");

		Pipe->SetVertexShader("VerticalBlur.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("VerticalBlur.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("AllBlur7x7");

		Pipe->SetVertexShader("AllBlur7x7.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("AllBlur7x7.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ResultRender");

		Pipe->SetVertexShader("ResultRender.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ResultRender.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("DetectMask");

		Pipe->SetVertexShader("DetectMask.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("DetectMask.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("LightMerge");

		Pipe->SetVertexShader("LightMerge.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("LightMerge.hlsl");
		Pipe->SetBlendState("MergeBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("DefferedColorMerge");

		Pipe->SetVertexShader("DefferedColorMerge.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("DefferedColorMerge.hlsl");
		Pipe->SetBlendState("MergeBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("AlphaColorMerge");

		Pipe->SetVertexShader("AlphaColorMerge.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("AlphaColorMerge.hlsl");
		Pipe->SetBlendState("MergeBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("GrayScale");

		Pipe->SetVertexShader("GrayScale.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("GrayScale.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("Fire");

		Pipe->SetVertexShader("FireShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("FireShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("SwordTrailShader");

		Pipe->SetVertexShader("SwordTrailShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("SwordTrailShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("FXAA");
		Pipe->SetVertexShader("FXAA.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("FXAA.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("AlwayDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("DetectLum");
		Pipe->SetVertexShader("DetectLuminance.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("DetectLuminance.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("AlwayDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("GammaCorrection");
		Pipe->SetVertexShader("GammaCorrection.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("GammaCorrection.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("AlwayDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("Dust");
		Pipe->SetVertexShader("DustShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("DustShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ReflectMesh");
		Pipe->SetVertexShader("ReflectMesh.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ReflectMesh.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ReflectAniMesh");
		Pipe->SetVertexShader("ReflectAniMesh.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ReflectAniMesh.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("Water");
		Pipe->SetVertexShader("WaterShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("WaterShader.hlsl");
		Pipe->SetBlendState("WaterBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ParticleBasic");
		Pipe->SetVertexShader("ParticleBasicShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ParticleBasicShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}
	
	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("DustParticle");
		Pipe->SetVertexShader("DustParticle.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("DustParticle.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("HitCircle");
		Pipe->SetVertexShader("HitCircle.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("HitCircle.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("Particle3D");
		Pipe->SetVertexShader("Particle3D.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("Particle3D.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ShockCircle");
		Pipe->SetVertexShader("ShockCircle.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ShockCircle.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ContentMeshAlpha");
		Pipe->SetVertexShader("ContentMeshAlpha.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentMeshAlpha.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}
	//{
	//	// 블랜드
	//	D3D11_BLEND_DESC Desc = { 0, };
	//	Desc.AlphaToCoverageEnable = false;
	//	Desc.IndependentBlendEnable = false;

	//	Desc.RenderTarget[0].BlendEnable = true;
	//	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	//	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	//	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	//	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	//	GameEngineBlend::Create("OldFilm", Desc);
	//}

	//{
	//	std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("OldFilm");

	//	//Pipe->SetVertexBuffer("FullRect");
	//	//Pipe->SetIndexBuffer("FullRect");
	//	Pipe->SetVertexShader("OldFilmShader.hlsl");
	//	Pipe->SetRasterizer("Engine2DBase");
	//	Pipe->SetPixelShader("OldFilmShader.hlsl");
	//	Pipe->SetBlendState("OldFilm");
	//	Pipe->SetDepthState("EngineDepth");
	//}


	//{
	//	std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("OldTV");

	//	Pipe->SetVertexShader("OldTVShader.hlsl");
	//	Pipe->SetRasterizer("Engine2DBase");
	//	Pipe->SetPixelShader("OldTVShader.hlsl");
	//	Pipe->SetBlendState("OldFilm");
	//	Pipe->SetDepthState("EngineDepth");
	//}


	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("DebugRect");

		Pipe->SetVertexShader("DebugMeshRender.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("DebugMeshRender.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}



	//{
	//	std::shared_ptr<GameEngineTexture> Res = GameEngineTexture::Find("EngineBaseTex.png");
	//	for (size_t y = 0; y < 10; y++)
	//	{
	//		for (size_t x = 0; x < 10; x++)
	//		{
	//			Res->SetPixel(x, y, {0, 0, 0, 0});
	//		}
	//	}
	//}


	//{
	//	std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("DebugSphere");
	//	Pipe->SetVertexBuffer("Sphere");
	//	Pipe->SetIndexBuffer("Sphere");
	//	Pipe->SetVertexShader("CollisionDebugShader.hlsl");
	//	Pipe->SetRasterizer("Engine2DBase");
	//	Pipe->SetPixelShader("CollisionDebugShader.hlsl");
	//	Pipe->SetBlendState("AlphaBlend");
	//	Pipe->SetDepthState("EngineDepth");
	//}

	//FBX STATIC MESH LOAD
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Mesh\\Static");
		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".FBX" });
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFBXMesh::Load(Files[i].GetFullPath());
		}
	}

	// FBX ANIMATOR MESH LOAD
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Mesh\\Animator");
		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".FBX" });
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFBXMesh::Load(Files[i].GetFullPath());
		}
	}


	// FBX ANIMATION MESH LOAD
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Mesh\\Animation");
		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".FBX" });
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFBXAnimation::Load(Files[i].GetFullPath());
		}
	}



	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("ContentResources");
	//	NewDir.Move("ContentResources");
	//	NewDir.Move("Mesh");
	//	NewDir.Move("AniMesh");

	//	std::vector<GameEngineFile> PlayerFiles = NewDir.GetAllFile({ ".FBX" });

	//	for (size_t i = 0; i < PlayerFiles.size(); i++)
	//	{
	//		GameEngineFBXMesh::Load(PlayerFiles[i].GetFullPath());
	//		GameEngineFBXAnimation::Load(PlayerFiles[i].GetFullPath());
	//	}
	//}

	{
		GameEngineFont::Load("맑은 고딕");
	}

	ContentsCore::CreateCylinderMesh();

	//여기까지

	// 
	// 
	// 
	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("ContentResources");
	//	NewDir.Move("ContentResources");
	//	NewDir.Move("Texture");
	//	NewDir.Move("Test");

	//	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

	//	for (size_t i = 0; i < File.size(); i++)
	//	{
	//		GameEngineTexture::Load(File[i].GetFullPath());
	//	}
	//}

}

void ContentsCore::CreateCylinderMesh()
{
	std::vector<GameEngineVertex> Vertices;
	std::vector<UINT> Indices;

	float Radius = 1.0f;    // 원기둥의 반지름
	float Height = 2.0f * GameEngineMath::PIE;  // 원기둥의 높이 (원기둥 옆면을 펼쳤을 때, 정사각형이 되는 비율이 가장 좋다 생각해서 2PIE로 설정)
	int NumSegments = 32;   // 원기둥의 세그먼트 수

	for (int i = 0; i <= NumSegments; ++i)
	{
		float CurTheta = 2.0f * GameEngineMath::PIE * float(i) / float(NumSegments);
		float CurX = Radius * cosf(CurTheta);
		float CurZ = Radius * sinf(CurTheta);

		// 상단 원기둥 버텍스
		Vertices.push_back({ { CurX, Height * 0.5f, CurZ }, { i / float(NumSegments), 0.0f } });
	}

	// 하단 원기둥 버텍스
	for (int i = 0; i <= NumSegments; ++i)
	{
		float CurTheta = 2.0f * GameEngineMath::PIE * float(i) / float(NumSegments);
		float CurX = Radius * cosf(CurTheta);
		float CurZ = Radius * sinf(CurTheta);

		// 하단 원기둥 버텍스
		Vertices.push_back({ { CurX, -Height * 0.5f, CurZ }, { i / float(NumSegments), 1.0f } });
	}

	for (int i = 0; i < NumSegments; i++)
	{
		Indices.push_back(i);
		Indices.push_back(i + 1);
		Indices.push_back(i + NumSegments + 1);
	}

	for (int i = 0; i < NumSegments; i++)
	{
		Indices.push_back(i + 1);
		Indices.push_back(i + NumSegments + 2);
		Indices.push_back(i + NumSegments + 1);
	}

	GameEngineVertexBuffer::Create("Cylinder", Vertices);
	GameEngineIndexBuffer::Create("Cylinder", Indices);
	GameEngineMesh::Create("Cylinder");
}