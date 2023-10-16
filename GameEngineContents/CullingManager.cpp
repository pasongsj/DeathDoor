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

		// 맵의 트리거와 컬링오브젝트를 세팅해준다.
		m_vCullingTriggers = CurMap->GetCullingTrigger();
		m_vCullingObjects = CurMap->GetCullingObject();

		break;
	}
	case ContentLevelType::FrogBossLevel:
		break;
	default:
		break;
	}

	// 여기서 트리거와 오브젝트를 링크시킨다. 
	LinkTrigger(LevelType);
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
	for (int i = 0; i < static_cast<int>(TriggerSize); ++i)
	{
		// 플레이어와 충돌했고 
		if (true == m_vCullingTriggers[i]->CheckCollision(PhysXFilterGroup::PlayerDynamic))
		{
			// 트리거가 발동되지 않았다면 
			if (false == m_vCullingTriggers[i]->IsActivate())
			{
				m_vCullingTriggers[m_iCurTrigger_Idx]->TriggerOff();
				m_iCurTrigger_Idx = i;
				if (0 <= m_iCurCullingObj_Idx0)
				{
					Off_Trigger();
				}
				// 활성화 할 트리거 인덱스를 세팅 후 트리거 on 
				Set_ActiveTrigger_Index(i);
				m_vCullingTriggers[i]->TriggerOn();


				// idx 변수 초기화
				CullingObjIdxClear();

				// 트리거에 지정된 오브젝트 넘버 받아오고 
				std::vector<int> Numbers = m_vCullingTriggers[i]->Get_CullingObjectNumbers();
				size_t Size = Numbers.size();

				// 인덱스 넘버지정 
				m_iCurCullingObj_Idx0 = Numbers[0];
				m_iCurCullingObj_Idx1 = Numbers[1];

				if (Size == 3)
				{
					m_iCurCullingObj_Idx2 = Numbers[2];
				}

				for (size_t i = 0; i < Size; i++)
				{
					int Idx = Numbers[i];
					m_vCullingObjects[Idx]->GetRenderer()->On();
				}
			}
			
		}

		// 업데이트 전까지는 이렇게 해줘야함 
		m_vCullingTriggers[i]->isPhysXCollision = 0;
	}
}

template<typename EnumType>
void CullingManager::LinkTrigger(EnumType _LevelType)
{
	ContentLevelType LevelType = static_cast<ContentLevelType>(_LevelType);
	
	// 오브젝트와 트리거를 링크한다.
	size_t TriggersSize = m_vCullingTriggers.size();
	size_t ObjectsSize = m_vCullingObjects.size();

	if (TriggersSize <= static_cast<size_t>(0) || ObjectsSize <= static_cast<size_t>(0))
	{
		MsgAssert("벡터의 사이즈가 0 입니다. 트리거와 오브젝트가 자료구조에 저장되었는지 확인하세요.");
		return;
	}

	switch (LevelType)
	{
	case ContentLevelType::OfficeLevel:
		break;
	case ContentLevelType::FortressLevel:
	{
		// 최소두개, 최대 3개까지 지정가능
		m_vCullingTriggers[0]->Set_CullingObjectNumber(0, 1);		 // 플레이어 생성위치 
		m_vCullingTriggers[1]->Set_CullingObjectNumber(1, 2);		 // 초반부 큰 문 입구
		m_vCullingTriggers[2]->Set_CullingObjectNumber(2, 3);		 // 이후 우측으로 꺾어서 레버 당기는 곳
		m_vCullingTriggers[3]->Set_CullingObjectNumber(2, 3, 4);	 // 생성된 사다리로 위쪽으로 올라가고 나서 바로 
		m_vCullingTriggers[4]->Set_CullingObjectNumber(4, 5);		 // 아래쪽 낙하 이후 처음 나오는 사각형 공간 지나가는 부분 
		


		break;
	}
	case ContentLevelType::FrogBossLevel:
		break;
	}

	CheckLink();
}

void CullingManager::On_FirstTrigger()
{
	m_vCullingTriggers[0]->TriggerOn();
	
	m_iCurCullingObj_Idx0 = 0;
	m_iCurCullingObj_Idx1 = 1;
	m_vCullingObjects[0]->GetRenderer()->On();
	m_vCullingObjects[1]->GetRenderer()->On();
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
			// 일단 주석 
			// MsgAssert("트리거와의 링크가 정상적으로 실행되지 않았습니다.");
			return;
		}
	}
}

inline void CullingManager::Set_ActiveTrigger_Index(int _Index)
{
	size_t TriggersSize = m_vCullingTriggers.size();

	if (_Index >= TriggersSize)
	{
		MsgAssert("인덱스 값이 잘못되었습니다.");
		return;
	}

	m_iCurTrigger_Idx = _Index;
}

void CullingManager::Off_Trigger()
{
	m_vCullingObjects[m_iCurCullingObj_Idx0]->GetRenderer()->Off();
	m_vCullingObjects[m_iCurCullingObj_Idx1]->GetRenderer()->Off();

	if (m_iCurCullingObj_Idx2 == -1)
	{
		return;
	}

	m_vCullingObjects[m_iCurCullingObj_Idx2]->GetRenderer()->Off();
}

// 지금해야될건? 
// 컬링매니저에서 가지고 있는 트리거들의 충돌검사를 수행한다. 