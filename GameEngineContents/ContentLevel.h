#pragma once
#include "PhysXLevel.h"

class ContentLevel : public PhysXLevel
{

public:

	ContentLevel();
	~ContentLevel();

	ContentLevel(const ContentLevel& _Other) = delete;
	ContentLevel(ContentLevel&& _Other) noexcept = delete;
	ContentLevel& operator=(const ContentLevel& _Other) = delete;
	ContentLevel& operator=(ContentLevel&& _Other) noexcept = delete;

protected:
	void CreateUI();
	void SetPostPrecessEffect();
private:

};

