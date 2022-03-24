#include "pch.h"
#include "CMesh.h"

#include "CDevice.h"



CMesh::CMesh()
	: m_tVBDesc{}
	, m_tIBDesc{}
	, m_iVtxCount(0)
	, m_iIdxCount(0)
	,m_pVtxSys(nullptr)
	, m_pIdxSys(nullptr)

{
	
}

CMesh::~CMesh()
{
	SAFE_DELETE(m_pVtxSys);
	SAFE_DELETE(m_pIdxSys);


}



int CMesh::Create(void* _pVtxSys, UINT _iVtxCount, void* _pIdxSys, UINT _iIdxCount)
{
	m_iVtxCount = _iVtxCount;
	m_iIdxCount = _iIdxCount;



	//========================== ���ؽ� ���� ����� ==========================

	// ���� ��ü�� ���� GPU �� �Űܾ� �Ѵ� 
	// ���� �����͸� ������ ���ؽ� ���۸� �����Ѵ�. 
	m_tVBDesc.ByteWidth = sizeof(Vertex) * _iVtxCount;// ��������� ũ��� 

	// 1. ���� ���� ���Ŀ���, ������ ������ ���� �� �� �ִ� �ɼ�
	// 2. 1.���� ������ ����X �������� �ٲ� 
	m_tVBDesc.CPUAccessFlags = 0; // D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // RAM ���� ���� GPU�� ���� �� ���� ��ġ�� �ٲ�� �� �ٽ� �ǳ��� .
	m_tVBDesc.Usage = D3D11_USAGE_DEFAULT; //D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	/*
		*
		* tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		*
		*	ID3D11Buffer �� ������ ������
		*	�� ���۰� �����ϰ� �ִ� GPU�� �޸� �����ȿ� ����Ǿ��ִ�
		*	������ Ÿ���� � ������ ��� ���� ���� ������ �̸� ������ �س��� ���̴� .
		*	�̷��� �ؾ� ���������� ����ȭ�� �����ϴ�.
	*/
	// ������ �����ϴ� ������ ���� ���� �˸�
	m_tVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	m_tVBDesc.MiscFlags = 0;
	m_tVBDesc.StructureByteStride = 0;

	// �ʱ� �����͸� �Ѱ��ֱ� ���� ���� ����ü 
	D3D11_SUBRESOURCE_DATA tSubDesc = {};
	tSubDesc.pSysMem = _pVtxSys;

	if (FAILED(DEVICE->CreateBuffer(&m_tVBDesc, &tSubDesc, m_VB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// ==========================  �ε��� ���� ����� ==========================


	m_tIBDesc = {};
	m_tIBDesc.ByteWidth = sizeof(UINT) * _iIdxCount;// ��������� ũ��� 

	// ���� ���� ���Ŀ���, ������ ������ ���� �� �� �ִ� �ɼ� 
	m_tIBDesc.CPUAccessFlags = 0; // RAM ���� ���� GPU�� ���� �� ���� ��ġ�� �ٲ�� �� �ٽ� �ǳ��� .
	m_tIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	// ������ �����ϴ� ������ ���� ���� �˸�
	m_tIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	m_tIBDesc.MiscFlags = 0;
	m_tIBDesc.StructureByteStride = 0;

	// �ʱ� �����͸� �Ѱ��ֱ� ���� ���� ����ü 
	tSubDesc = {};
	tSubDesc.pSysMem = _pIdxSys; // ���� �ּ� 

	if (FAILED(DEVICE->CreateBuffer(&m_tIBDesc, &tSubDesc, m_IB.GetAddressOf())))
	{
		return E_FAIL;
	}

	
	// ============== System Memory �� ����� Vertex, Index ���� ���� ==============
	m_pVtxSys = new Vtx[m_iVtxCount];
	memcpy(m_pVtxSys, _pVtxSys, sizeof(Vtx) * m_iVtxCount);

	m_pIdxSys = new UINT[m_iIdxCount];
	memcpy(m_pIdxSys, _pIdxSys, sizeof(UINT) * m_iIdxCount);


	return S_OK;
}

void CMesh::render()
{

	UpdateData();
	CONTEXT->DrawIndexed(m_iIdxCount, 0, 0);
}


void CMesh::UpdateData()
{
	UINT iStride = sizeof(Vtx);
	UINT iOffSet = 0;
	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &iStride, &iOffSet);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);


}
