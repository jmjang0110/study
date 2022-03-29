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


	// Rendering 하기 직전에 상수버퍼를 전달한다. 
	// 이렇게 하지 않으면 마지막에 넣은 상수버퍼로 전부 render 될 것이다. 
	Transform()->UpdateData();
	m_pShader->UpdateData();
	m_pMesh->render();


}


