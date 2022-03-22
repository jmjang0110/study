#include "pch.h"
#include "Temp.h"

#include "CDevice.h"

/*
	Vertex ( 정점 )
	

*/

// 정점을 저장시킬 버퍼 하나를 
// GPU 메모리에 만들어서 그 GPU 메모리를 관리하는 역할을 한다. 


ComPtr<ID3D11Buffer> g_pVB; 


void TestInit()
{
	// 지역 변수들 
	Vertex arrVtx[3] = {};
	arrVtx[0].vPos = Vec3(0.f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	arrVtx[1].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	arrVtx[2].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	// 버퍼 객체를 만들어서 GPU 로 옮겨야 한다 
	// 정점 데이터를 저장할 버텍스 버퍼를 생성한다. 
	D3D11_BUFFER_DESC tBufferDesc = {};
	tBufferDesc.ByteWidth = sizeof(Vertex) * 3;// 어느정도의 크기냐 
	
	// 버퍼 생성 이후에도, 버퍼의 내용을 수정 할 수 있는 옵션 
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // RAM 에서 만들어서 GPU로 보낼 때 정점 위치가 바뀌는 걸 다시 건낸다 .
	tBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;


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
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	tBufferDesc.MiscFlags = 0;
	tBufferDesc.StructureByteStride = 0;


	// 초기 데이터를 넘겨주기 위한 정보 구조체 
	D3D11_SUBRESOURCE_DATA tSubDesc = {};
	tSubDesc.pSysMem = arrVtx;

	DEVICE->CreateBuffer(&tBufferDesc, &tSubDesc, g_pVB.GetAddressOf());
	
}

void TestUpdate()
{


}

void TestRender()
{
	CDevice::GetInst()->ClearTarget();

	// render 



	CDevice::GetInst()->Present();


}
