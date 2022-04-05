#include "pch.h"
#include "CEventMgr.h"

#include "CGameObject.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	// Dead Object 삭제
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		assert(m_vecDead[i]);
		delete m_vecDead[i];
	}
	m_vecDead.clear();


	// Event 처리
	bool bChangeStage = false;

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		switch (m_vecEvent[i].eType)
		{
		case EEVENT_TYPE::CREATE_OBJ:
			// lParam : Object Adress, wParam : Object Type
		{

		}
		break;

		case EEVENT_TYPE::DELETE_OBJ:
			// lParam : Object Adress
		{

		}
		break;
		case EEVENT_TYPE::STAGE_CHANGE:
			// lParam : Next Stage Enum		

			break;

		case EEVENT_TYPE::CHANGE_AI_STATE:
		{
			// lParam : FSM Adress, wParam : Next State Type

		}
		break;
		}

		// 이벤트 중에 Stage 변경 이벤트가 있었다면,
		// 나머지 이벤트는 다 무시하고 종료
		if (bChangeStage)
		{
			break;
		}
	}

	m_vecEvent.clear();
}