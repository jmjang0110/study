#pragma once

// === 모든 클래스의 최상위 클래스 === 


class CEntity
{
private:
	static UINT g_iNextID;


private:
	wstring m_strName;
	const UINT m_iID;

public:
	void SetName(const wstring& _name) { m_strName = _name; }
	const wstring& GetName() { return m_strName; }
	UINT GetID() { return m_iID; }

public:
	virtual void UpdateData() {}

	virtual CEntity* Clone() = 0; // 반드시 구현해야한다. 



public:
	CEntity();
	CEntity(const CEntity& _origin);
	virtual ~CEntity();


	
};

