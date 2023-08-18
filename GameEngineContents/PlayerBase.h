#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string_view>
#include <list>
#include <optional>

class PlayerBase : public GameEngineActor
{
public:
	
	enum class MoveTypes
	{
		Idle,
		Move,
		Throw, //부메랑 던지기
		Cut,   //근접공격
		Die
	};

public:

	PlayerBase();
	~PlayerBase();

	PlayerBase(const PlayerBase& _Other) = delete;
	PlayerBase(PlayerBase&& _Other) noexcept = delete;
	PlayerBase& operator=(const PlayerBase& _Other) = delete;
	PlayerBase& operator=(PlayerBase&& _Other) noexcept = delete;

protected:

	void SetMyType(const std::string_view& _Name)
	{
		Type = GameEngineString::ToUpper(_Name);

		SetMesh();
		SetCollision();
	}

protected:
	void PlayerUpdate(float _Delta);
	void StatusUpdate();

	void CreateKey();
private:

	void SetMesh();
	void SetCollision();
	
	int GetKeyInput();

	void IdleStart();
	void MoveStart();
	void ThrowStart();
	void CutStart();
	void DieStart();

	bool IdleUpdate(float _Delta);
	bool MoveUpdate(float _Delta);
	bool ThrowUpdate(float _Delta);
	bool CutUpdate(float _Delta);
	bool DieUpdate(float _Delta);


	template<typename EnumType>
	std::optional<std::function<bool(float)>> isPlayerUpdate(EnumType _MoveTypes);

	std::map<int, std::function<bool(float)>> UpdateList;

	int Status = 0;

	std::string Type = "";

	std::shared_ptr<class GameEngineFBXRenderer> PlayerMesh = nullptr;
	std::shared_ptr<class GameEngineCollision> PlayerCollision = nullptr;

};

