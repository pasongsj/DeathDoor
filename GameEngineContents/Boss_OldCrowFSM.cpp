#include "PreCompileHeader.h"

#include "Boss_OldCrow.h"

void Boss_OldCrow::SetFSMFUNC()
{
	SetFSM(Boss_OldCrowState::IDLE,
		[this]
		{
			BossRender->ChangeAnimation("DASH");
		},
		[this](float Delta)
		{

		},
		[this]
		{
		}
	);

}
