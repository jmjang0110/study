#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CPathMgr.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CMesh.h"
#include "CGraphicsShader.h"
#include "CConstBuffer.h"



/*
	Vertex ( ���� )
	* ������ �����ų ���� �ϳ��� 
	* GPU �޸𸮿� ���� �� GPU �޸𸮸� �����ϴ� ������ �Ѵ�. 
	* 
	* Blob : C++ �ڵ� �ۼ� - ���� ���� �̷������� 
	* Shader �ڵ带 Compile �ؼ� GPU �� ������ �� �ִ� ���̳ʸ��� �ٲ� 
	* Compile �� ���������ͷ� ������� ���̴� �ڵ带 �޸𸮻� �����ϰ� 
	* GPU �� �����ؾ��� �װ��� �����ϴ°� Blob �̴�. Blob �� Vertex Shader �ν�
	* ������ �ڵ�� �� ��������� dx �� Vertex Shader�� ����� �� blob �� �޶�� ���� �ʰ�
	* ID3D11VertexShader �� �޶�� �Ѵ�. 
	* �׷��� ������ Blob �� �̿��ؼ� ID3D11VertexShader ��ü�� ������ 
	* Vertex Shader Setting �Լ����ٰ� ID3D11VertexShader ��ü�� �����ؾ��Ѵ�.
	* 
	* 
*/

// ���� ��ġ 
Vertex arrVtx[4] = {};
Vec4	g_vPos;

CMesh*				g_pMesh = nullptr;		// ����� ����	
CGraphicsShader*	g_pShader = nullptr;	// �׸� ��� 
CConstBuffer*		g_pCB = nullptr;



/*
	Shader ( ���̴� )
	*
	* GPU �� ���� �� �Լ� 
	=== [ Rendering Pipelint ] === 
	* Vertex Shader 	
	* Hull Shader 		-----> [ Tesellation ]
	* Domain Shader		-----> [ Tesellation ]
	* Geometry Shader
	* Pixel Shader 
	
	* Compute Shader	-----> [ GPGPU ]
	* 
	* Rendering Pipelint : 
	*	- ��ü�� �׷����� ���� 
	*	- 3���� ������ 2�������� �׷����� ���� 
	* 
	* IA ( Input Assembler ) : �׷��� ��ü�� ����
		(������ ���� ���� _ �����Ʈ ������ ���� �����ΰ� _ Input LayOut)
		, ������ ���� ������ �ԷµǴ� �ܰ� 
	*	- ������ ���ο� �ʿ��� �����͵��� �ԷµǴ� �ܰ�
	* 
	* ���������ο� �ʿ��� �����͵��� �Էµ� ��
	* - Vertex Shader �� ����ȴ�. 
	* Vertex Shader ---> ���� �ϳ��� ���� �Ǵ� �Լ�, ������ NDC ( ���� ��ǥ�� )�� �̵� 
	* 
	* - Hull Shader , Domain Shader �� ���ؼ� ������ �߰��� �� ������ �� �ִ�. ( �뷮 ) Dx11 
	*	- ( ������ ���������� ���߿� ������Ŵ )
	* 
	* Geometry Shader ---> ������ ������ ���� ���߿� ������Ŵ ( ���� ) Dx10
	* 
	* Rasterizer ---> Culling ( �������� �̷�� ������ ���� ������ ���� Culling )
	*				  ������ ���� �ȼ��� ���� ( �ȼ� ���̴��� ȣ��� �ĺ��� ã�� )
	* 
	* Pixel Shader ---> Pixel ���� ȣ�� �� �Լ� 
	* 
	* [ OM �ܰ� : Output Merge ]
	* Depth Stencil State Test ---> �ȼ��� ���̰��� ���� �ؽ��Ŀ� ���ؼ� ���������� ���� 
	*								�ƹ��͵� �������ϸ� Default ��
	* 
	* Blend State Test
	* ȥ�� ���Ŀ� ���� ���� ---> ���� Ÿ�ٿ� ��� 
	
	
	*/

void TestInit()
{

	// ���� ������ 
	
	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);


	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	UINT arrIdx[6] = { 0,2,3,0,1,2 };

	g_pMesh = new CMesh;
	g_pMesh->Create(arrVtx,4, arrIdx, 6);


	

	
	/*

		* Shader �ʿ����� ���� struct �� ���� ����ü�� �����ϰ� (Vertex)
		* �� ���θ� � �������� �з��� �س����� ������ �𸥴�.
		* �׳� Sizeof(Vertex) * 3 ���� ����� �ȴ�.
		* �̰� IA �ܰ迡�� �޸� �����ּ� �˷��ְ�
		* ������ �ϳ��� ����ĥ Size �� �˷��ش�.
		* �׷� Vertex Shader ���� 28����Ʈ�� Size�� �˷���ٸ� 28 ����Ʈ ��ŭ�� ���� �ϳ��� ����
		* ���� �ϳ��� Vertex Shader �Լ��� �ϳ��� ȣ�� ��Ų��.
		* �ٵ� �ű⼭ 12����Ʈ�� ���� 16����Ʈ�� ����� �س��� .
		* ���⼭ semantic �� �ʿ��ϴ� . vPos �󸶸�ŭ���� vColor �󸶸�ŭ������ �����ؼ�
		* semantic ���� ����/���� ������ �˸���.
		* semantic�� �̹� �������� �־�����, �� �̸��� �����ָ� �ȴ�.


	*/

	//** InputLayout ���� [���� �Է� ����] * *

	D3D11_INPUT_ELEMENT_DESC tInputDesc = {};
	UINT iOffset = 0;


	tInputDesc.SemanticName = "POSITION"; // semantic �̸� 
	tInputDesc.SemanticIndex = 0;		  // �ߺ� �̸��� ��� �ε����� ���� 
	tInputDesc.InputSlot = 0;				// 0 ���� ��ġ�� ���� ���̴�. 
	tInputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA; // ���� �����̴�. ( ���� �����ϴ� �� �����ʹ� ������ �ϳ��� ������� ���̴�. ) 
	tInputDesc.InstanceDataStepRate = 0;
	tInputDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT; // float3 Ÿ���̶�� ����� �˸���. 
	tInputDesc.AlignedByteOffset = iOffset;			// ���� ù��° 
	iOffset += 12; // POSITION ũ�Ⱑ 12 ����Ʈ �̹Ƿ� Offset ũ�⸦ 12 �ø���.

	CGraphicsShader::AddInputLayout(tInputDesc);

	tInputDesc.SemanticName = "COLOR";
	tInputDesc.SemanticIndex = 0;
	tInputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tInputDesc.InstanceDataStepRate = 0;
	tInputDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	tInputDesc.AlignedByteOffset = iOffset;
	iOffset += 16;


	CGraphicsShader::AddInputLayout(tInputDesc);

	



	// ========================== ��� ���� ==================================
	g_pCB = new CConstBuffer(CB_TYPE::TRANSFORM);
	g_pCB->Create(sizeof(Vec4));

	D3D11_BUFFER_DESC tBufferDesc = {};

	

	g_pShader = new CGraphicsShader;
	g_pShader->CreateVertexShader(L"shader\\test.fx", "VS_Test"); // ( CreateInputLayout �Լ��� ���� )
	g_pShader->CreatePixelShader(L"shader\\test.fx", "PS_Test");

 }

void TestUpdate()
{
	// ���� Ű�� ������ �ִٸ� 
	if (KEY_PRESSED(KEY::LEFT))
	{
		g_vPos.x -= DT * 0.5f;
	}


	// ���� Ű�� ������ �ִٸ� 
	if (KEY_PRESSED(KEY::RIGHT))
	{
		g_vPos.x += DT * 0.5f;
	}

	g_pCB->SetData(&g_vPos, sizeof(Vec4));

}

void TestRender()
{
	CDevice::GetInst()->ClearTarget();

	// ��� ���۰� Vertex Shader ������ �´�.
	// ( ���޵� ��� ���� Object �� ��ġ�� �ȴ�. 

	// render 
	// IA ���� -- �Ʒ� CONTEXT �Լ� ȣ�� ������ ����̾���. �׳� ������ ������ �Ѱ����� ������ �ϴ� ���� �ƴϱ� ���� 
	g_pShader->UpdateData();
	g_pCB->UpdateData(); // �������Ϳ� ����
	//CONTEXT->Draw(6, 0); // OffSet ���� ���� �󸶳� ����� �������� �˸���. 
	g_pMesh->render();

	CDevice::GetInst()->Present();

}

void TestRelease()
{
	SAFE_DELETE(g_pMesh);
	SAFE_DELETE(g_pShader);
	SAFE_DELETE(g_pCB);


}
