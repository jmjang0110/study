#include "pch.h"
#include "CMeshRender.h"

#include "CGraphicsShader.h"
#include "CMesh.h"
#include "CGameObject.h"
#include "CTransform.h"




CMeshRender::CMeshRender()
	: CComponent(COMPONENT_TYPE::MESHRENDER)
	, m_pMesh(nullptr)
	, m_pShader(nullptr)
{

}

CMeshRender::~CMeshRender()
{

}


void CMeshRender::finalupdate()
{
}

void CMeshRender::render()
{

	if (nullptr == m_pMesh || nullptr == m_pShader)
		return;

	Transform()->UpdateData();
	m_pShader->UpdateData();
	m_pMesh->render();


}


