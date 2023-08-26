#pragma once
#include "PlayerBase.h"

class Player_Banana : public PlayerBase
{

public:

	Player_Banana();
	~Player_Banana();

	Player_Banana(const Player_Banana& _Other) = delete;
	Player_Banana(Player_Banana&& _Other) noexcept = delete;
	Player_Banana& operator=(const Player_Banana& _Other) = delete;
	Player_Banana& operator=(Player_Banana&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
private:

};

