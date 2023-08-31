#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineBase/GameEngineDirectory.h>
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

		//GameEngineVertexShader::Load(Files[0].GetFullPath(), "MyShader_VS");
		//GameEnginePixelShader::Load(Files[0].GetFullPath(), "MyShader_PS");
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
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ContentMesh");

		//Pipe->SetVertexBuffer("FullRect");
		//Pipe->SetIndexBuffer("FullRect");
		Pipe->SetVertexShader("ContentMeshShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentMeshShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ContentAniMesh");

		//Pipe->SetVertexBuffer("FullRect");
		//Pipe->SetIndexBuffer("FullRect");
		Pipe->SetVertexShader("ContentMeshAniShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentMeshAniShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("ContentMeshToon");

		//Pipe->SetVertexBuffer("FullRect");
		//Pipe->SetIndexBuffer("FullRect");
		Pipe->SetVertexShader("ContentMeshToonShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentMeshToonShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Pipe = GameEngineMaterial::Create("Content2DTexture");

		//Pipe->SetVertexBuffer("FullRect");
		//Pipe->SetIndexBuffer("FullRect");
		Pipe->SetVertexShader("ContentTextureShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentTextureShader.hlsl");
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
		//Pipe->SetVertexBuffer("Rect");
		//Pipe->SetIndexBuffer("Rect");
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

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Mesh");
		NewDir.Move("Characters");


		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".FBX" });
		
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFBXMesh::Load(Files[i].GetFullPath());
		}
		
		NewDir.MoveParent();
		NewDir.Move("Map");
		
		std::vector<GameEngineFile> MapFiles = NewDir.GetAllFile({ ".FBX" });
		
		for (size_t i = 0; i < MapFiles.size(); i++)
		{
			GameEngineFBXMesh::Load(MapFiles[i].GetFullPath());
		}

		NewDir.MoveParent();
		NewDir.Move("Animations");
		
		std::vector<GameEngineFile> PlayerFiles = NewDir.GetAllFile({ ".FBX" });
		
		for (size_t i = 0; i < PlayerFiles.size(); i++)
		{
			GameEngineFBXAnimation::Load(PlayerFiles[i].GetFullPath());
		}
	}

	{
		GameEngineFont::Load("맑은 고딕");
	}

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
