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

#include "CGameObject.h"
#include "CMeshRender.h"
#include "CTransform.h"

#include "CPlayerScript.h"

CGameObject* g_pObj = nullptr;


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
	g_pObj = new CGameObject;
	g_pObj->SetName(L"Player");
	g_pObj->AddComponent(new CTransform);
	g_pObj->AddComponent(new CMeshRender);
	g_pObj->AddComponent(new CPlayerScript);


	g_pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	g_pObj->MeshRender()->SetShader(CResMgr::GetInst()->FindRes<CGraphicsShader>(L"TestShader"));

}

void TestUpdate()
{
	g_pObj->update();
	g_pObj->lateupdate();
	g_pObj->finalupdate();


}

void TestRender()
{

	// ��� ���۰� Vertex Shader ������ �´�.
	// ( ���޵� ��� ���� Object �� ��ġ�� �ȴ�. 
	// render 
	// IA ���� -- �Ʒ� CONTEXT �Լ� ȣ�� ������ ����̾���. �׳� ������ ������ �Ѱ����� ������ �ϴ� ���� �ƴϱ� ���� 


	CDevice::GetInst()->ClearTarget();

	// Render
	g_pObj->render();


	CDevice::GetInst()->Present();

}

void TestRelease()
{
	SAFE_DELETE(g_pObj);


}