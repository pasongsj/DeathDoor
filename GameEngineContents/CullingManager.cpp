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
				// 현재 트리거를 Off 처리 해주고
				m_vCullingTriggers[m_iCurTrigger_Idx]->TriggerOff();

				// 현재 트리거 인덱스를 변경
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

				if (0 == Size)
				{
					MsgAssert("현재 오브젝트 넘버 버퍼의 사이즈가 0 입니다.");
					return;
				}

				// 인덱스 넘버지정 
				m_iCurCullingObj_Idx0 = Numbers[0];
				m_iCurCullingObj_Idx1 = Numbers[1];
				m_iCurCullingObj_Idx2 = Numbers[2];

				if (Size == 4)
				{
					m_iCurCullingObj_Idx3 = Numbers[3];
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
		// 최소 3개, 최대 4개까지 지정가능
		// 0번 인자는 반드시 포함될 바닥메쉬인걸로 
		// 3번부터 메쉬 파트1. 
		m_vCullingTriggers[0]->Set_CullingObjectNumber(0, 3, 4);		 // 플레이어 생성위치 
		m_vCullingTriggers[1]->Set_CullingObjectNumber(0, 3, 4, 5);		 // 초반부 큰 문 입구
		m_vCullingTriggers[2]->Set_CullingObjectNumber(0, 4, 5);		 // 문 통과 후 우측으로 꺾어서 나오는 네모난 공간 
		m_vCullingTriggers[3]->Set_CullingObjectNumber(0, 5, 6);	     // 생성된 사다리로 위쪽으로 올라가고 나서 바로 
		m_vCullingTriggers[4]->Set_CullingObjectNumber(0, 1, 5, 7);	     // 위에거 다음 바로
		m_vCullingTriggers[5]->Set_CullingObjectNumber(0, 1, 7, 8);	     // 내려가서돌다리 지나고 처음나오는 네모난 공간 
		m_vCullingTriggers[6]->Set_CullingObjectNumber(0, 1, 7, 8);	     // 바로 다음 다리 건너기 전 
		m_vCullingTriggers[7]->Set_CullingObjectNumber(0, 1, 8, 9);	     // 다리 건너고 바로 
		m_vCullingTriggers[8]->Set_CullingObjectNumber(0, 1, 8, 9);      // 다리 구간 끝나고 다시 바닥지형 입성시 
		m_vCullingTriggers[9]->Set_CullingObjectNumber(1, 9, 10);        // 바로다음
		
		// 여기서부터 
		m_vCullingTriggers[10]->Set_CullingObjectNumber(1, 2, 9, 10);   // 나무다리넘어가기전 
		m_vCullingTriggers[11]->Set_CullingObjectNumber(1, 2, 9 ,10);   // 나무다리 중간
		m_vCullingTriggers[12]->Set_CullingObjectNumber(1, 2, 10, 11);      // 돌다리넘어가기전 
		m_vCullingTriggers[13]->Set_CullingObjectNumber(1, 2, 11, 12);		// 돌다리중간 
		m_vCullingTriggers[14]->Set_CullingObjectNumber(2, 12, 13);		// 마지막거기 
		m_vCullingTriggers[15]->Set_CullingObjectNumber(2, 12, 13);		// 4 사각형 들어가는 입구 

		// 세팅하면됨 
		m_vCullingTriggers[16]->Set_CullingObjectNumber(2, 13, 14);		// 4 사각형 들어가는 입구 

		// 4 사각형 마무리 구간 두개 
		m_vCullingTriggers[17]->Set_CullingObjectNumber(2, 14, 15, 16);	
		m_vCullingTriggers[18]->Set_CullingObjectNumber(2, 14, 15, 16);
		m_vCullingTriggers[19]->Set_CullingObjectNumber(2, 15, 16);

		//m_vCullingTriggers[4]->Set_CullingObjectNumber(0, 1, 5 ,7);		 // 위쪽 트리거 지난 후 바로 
		//m_vCullingTriggers[5]->Set_CullingObjectNumber(0, 1, 5, 7);	     // 


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
	m_iCurCullingObj_Idx1 = 3;
	m_iCurCullingObj_Idx2 = 4;

	m_vCullingObjects[m_iCurCullingObj_Idx0]->GetRenderer()->On();
	m_vCullingObjects[m_iCurCullingObj_Idx1]->GetRenderer()->On();
	m_vCullingObjects[m_iCurCullingObj_Idx2]->GetRenderer()->On();
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
	m_vCullingObjects[m_iCurCullingObj_Idx2]->GetRenderer()->Off();

	if (m_iCurCullingObj_Idx3 == -1)
	{
		return;
	}

	m_vCullingObjects[m_iCurCullingObj_Idx3]->GetRenderer()->Off();
}

// 지금해야될건? 
// 컬링매니저에서 가지고 있는 트리거들의 충돌검사를 수행한다. 