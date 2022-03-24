#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CPathMgr.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"

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

	// ��� ���۰� Vertex Shader ������ �´�.
	// ( ���޵� ��� ���� Object �� ��ġ�� �ȴ�. 
	// render 
	// IA ���� -- �Ʒ� CONTEXT �Լ� ȣ�� ������ ����̾���. �׳� ������ ������ �Ѱ����� ������ �ϴ� ���� �ƴϱ� ���� 


	CDevice::GetInst()->ClearTarget();

	// Render
	
	// ����� ���̴� 
	CGraphicsShader* pShader = CResMgr::GetInst()->FindRes<CGraphicsShader>(L"TestShader");
	pShader->UpdateData();	

	g_pCB->UpdateData();		// b0 �������Ϳ� ������ ��� ���� 
	//CONTEXT->Draw(6, 0);		// OffSet ���� ���� �󸶳� ����� �������� �˸���. 
	
	CMesh* pRectMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
	pRectMesh->render();		// ����� ���� ( �޽� )

	CDevice::GetInst()->Present();

}

void TestRelease()
{
	SAFE_DELETE(g_pMesh);
	SAFE_DELETE(g_pShader);
	SAFE_DELETE(g_pCB);


}
