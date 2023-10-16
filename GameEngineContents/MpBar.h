#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MpBar : public GameEngineActor
{

public:

	MpBar();
	~MpBar();

	MpBar(const MpBar& _Other) = delete;
	MpBar(MpBar&& _Other) noexcept = delete;
	MpBar& operator=(const MpBar& _Other) = delete;
	MpBar& operator=(MpBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTtime) override;
	void Render(float _DeltaTtime) override;
private:

	void MpUpdate();
	
	int MaxMp = 4;
	int PrevMP = 4;
	int CurMp = 4;

	std::shared_ptr<class ContentUIRenderer> MpBarRender = nullptr;
	std::vector<std::shared_ptr<ContentUIRenderer>> MpBlocks;
};

