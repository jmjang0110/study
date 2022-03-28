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
	Vertex ( 정점 )
	* 정점을 저장시킬 버퍼 하나를
	* GPU 메모리에 만들어서 그 GPU 메모리를 관리하는 역할을 한다.
	*
	* Blob : C++ 코드 작성 - 기계어 번역 이런식으로
	* Shader 코드를 Compile 해서 GPU 가 이해할 수 있는 바이너리로 바꿈
	* Compile 후 이진데이터로 만들어진 쉐이더 코드를 메모리상에 저장하고
	* GPU 에 전달해야함 그것을 저장하는게 Blob 이다. Blob 에 Vertex Shader 로써
	* 동작할 코드는 다 들어있지만 dx 는 Vertex Shader를 사용할 때 blob 을 달라고 하지 않고
	* ID3D11VertexShader 를 달라고 한다.
	* 그렇기 때문에 Blob 을 이용해서 ID3D11VertexShader 객체를 만들어내고
	* Vertex Shader Setting 함수에다가 ID3D11VertexShader 객체를 전달해야한다.
	*
	*
*/



/*
	Shader ( 쉐이더 )
	*
	* GPU 가 실행 할 함수
	=== [ Rendering Pipelint ] ===
	* Vertex Shader
	* Hull Shader 		-----> [ Tesellation ]
	* Domain Shader		-----> [ Tesellation ]
	* Geometry Shader
	* Pixel Shader

	* Compute Shader	-----> [ GPGPU ]
	*
	* Rendering Pipelint :
	*	- 물체가 그려지는 과정
	*	- 3차원 정보가 2차원으로 그려지는 과정
	*
	* IA ( Input Assembler ) : 그려질 물체의 정보
		(정점의 내부 구조 _ 몇바이트 단위로 무슨 목적인가 _ Input LayOut)
		, 렌더링 관련 정보가 입력되는 단계
	*	- 파이프 라인에 필요한 데이터들이 입력되는 단계
	*
	* 파이프라인에 필요한 데이터들이 입력된 후
	* - Vertex Shader 가 실행된다.
	* Vertex Shader ---> 정점 하나당 실행 되는 함수, 정점을 NDC ( 투영 좌표계 )로 이동
	*
	* - Hull Shader , Domain Shader 에 의해서 정점을 추가로 더 생상할 수 있다. ( 대량 ) Dx11
	*	- ( 정점을 파이프라인 도중에 생성시킴 )
	*
	* Geometry Shader ---> 정점을 파이프 라인 도중에 생성시킴 ( 조금 ) Dx10
	*
	* Rasterizer ---> Culling ( 폴리곤을 이루는 정점의 접근 순서에 따른 Culling )
	*				  폴리곤 내부 픽셀을 검출 ( 픽셀 쉐이더가 호출될 후보를 찾음 )
	*
	* Pixel Shader ---> Pixel 마다 호출 될 함수
	*
	* [ OM 단계 : Output Merge ]
	* Depth Stencil State Test ---> 픽셀의 깊이값을 깊이 텍스쳐와 비교해서 가려지는지 판정
	*								아무것도 설정안하면 Default 값
	*
	* Blend State Test
	* 혼합 공식에 따른 블렌딩 ---> 렌더 타겟에 출력


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

	// 상수 버퍼가 Vertex Shader 시점에 온다.
	// ( 전달된 상수 값이 Object 의 위치가 된다. 
	// render 
	// IA 전달 -- 아래 CONTEXT 함수 호출 순서는 상관이없다. 그냥 저렇게 설정을 한것이지 수행을 하는 것이 아니기 때문 


	CDevice::GetInst()->ClearTarget();

	// Render
	g_pObj->render();


	CDevice::GetInst()->Present();

}

void TestRelease()
{
	SAFE_DELETE(g_pObj);


}