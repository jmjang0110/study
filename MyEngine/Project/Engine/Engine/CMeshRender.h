#pragma once
#include "CComponent.h"

/*
====================
헤더를 적은 이유 
====================
Ptr : 스마트 포인터랄 template로 구현했다.	
	  template 는 전방선언으로 하면 안되고 
	  원래 정체를 알아야 한다. 
	  그러므로 직집적인 헤더 참조가 필요하다 .
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

