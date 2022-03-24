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

// 정점 위치 
Vertex arrVtx[4] = {};
Vec4	g_vPos;

CMesh*				g_pMesh = nullptr;		// 사용할 형태	
CGraphicsShader*	g_pShader = nullptr;	// 그릴 방식 
CConstBuffer*		g_pCB = nullptr;



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

	// 지역 변수들 
	
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

		* Shader 쪽에서는 내가 struct 로 정점 구조체를 설정하고 (Vertex)
		* 그 내부를 어떤 목적으로 분류를 해놨는지 단위를 모른다.
		* 그냥 Sizeof(Vertex) * 3 으로 덩어리로 안다.
		* 이건 IA 단계에서 메모리 시작주소 알려주고
		* 정점을 하나씩 끊어칠 Size 를 알려준다.
		* 그럼 Vertex Shader 에서 28바이트로 Size를 알려줬다면 28 바이트 만큼을 정점 하나로 보고
		* 정점 하나당 Vertex Shader 함수를 하나씩 호출 시킨다.
		* 근데 거기서 12바이트는 정점 16바이트는 색깔로 해놨다 .
		* 여기서 semantic 이 필요하다 . vPos 얼마만큼인지 vColor 얼마만큼인지를 지정해서
		* semantic 으로 정점/색깔 정보를 알린다.
		* semantic은 이미 종류별로 주어진다, 그 이름에 맞춰주면 된다.


	*/

	//** InputLayout 생성 [정점 입력 구조] * *

	D3D11_INPUT_ELEMENT_DESC tInputDesc = {};
	UINT iOffset = 0;


	tInputDesc.SemanticName = "POSITION"; // semantic 이름 
	tInputDesc.SemanticIndex = 0;		  // 중복 이름일 경우 인덱스로 구분 
	tInputDesc.InputSlot = 0;				// 0 번재 위치에 있을 것이다. 
	tInputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA; // 정점 정보이다. ( 내가 전달하는 이 데이터는 정점당 하나씩 들어있을 것이다. ) 
	tInputDesc.InstanceDataStepRate = 0;
	tInputDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT; // float3 타입이라고 사이즈를 알린다. 
	tInputDesc.AlignedByteOffset = iOffset;			// 가장 첫번째 
	iOffset += 12; // POSITION 크기가 12 바이트 이므로 Offset 크기를 12 늘린다.

	CGraphicsShader::AddInputLayout(tInputDesc);

	tInputDesc.SemanticName = "COLOR";
	tInputDesc.SemanticIndex = 0;
	tInputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tInputDesc.InstanceDataStepRate = 0;
	tInputDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	tInputDesc.AlignedByteOffset = iOffset;
	iOffset += 16;


	CGraphicsShader::AddInputLayout(tInputDesc);

	



	// ========================== 상수 버퍼 ==================================
	g_pCB = new CConstBuffer(CB_TYPE::TRANSFORM);
	g_pCB->Create(sizeof(Vec4));

	D3D11_BUFFER_DESC tBufferDesc = {};

	

	g_pShader = new CGraphicsShader;
	g_pShader->CreateVertexShader(L"shader\\test.fx", "VS_Test"); // ( CreateInputLayout 함수내 존재 )
	g_pShader->CreatePixelShader(L"shader\\test.fx", "PS_Test");

 }

void TestUpdate()
{
	// 왼쪽 키를 누르고 있다면 
	if (KEY_PRESSED(KEY::LEFT))
	{
		g_vPos.x -= DT * 0.5f;
	}


	// 왼쪽 키를 누르고 있다면 
	if (KEY_PRESSED(KEY::RIGHT))
	{
		g_vPos.x += DT * 0.5f;
	}

	g_pCB->SetData(&g_vPos, sizeof(Vec4));

}

void TestRender()
{
	CDevice::GetInst()->ClearTarget();

	// 상수 버퍼가 Vertex Shader 시점에 온다.
	// ( 전달된 상수 값이 Object 의 위치가 된다. 

	// render 
	// IA 전달 -- 아래 CONTEXT 함수 호출 순서는 상관이없다. 그냥 저렇게 설정을 한것이지 수행을 하는 것이 아니기 때문 
	g_pShader->UpdateData();
	g_pCB->UpdateData(); // 레지스터에 전달
	//CONTEXT->Draw(6, 0); // OffSet 으로 부터 얼마나 출력할 것인지를 알린다. 
	g_pMesh->render();

	CDevice::GetInst()->Present();

}

void TestRelease()
{
	SAFE_DELETE(g_pMesh);
	SAFE_DELETE(g_pShader);
	SAFE_DELETE(g_pCB);


}
