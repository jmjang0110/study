#pragma once
#include "CEntity.h"

#include "ptr.h"


class CRes : 
	public CEntity
{

private:
	wstring		m_strKey;
	wstring		m_strRelativePath;
	UINT		m_iRefCount;


protected:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey;}
	void SetRelativePath(const wstring& _strRelativePath) { m_strRelativePath = _strRelativePath; }
	bool CheckFail(HRESULT _hr);

public:
	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

protected:
	// 순수 가상 함수가 있으니 CRes 를 상속받는 클래스들은 
	// 전부 Load 함수기능이 있어야한다. ( CRes는 객체생성 불가 - 순수가상함수 있기 때문) 
	// CRes 는 객체 생성 목적이 아니라 모든 리소스들의 객체 부모 역할
	// 을 한다는 명분으로 순수가상함수를 두어야할 필요가 있기에 
	// 순수가상함수를 추가했다. 
	virtual int Load(const wstring& _strFilePath) = 0;
	CLONE_DISABLE(CRes)


private:
	void AddRef() { ++m_iRefCount; }
	void SubRef() { --m_iRefCount; }
	
public:
	CRes();
	virtual ~CRes();


	friend class CResMgr;

	template<typename T>
	friend class Ptr;

};

