#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineFBXMesh.h"

struct AnimStartFunc
{
	bool bStart = true;
	std::function<void()> pFunc = nullptr;
};

class FbxExAniData;
class GameEngineFBXMesh;
class GameEngineFBXAnimation;
class GameEngineFBXRenderer;
class GameEngineFBXAnimationInfo : public std::enable_shared_from_this<GameEngineFBXAnimationInfo>
{
public:
	GameEngineFBXRenderer* ParentRenderer;
	// SetFBX 본을 가지고 있는 매쉬
	std::shared_ptr<GameEngineFBXMesh> Mesh;
	// 애니메이션을 가지고 있는 FBX
	std::shared_ptr<GameEngineFBXAnimation> Aniamtion;
	FbxExAniData* FBXAnimationData;

	std::vector<float> FrameTime;
	float PlayTime = 0.0f;
	float CurFrameTime = 0.0f;
	float Inter = 0.1f;

	std::vector<unsigned int> Frames;
	UINT CurFrame = 0;
	UINT Start = -1;
	UINT End = -1;

	bool bOnceStart = true;
	bool bOnceEnd = true;
	bool Loop = true;
	bool EndValue = false;

	float BlendIn = 0.2f;
	float BlendOut = 0.2f;

	std::map<UINT, AnimStartFunc> StartFunc;

	void Init(std::shared_ptr<GameEngineFBXMesh> _Mesh, std::shared_ptr<GameEngineFBXAnimation> _Animation, const std::string_view& _Name, int _Index);
	void Reset();
	bool IsEnd();
	void Update(float _DeltaTime);

public:
	GameEngineFBXAnimationInfo()
		: Start(0)
		, End(0)
		, bOnceStart(false)
		, bOnceEnd(false)
	{
	}

	~GameEngineFBXAnimationInfo()
	{
	}
};

class AnimationCreateParams
{
public:
	float Inter = 0.0f;
	bool Loop = true;
	int Start = -1;
	int End = -1;
	std::vector<float> FrameTime = std::vector<float>();
	float BlendIn = 0.02f;
	float BlendOut = 0.02f;
};


struct AnimationBoneData
{
public:
	int Index = -1;
	float4 Scale;
	float4 RotQuaternion;
	float4 Pos;
	float4 RotEuler;
};

struct AttachTransformInfo
{
	int Index = -1;
	GameEngineTransform* Transform;
	float4 OffsetPos = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float4 OffsetRot = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4x4 OffsetMat;
};

// 설명 :
class GameEngineFBXRenderer : public GameEngineRenderer
{
	friend class GameEngineFBXAnimationInfo;

public:
	// constrcuter destructer
	GameEngineFBXRenderer();
	~GameEngineFBXRenderer();

	// delete Function
	GameEngineFBXRenderer(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer(GameEngineFBXRenderer&& _Other) noexcept = delete;
	GameEngineFBXRenderer& operator=(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer& operator=(GameEngineFBXRenderer&& _Other) noexcept = delete;

	virtual void SetFBXMesh(const std::string& _Name, std::string _Material);
	virtual void SetFBXMesh(const std::string& _Name, std::string _Material, size_t MeshIndex);
	virtual std::shared_ptr<GameEngineRenderUnit> SetFBXMesh(const std::string& _Name, std::string _Material, size_t MeshIndex, size_t _SubSetIndex);

	void SetAnimationStartFunc(const std::string_view& _Name, UINT _Index, std::function<void()> _Func);

	bool IsAnimationEnd()
	{
		if (nullptr == CurAnimation)
		{
			MsgAssert("CurAnimation이 nullptr입니다");
		}
		return CurAnimation->IsEnd();
	}

	std::map<std::pair<size_t, size_t>, std::shared_ptr<GameEngineRenderUnit>> GetUnTexturedUnit()
	{
		return UnTexturedUnit;
	}
	inline std::shared_ptr<GameEngineFBXMesh> GetFBXMesh()
	{
		return FBXMesh;
	}

	void CreateFBXAnimation(const std::string& _AnimationFBXName, const AnimationCreateParams& _Params, int _Index = 0)
	{
		CreateFBXAnimation(_AnimationFBXName, _AnimationFBXName, _Params, _Index);
	}

	void CreateFBXAnimation(const std::string& _AnimationName, const std::string& _AnimationFBXName, const AnimationCreateParams& _Params = {0.05f,true}, int _Index = 0);

	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>>& GetAllRenderUnit()
	{
		return Unit;
	}

	void Update(float _DeltaTime) override;

	void PauseSwtich();

	inline void PauseOn()
	{
		Pause = true;
	}
	inline void PauseOff()
	{
		Pause = false;
	}

	void ChangeAnimation(const std::string& _AnimationName, bool _Force = false, float _BlendTime = -1.0f);

	AnimationBoneData GetBoneData(std::string _Name);

	AnimationBoneData GetBoneData(int _Index)
	{
		return AnimationBoneDatas[_Index];
	}

	void SetAttachTransform(std::string_view _Name, GameEngineTransform* _Transform, float4 _OffsetPos = float4(0.0f, 0.0f, 0.0f, 1.0f), float4 _OffsetRot = float4(0.0f, 0.0f, 0.0f, 0.0f));

	void SetAttachTransform(int Index, GameEngineTransform* _Transform, float4 _OffsetPos = float4(0.0f, 0.0f, 0.0f, 1.0f), float4 _OffsetRot = float4(0.0f, 0.0f, 0.0f, 0.0f));

	void CalculateUnitPos();

	float4 GetMeshScale();
protected:
	// void Render(float _DeltaTime) override;

private:
	bool Pause = false;

	// 그게 불가능하다.
	// 맨처음 세팅해준 메인 매쉬와완전히 연관되어 있는 매쉬여야만 가능하다.
	float4 ResultMeshScale = float4::ZERO;
	std::shared_ptr<GameEngineFBXMesh> FBXMesh;
	std::map<std::pair<size_t, size_t>, std::shared_ptr<GameEngineRenderUnit>> UnTexturedUnit;

	// vertexbuffer1       indexbuffer          
	// 0번매쉬의            0번째 서브셋
	std::vector<         std::vector<std::shared_ptr<GameEngineRenderUnit>>> Unit;

	std::map<std::string, std::shared_ptr<GameEngineFBXAnimationInfo>> Animations;
	std::shared_ptr<GameEngineFBXAnimationInfo> CurAnimation = nullptr;

	// 처음에는 그냥 들고만 있다가
	// 애니메이션이 되는순간
	// 확장되어야 한다.
	// 본개수 만큼
	// 앞쪽에 키는 매쉬 개수 x 본개수의 뜻을 가지게 된다.

	// Structure Buffer랑 링크가 되는 녀석.
	std::vector<float4x4> AnimationBoneMatrixs;

	std::vector<float4x4> AnimationBoneMatrixsNotOffset;

	float BlendTime = 0.0f; // 0.2
	float CurBlendTime = 0.0f; // 0.2

	void UpdateBlend(float _DeltaTime);

	std::vector <AnimationBoneData> PrevAnimationBoneDatas;

	std::vector<AnimationBoneData> AnimationBoneDatas;

	std::vector<AttachTransformInfo> AttachTransformValue;
};

