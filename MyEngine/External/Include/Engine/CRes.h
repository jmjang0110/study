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
	// ���� ���� �Լ��� ������ CRes �� ��ӹ޴� Ŭ�������� 
	// ���� Load �Լ������ �־���Ѵ�. ( CRes�� ��ü���� �Ұ� - ���������Լ� �ֱ� ����) 
	// CRes �� ��ü ���� ������ �ƴ϶� ��� ���ҽ����� ��ü �θ� ����
	// �� �Ѵٴ� ������� ���������Լ��� �ξ���� �ʿ䰡 �ֱ⿡ 
	// ���������Լ��� �߰��ߴ�. 
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

