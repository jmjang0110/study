#include "pch.h"
#include "CCamera.h"

#include "CTransform.h"
#include "CDevice.h"



CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
{
}

CCamera::~CCamera()
{
}


void CCamera::finalupdate()
{

	// ** View 행렬 **
	Vec3 vCamPos = Transform()->GetPos();
	// z축만 바라본다는 가정하에 View 행렬 변환 ( 회전 없음 )
	m_matView = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);


	// ** Proj 행렬 ** 
	Vec2 vRenderfResolution = CDevice::GetInst()->GetRenderResolution();
	m_matProj = XMMatrixOrthographicLH(vRenderfResolution.x, vRenderfResolution.y, 0.f, 5000.f);

	g_transform.matView = m_matView;
	g_transform.matProj = m_matProj;


}