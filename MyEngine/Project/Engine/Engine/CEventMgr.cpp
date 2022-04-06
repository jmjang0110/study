#include "pch.h"
#include "CEventMgr.h"

#include "CGameObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
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
		case EVENT_TYPE::CREATE_OBJ:
			// lParam : Object Adress, wParam : Layer Index
		{
			CGameObject* pObj = (CGameObject*)m_vecEvent[i].lParam;
			int iLayerIdx = (int)m_vecEvent[i].wParam;
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			pCurScene->AddObject(pObj, iLayerIdx);

		}
		break;

		case EVENT_TYPE::DELETE_OBJ:
			// lParam : Object Adress
		{
			CGameObject* pDeleteObject = (CGameObject*)m_vecEvent[i].lParam;
			
			if (false == pDeleteObject->m_bDead)
			{
				// 여기서 죽은 객체들은 다음 프레임에서 삭제된다 .
				m_vecDead.push_back(pDeleteObject);
				pDeleteObject->m_bDead = true;
			}
		}
		break;
		

		case EVENT_TYPE::ADD_CHILD:
		{
			CGameObject* pParent = (CGameObject*)m_vecEvent[i].lParam;
			CGameObject* pChild = (CGameObject*)m_vecEvent[i].wParam;

			// pChild 는 특정 레이어에서 최상위 오브젝트 였는데
			// ADD_CHILD 로 특정 객체의 자식이 되었다. 
			// pChild 는 특정 레이어 소속을 유지하면서 
			// pParent 객체 소속 레이어에도 소속된다. 
			// 즉 2개 이상의 레이어에 소속된다는 것이다. 
			int iLayerIdx = pChild->m_iLayerIdx;
			pChild->Deregister();
			pChild->m_iLayerIdx = iLayerIdx;

			pParent->AddChild(pChild);

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