#pragma once

class CGameObject;

/*
	
	CEventMgr

	게임이 동작하고 있는 도중에 
	물체를 생성 할 때 무조건 EventMgr 을 통해서 생성한다. 

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

