#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class PlayerBow : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerBow();
	~PlayerBow();

	// delete Function
	PlayerBow(const PlayerBow& _Other) = delete;
	PlayerBow(PlayerBow&& _Other) noexcept = delete;
	PlayerBow& operator=(const PlayerBow& _Other) = delete;
	PlayerBow& operator=(PlayerBow&& _Other) noexcept = delete;


	void SetTrans(const float4& _Pos, const float4& Rot = float4::ZERO);

protected:
	void Start();

private:
	std::shared_ptr<class ContentFBXRenderer> BowRenderer = nullptr;

};

