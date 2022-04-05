#pragma once

class CGameObject;

/*
	
	CEventMgr

	������ �����ϰ� �ִ� ���߿� 
	��ü�� ���� �� �� ������ EventMgr �� ���ؼ� �����Ѵ�. 

*/
class CEventMgr
	: public CSingleton<CEventMgr>
{
	SINGLE(CEventMgr)

private:
	vector<tEventInfo>		m_vecEvent;
	vector<CGameObject*>	m_vecDead;

public:
	void update();

public:
	void AddEvent(const tEventInfo& _event) { m_vecEvent.push_back(_event); }

};

