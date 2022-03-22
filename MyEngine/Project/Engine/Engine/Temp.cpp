#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CPathMgr.h"

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

// Vertex
ComPtr<ID3D11Buffer>		g_pVB; 
// 하나의 정점이 어떤 구조로 만들어져 있는가 
ComPtr<ID3D11InputLayout> g_pInputLayout;


// Shader Conpile Error_ Fail Reason store BLob
ComPtr<ID3DBlob>			g_pErrBlob;

// Vertex Shader 
ComPtr<ID3DBlob>			g_pVSBlob;
ComPtr<ID3D11VertexShader>	g_pVS;

// Pixel Shader 
ComPtr<ID3DBlob>			g_pPSBlob;
ComPtr<ID3D11PixelShader>	g_pPS;


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
	Vertex arrVtx[3] = {};
	arrVtx[0].vPos = Vec3(0.f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	arrVtx[1].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[1].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	arrVtx[2].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

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



	// Vertex Shader 컴파일
	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif

	//					[  Vertex Shader Compile  ] 
	wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
	HRESULT hr = D3DCompileFromFile(wstring(strContentPath + L"shader\\test.fx").c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_Test", "vs_5_0", iFlag, 0
		, g_pVSBlob.GetAddressOf(), g_pErrBlob.GetAddressOf()); // (VS_Test)L"" 안붙이고 1byte 로 전달 

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, (char*)g_pErrBlob->GetBufferPointer(), "Vertex Shader Compile Failed!! ", MB_OK);
		assert(nullptr);

	}
	// Compile 된 코드로 Vertex Shader 객체 만들기 
	// Compile 완료된 Vertex Shader 의 시작 주소를 전달 : Blob안에 있음  
	DEVICE->CreateVertexShader(g_pVSBlob->GetBufferPointer(), g_pVSBlob->GetBufferSize(),
		nullptr, g_pVS.GetAddressOf());

	//					[  Pixel Shader Compile  ]
	hr = D3DCompileFromFile(wstring(strContentPath + L"shader\\test.fx").c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_Test"
		, "ps_5_0", iFlag, 0, g_pPSBlob.GetAddressOf()
		, g_pErrBlob.GetAddressOf()); // (VS_Test)L"" 안붙이고 1byte 로 전달 

	

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, (char*)g_pErrBlob->GetBufferPointer(), "Pixel Shader Compile Failed!! ", MB_OK);
		assert(nullptr);

	}
	// Compile 된 코드로 Vertex Shader 객체 만들기 
	// Compile 완료된 Vertex Shader 의 시작 주소를 전달 : Blob안에 있음  
	DEVICE->CreatePixelShader(g_pPSBlob->GetBufferPointer(), g_pPSBlob->GetBufferSize(),
		nullptr, g_pPS.GetAddressOf());
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

	vector<D3D11_INPUT_ELEMENT_DESC> arrDesc;
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


	arrDesc.push_back(tInputDesc);

	tInputDesc.SemanticName = "COLOR";
	tInputDesc.SemanticIndex = 0;
	tInputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tInputDesc.InstanceDataStepRate = 0;
	tInputDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	tInputDesc.AlignedByteOffset = iOffset;
	iOffset += 16;


	arrDesc.push_back(tInputDesc);

	DEVICE->CreateInputLayout(arrDesc.data(), 2
		, g_pVSBlob->GetBufferPointer(), g_pVSBlob->GetBufferSize()
		, g_pInputLayout.GetAddressOf());

}

void TestUpdate()
{


}

void TestRender()
{
	CDevice::GetInst()->ClearTarget();

	// render 
	// IA 전달 -- 아래 CONTEXT 함수 호출 순서는 상관이없다. 그냥 저렇게 설정을 한것이지 수행을 하는 것이 아니기 때문 
	CONTEXT->IASetInputLayout(g_pInputLayout.Get());

	UINT iStride = sizeof(VTX); // 간격 
	UINT iOffset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, g_pVB.GetAddressOf(), &iStride, &iOffset); // 간격과 시작 위치 알림 
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 삼각형 모양이다,. 

	CONTEXT->VSSetShader(g_pVS.Get(), 0, 0); // 이 정점들을 어떤 쉐이더를 사용할 것인지를 선택한다. 
	CONTEXT->PSSetShader(g_pPS.Get(), 0, 0);


	CONTEXT->Draw(3, 0); // OffSet 으로 부터 얼마나 출력할 것인지를 알린다. 


	CDevice::GetInst()->Present();

}
