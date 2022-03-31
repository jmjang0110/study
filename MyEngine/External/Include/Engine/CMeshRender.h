#pragma once
#include "CComponent.h"

class CMeshRender :
	public CComponent
{

private:

	class CMesh*		m_pMesh;
	class CMaterial*	m_pMtrl;

public:
	void SetMesh(CMesh* _pMesh) { m_pMesh = _pMesh; }

	void SetMaterial(CMaterial* _pMtrl) { m_pMtrl = _pMtrl;}


	CMesh* GetMesh() { return m_pMesh; }
	CMaterial* GetMaterial() { return m_pMtrl; }



public:
	virtual void finalupdate() override;
	virtual void render() override;


public:
	CMeshRender();
	~CMeshRender();



};

