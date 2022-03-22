#include "pch.h"
#include "Temp.h"

#include "CDevice.h"

/*
	Vertex ( ���� )
	

*/

// ������ �����ų ���� �ϳ��� 
// GPU �޸𸮿� ���� �� GPU �޸𸮸� �����ϴ� ������ �Ѵ�. 


ComPtr<ID3D11Buffer> g_pVB; 


void TestInit()
{
	// ���� ������ 
	Vertex arrVtx[3] = {};
	arrVtx[0].vPos = Vec3(0.f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	arrVtx[1].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	arrVtx[2].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	// ���� ��ü�� ���� GPU �� �Űܾ� �Ѵ� 
	// ���� �����͸� ������ ���ؽ� ���۸� �����Ѵ�. 
	D3D11_BUFFER_DESC tBufferDesc = {};
	tBufferDesc.ByteWidth = sizeof(Vertex) * 3;// ��������� ũ��� 
	
	// ���� ���� ���Ŀ���, ������ ������ ���� �� �� �ִ� �ɼ� 
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // RAM ���� ���� GPU�� ���� �� ���� ��ġ�� �ٲ�� �� �ٽ� �ǳ��� .
	tBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;


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
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	tBufferDesc.MiscFlags = 0;
	tBufferDesc.StructureByteStride = 0;


	// �ʱ� �����͸� �Ѱ��ֱ� ���� ���� ����ü 
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
