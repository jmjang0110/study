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



	//========================== 버텍스 버퍼 만들기 ==========================

	// 버퍼 객체를 만들어서 GPU 로 옮겨야 한다 
	// 정점 데이터를 저장할 버텍스 버퍼를 생성한다. 
	m_tVBDesc.ByteWidth = sizeof(Vertex) * _iVtxCount;// 어느정도의 크기냐 

	// 1. 버퍼 생성 이후에도, 버퍼의 내용을 수정 할 수 있는 옵션
	// 2. 1.수정 버젼을 수정X 버젼으로 바꿈 
	m_tVBDesc.CPUAccessFlags = 0; // D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // RAM 에서 만들어서 GPU로 보낼 때 정점 위치가 바뀌는 걸 다시 건낸다 .
	m_tVBDesc.Usage = D3D11_USAGE_DEFAULT; //D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	/*
		*
		* tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		*
		*	ID3D11Buffer 로 통일이 되지만
		*	이 버퍼가 관리하고 있는 GPU의 메모리 공간안에 저장되어있는
		*	데이터 타입이 어떤 종류냐 라는 것을 생성 시점에 미리 세팅을 해놓는 것이다 .
		*	이렇게 해야 내부적으로 최적화가 가능하다.
	*/
	// 정점을 저장하는 목적의 버퍼 임을 알림
	m_tVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	m_tVBDesc.MiscFlags = 0;
	m_tVBDesc.StructureByteStride = 0;

	// 초기 데이터를 넘겨주기 위한 정보 구조체 
	D3D11_SUBRESOURCE_DATA tSubDesc = {};
	tSubDesc.pSysMem = _pVtxSys;

	if (FAILED(DEVICE->CreateBuffer(&m_tVBDesc, &tSubDesc, m_VB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// ==========================  인덱스 버퍼 만들기 ==========================


	m_tIBDesc = {};
	m_tIBDesc.ByteWidth = sizeof(UINT) * _iIdxCount;// 어느정도의 크기냐 

	// 버퍼 생성 이후에도, 버퍼의 내용을 수정 할 수 있는 옵션 
	m_tIBDesc.CPUAccessFlags = 0; // RAM 에서 만들어서 GPU로 보낼 때 정점 위치가 바뀌는 걸 다시 건낸다 .
	m_tIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	// 정점을 저장하는 목적의 버퍼 임을 알림
	m_tIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	m_tIBDesc.MiscFlags = 0;
	m_tIBDesc.StructureByteStride = 0;

	// 초기 데이터를 넘겨주기 위한 정보 구조체 
	tSubDesc = {};
	tSubDesc.pSysMem = _pIdxSys; // 시작 주소 

	if (FAILED(DEVICE->CreateBuffer(&m_tIBDesc, &tSubDesc, m_IB.GetAddressOf())))
	{
		return E_FAIL;
	}

	
	// ============== System Memory 에 저장된 Vertex, Index 정보 저장 ==============
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
