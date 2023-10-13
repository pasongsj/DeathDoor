#include "PrecompileHeader.h"
#include "CullingManager.h"

#include "FortressLevel.h"
#include "OfficeLevel.h"

#include "Map_Fortress.h"

#include "CullingObject.h"
#include "CullingTrigger.h"

#include "Player.h"

CullingManager::CullingManager()
{
}

CullingManager::~CullingManager()
{
}

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

		m_vCullingTriggers = CurMap->GetCullingTrigger();
		m_vCullingObjects = CurMap->GetCullingObject();

		// 여기서 트리거와 오브젝트를 링크시킨다. 
		LinkTrigger();

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
	if (0.3f >= GetLiveTime())
	{
		On_FirstTrigger();

		size_t TriggerSize = m_vCullingTriggers.size();
		for (size_t i = 0; i < TriggerSize; ++i)
		{
			// 업데이트 전까지는 이렇게 해줘야함 
			m_vCullingTriggers[i]->isPhysXCollision = 0;
		}

		
		return;
	}

	Culling();
}

void CullingManager::Culling()
{
	

	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	
	size_t TriggerSize = m_vCullingTriggers.size();

	// 여기서 트리거 온체크를 해줘
	for (size_t i = 0; i < TriggerSize; ++i)
	{
		// 플레이어와 충돌했고 
		if (true == m_vCullingTriggers[i]->CheckCollision(PhysXFilterGroup::PlayerDynamic))
		{
			// 트리거가 발동되지 않았다면 
			if (false == m_vCullingTriggers[i]->IsActivate())
			{
				m_vCullingTriggers[i]->TriggerOn();
				m_vCullingTriggers[i]->On_CullingObject();

				// 그리고 바로 전 트리거의 첫번째 컬링 오브젝트를 Off 처리
				if (i > 0)
				{
					m_vCullingTriggers[i - 1]->Off_CullingObject();
				}
			}
			
		}

		// 업데이트 전까지는 이렇게 해줘야함 
		m_vCullingTriggers[i]->isPhysXCollision = 0;
	}
}


void CullingManager::LinkTrigger()
{
	// 오브젝트와 트리거를 링크한다.
	size_t TriggersSize = m_vCullingTriggers.size();
	size_t ObjectsSize = m_vCullingObjects.size();

	if (TriggersSize <= static_cast<size_t>(0) || ObjectsSize <= static_cast<size_t>(0))
	{
		MsgAssert("벡터의 사이즈가 0 입니다. 트리거와 오브젝트가 자료구조에 저장되었는지 확인하세요.");
		return;
	}

	// 트리거 하나당 컬링 오브젝트를 링크하고 
	// ex ) 1번 트리거 : 1,2 번 컬링오브젝트 , 2번트리거 : 2,3 번 컬링오브젝트
	// 트리거 작동시 링크되어있는 컬링오브젝트의 렌더러를 ON 시킨다. 
	for (size_t i = 0; i < TriggersSize; ++i)
	{
		m_vCullingTriggers[i]->Set_CullingObject(m_vCullingObjects[i], m_vCullingObjects[i + 1]);
	}

	CheckLink();
}

void CullingManager::On_FirstTrigger()
{
	m_vCullingTriggers[0]->TriggerOn();
	m_vCullingTriggers[0]->On_CullingObject();
}

void CullingManager::CheckLink()
{
	std::vector<std::shared_ptr<CullingObject>>::iterator StartIter = m_vCullingObjects.begin();
	std::vector<std::shared_ptr<CullingObject>>::iterator EndIter = m_vCullingObjects.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		// 하나라도 false 라면 에러
		if (false == (*StartIter)->IsLink())
		{
			MsgAssert("트리거와의 링크가 정상적으로 실행되지 않았습니다.");
			return;
		}
	}
}

// 지금해야될건? 
// 컬링매니저에서 가지고 있는 트리거들의 충돌검사를 수행한다. 