#pragma once
#include "CComponent.h"

/*
====================
����� ���� ���� 
====================
Ptr : ����Ʈ �����Ͷ� template�� �����ߴ�.	
	  template �� ���漱������ �ϸ� �ȵǰ� 
	  ���� ��ü�� �˾ƾ� �Ѵ�. 
	  �׷��Ƿ� �������� ��� ������ �ʿ��ϴ� .
*/
#include "CMesh.h"
#include "CMaterial.h"


class CMeshRender :
	public CComponent
{

private:

	Ptr<CMesh>	m_pMesh;
	Ptr<CMaterial>	m_pMtrl;

public:
	void SetMesh(Ptr<CMesh> _pMesh) { m_pMesh = _pMesh; }
	void SetMaterial(Ptr<CMaterial> _pMtrl) { m_pMtrl = _pMtrl;}


	Ptr<CMesh>  GetMesh() { return m_pMesh; }
	Ptr<CMaterial> GetMaterial() { return m_pMtrl; }



public:
	virtual void finalupdate() override;
	virtual void render() override;

	CLONE(CMeshRender)


public:
	CMeshRender();
	~CMeshRender();



};

