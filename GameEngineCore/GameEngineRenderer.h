#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"
#include "EngineContentRenderingStruct.h"
#include "GameEngineFBXMesh.h"

enum class RenderPath
{
	None,
	Forward,
	Deferred,
	Alpha,
	Custom01,
	Custom02,
	Custom03,
	Debug,
};

class GameEngineRenderUnit : public GameEngineObjectBase, public std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
	bool IsShadow = false;

	GameEngineShaderResHelper ShaderResHelper;
	std::shared_ptr<class GameEngineMaterial> Material;

	std::function<void(float)> RenderFunction;

	GameEngineRenderUnit();
	void SetMesh(const std::string_view& _Name);
	void SetMesh(std::shared_ptr<class GameEngineMesh> _Mesh);
	void SetMaterial(const std::string_view& _Name, RenderPath _Path = RenderPath::None);
	void Render(float _DeltaTime);
	void SetRenderer(class GameEngineRenderer* _Renderer);

	class GameEngineRenderer* GetRenderer()
	{
		return ParentRenderer;
	}
	std::shared_ptr<class GameEngineFBXMesh> GetFbxMesh()
	{
		std::shared_ptr<GameEngineFBXMesh> FbxMesh = std::dynamic_pointer_cast<GameEngineFBXMesh>(Mesh);
		if (nullptr != FbxMesh)
		{
			return FbxMesh;
		}
		return nullptr;
	}

	void Setting();

	void Draw();

	struct MaskInfo
	{
		float UV_MaskingValue = 1.0f;
		float MaskingColor_R = 1.0f;
		float MaskingColor_G = 0.0f;
		float MaskingColor_B = 1.0f;
	};

	struct FadeInfo
	{
		float Fade = 0.0f;
		float R = 0.0f;
		float G = 0.0f;
		float B = 0.0f;
	};

	float4 UVdata = { 1, 1, 0, 0 };

	FadeInfo Fade;
	MaskInfo Mask;

	ColorOption Color = { { 1, 1, 1, 1 }, { 0, 0, 0, 0 } };
	
	void SetUnitPos(float4 _Pos)
	{
		UnitPos = _Pos;
	}
	void SetUnitScale(float4 _Scale)
	{
		UnitScale = _Scale;
	}
	float4 GetUnitPos()
	{
		return UnitPos;
	}
	float4 GetUnitScale()
	{
		return UnitScale;
	}

private:
	float4 UnitScale = float4::ZERONULL;
	float4 UnitPos = float4::ZERONULL;
	class GameEngineRenderer* ParentRenderer = nullptr;
	std::shared_ptr<class GameEngineInputLayOut> InputLayOutPtr;
	std::shared_ptr<class GameEngineMesh> Mesh;
};


class RenderBaseValue
{
public:
	float4 BaseColor = { 1.0f, 0.0f, 0.0f, 1.0f };
	float DeltaTime = 0.0f;
	float SumDeltaTime = 0.0f;
	int IsAnimation = 0;
	int IsNormal = 0;
	float4 ScreenScale;
	float4 Mouse;
};

// ���� :
class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;
	friend class GameEngineRenderUnit;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// ������������ ���õǾ� �ְ�
	// � ���̴��� ����ߴٴ� �� �˾ƾ� �ϰ�
	// �� ���̴����� � �ؽ�ó�� ����߰�
	// � ���÷� � ������۸� ����ߴ����� �˾ƾ� �Ѵ�.

	void SetMaterial(const std::string_view& _Name, int _index = 0);
	void SetMesh(const std::string_view& _Name, int _index = 0);

	// void SetMesh(const std::string_view& _Name, int _index = 0);

	std::shared_ptr<GameEngineRenderUnit> CreateRenderUnit(std::string_view _Mesh, std::string_view _Material);
	std::shared_ptr<GameEngineRenderUnit> CreateRenderUnitToIndex(unsigned int _Index);

	// ��������Ʈ�� �����.
	std::shared_ptr<GameEngineRenderUnit> CreateRenderUnit();

	// ���⼭ ���ϵ� ������������ �����ϸ� �� ������������ ����ϴ� ��� �ֵ��� �ٲ�� �ȴ�.
	std::shared_ptr<GameEngineMaterial> GetMaterial(int _index = 0);

	// �̰� ����ϰԵǸ� �� �������� ����Ʈ�� �ڽŸ��� Ŭ�� ������������ ������ �ȴ�.
	// std::shared_ptr<GameEngineMaterial> GetPipeLineClone(int _index = 0);

	inline GameEngineShaderResHelper& GetShaderResHelper(int _index = 0)
	{
		return Units[_index]->ShaderResHelper;
	}

	void CameraCullingOn()
	{
		IsCameraCulling = true;
	}

	void CalSortZ(class GameEngineCamera* _Camera);

	GameEngineCamera* GetCamera()
	{
		return RenderCamera;
	}

	// ������Ʈ���� �Ұ��̱� ������ �׳� �ϰڽ��ϴ�. 
	// ���� ���߿� ī�޶� �ٲٰų� �Ѵٸ� �̻��� ���� �߻��Ҽ� �ִ�.

	std::shared_ptr<GameEngineRenderUnit> GetUnit(unsigned int _Index = 0)
	{
		if (_Index >= Units.size())
		{
			return nullptr;
		}

		return Units[_Index];
	}

	RenderBaseValue& GetRenderBaseValueRef()
	{
		return BaseValue;
	}


	void ShadowOn(size_t _UnitIndex = -1)
	{
		if (_UnitIndex == -1)
		{
			for (size_t i = 0; i < Units.size(); i++)
			{
				Units[i]->IsShadow = true;
			}
			return;
		}

		Units[_UnitIndex]->IsShadow = true;
	}

	void ShadowOff(size_t _UnitIndex = -1)
	{
		if (_UnitIndex == -1)
		{
			for (size_t i = 0; i < Units.size(); i++)
			{
				Units[i]->IsShadow = false;
			}
			return;
		}

		Units[_UnitIndex]->IsShadow = false;
	}

protected:
	void Start();

	void Render(float _Delta) override;

	void RenderBaseValueUpdate(float _Delta);

	void PushCameraRender(int _CameraOrder);

	RenderBaseValue BaseValue;

private:
	bool IsCameraCulling = false;

	float CalZ = 0.0f;

	GameEngineCamera* RenderCamera;

	std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;

	// Pipe��
	//// GameEngineShaderResHelper �� �������� ������ �� �Ǵ� ���� �˴ϴ�.
	//std::shared_ptr<class GameEngineMaterial> Pipe;
	//GameEngineShaderResHelper ShaderResHelper;


	void RenderTransformUpdate(GameEngineCamera* _Camera);
};

