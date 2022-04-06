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
	// Dead Object ����
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		assert(m_vecDead[i]);
		delete m_vecDead[i];
	}
	m_vecDead.clear();


	// Event ó��
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
				// ���⼭ ���� ��ü���� ���� �����ӿ��� �����ȴ� .
				m_vecDead.push_back(pDeleteObject);
				pDeleteObject->m_bDead = true;
			}
		}
		break;
		

		case EVENT_TYPE::ADD_CHILD:
		{
			CGameObject* pParent = (CGameObject*)m_vecEvent[i].lParam;
			CGameObject* pChild = (CGameObject*)m_vecEvent[i].wParam;

			// pChild �� Ư�� ���̾�� �ֻ��� ������Ʈ ���µ�
			// ADD_CHILD �� Ư�� ��ü�� �ڽ��� �Ǿ���. 
			// pChild �� Ư�� ���̾� �Ҽ��� �����ϸ鼭 
			// pParent ��ü �Ҽ� ���̾�� �Ҽӵȴ�. 
			// �� 2�� �̻��� ���̾ �Ҽӵȴٴ� ���̴�. 
			int iLayerIdx = pChild->m_iLayerIdx;
			pChild->Deregister();
			pChild->m_iLayerIdx = iLayerIdx;

			pParent->AddChild(pChild);

		}
		break;
		}

		

		// �̺�Ʈ �߿� Stage ���� �̺�Ʈ�� �־��ٸ�,
		// ������ �̺�Ʈ�� �� �����ϰ� ����
		if (bChangeStage)
		{
			break;
		}
	}

	m_vecEvent.clear();
}