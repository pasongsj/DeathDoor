#include "PrecompileHeader.h"
#include "CullingManager.h"

#include "FortressLevel.h"
#include "OfficeLevel.h"

#include "Map_Fortress.h"

CullingManager::CullingManager()
{
}

CullingManager::~CullingManager()
{
}

// 인자로 ~~ 를 받고 
void CullingManager::SetCullingObject()
{
	
}

// 스타트에서 현재 레벨에 따라서 컬링에 필요한 오브젝트를 받아와서 저장, 세팅한다... 
// 어떻게 세팅할건지 
void CullingManager::Start()
{
	ContentLevel* CurContentLevel = dynamic_cast<ContentLevel*>(GetLevel());
	if (nullptr == CurContentLevel)
	{
		MsgAssert("레벨의 다이나믹 캐스트에 실패했습니다. ㄷㄷ");
		return;
	}

	ContentLevelType LevelType = CurContentLevel->GetContentLevelType();
	switch (LevelType)
	{
	case ContentLevelType::NONE:
	{
		MsgAssert("콘텐츠레벨타입이 NONE 입니다. Level 의 Start 에서 타입을 세팅해주세요.");
		break;
	}
	case ContentLevelType::OfficeLevel:
	{

		break;
	}
	case ContentLevelType::FortressLevel:
	{
		std::shared_ptr<FortressLevel> CurLevel = CurContentLevel->DynamicThis<FortressLevel>();
		std::shared_ptr<Map_Fortress> CurMap = CurLevel->GetMap();

		// 이렇게 가져와서
		// CurMap->GetCullingObject();
		// SetCullingObject(); <-- 인자넣어서 호출해서 함수안에서 컬링할녀석들을 세팅해준다. 
		// 그리고 Culling 함수에서 여차저차 어쩌구저쩌구
		break;
	}
	case ContentLevelType::FrogBossLevel:
		break;
	default:
		break;
	}
}

void CullingManager::Update(float _DeltaTime)
{
	Culling();
}

void CullingManager::Culling()
{
	int a = 0;
}
