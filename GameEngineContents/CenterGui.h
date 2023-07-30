#pragma once

// Ό³Έν :
class CenterGui
{
public:
	// constrcuter destructer
	CenterGui();
	~CenterGui();

	// delete Function
	CenterGui(const CenterGui& _Other) = delete;
	CenterGui(CenterGui&& _Other) noexcept = delete;
	CenterGui& operator=(const CenterGui& _Other) = delete;
	CenterGui& operator=(CenterGui&& _Other) noexcept = delete;

protected:

private:

};

