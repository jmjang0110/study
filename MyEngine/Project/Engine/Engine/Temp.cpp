#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CPathMgr.h"

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

// Vertex
ComPtr<ID3D11Buffer>		g_pVB; 
// �ϳ��� ������ � ������ ������� �ִ°� 
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
	Vertex arrVtx[3] = {};
	arrVtx[0].vPos = Vec3(0.f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	arrVtx[1].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[1].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	arrVtx[2].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

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



	// Vertex Shader ������
	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif

	//					[  Vertex Shader Compile  ] 
	wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
	HRESULT hr = D3DCompileFromFile(wstring(strContentPath + L"shader\\test.fx").c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_Test", "vs_5_0", iFlag, 0
		, g_pVSBlob.GetAddressOf(), g_pErrBlob.GetAddressOf()); // (VS_Test)L"" �Ⱥ��̰� 1byte �� ���� 

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, (char*)g_pErrBlob->GetBufferPointer(), "Vertex Shader Compile Failed!! ", MB_OK);
		assert(nullptr);

	}
	// Compile �� �ڵ�� Vertex Shader ��ü ����� 
	// Compile �Ϸ�� Vertex Shader �� ���� �ּҸ� ���� : Blob�ȿ� ����  
	DEVICE->CreateVertexShader(g_pVSBlob->GetBufferPointer(), g_pVSBlob->GetBufferSize(),
		nullptr, g_pVS.GetAddressOf());

	//					[  Pixel Shader Compile  ]
	hr = D3DCompileFromFile(wstring(strContentPath + L"shader\\test.fx").c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_Test"
		, "ps_5_0", iFlag, 0, g_pPSBlob.GetAddressOf()
		, g_pErrBlob.GetAddressOf()); // (VS_Test)L"" �Ⱥ��̰� 1byte �� ���� 

	

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, (char*)g_pErrBlob->GetBufferPointer(), "Pixel Shader Compile Failed!! ", MB_OK);
		assert(nullptr);

	}
	// Compile �� �ڵ�� Vertex Shader ��ü ����� 
	// Compile �Ϸ�� Vertex Shader �� ���� �ּҸ� ���� : Blob�ȿ� ����  
	DEVICE->CreatePixelShader(g_pPSBlob->GetBufferPointer(), g_pPSBlob->GetBufferSize(),
		nullptr, g_pPS.GetAddressOf());
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

	vector<D3D11_INPUT_ELEMENT_DESC> arrDesc;
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
	// IA ���� -- �Ʒ� CONTEXT �Լ� ȣ�� ������ ����̾���. �׳� ������ ������ �Ѱ����� ������ �ϴ� ���� �ƴϱ� ���� 
	CONTEXT->IASetInputLayout(g_pInputLayout.Get());

	UINT iStride = sizeof(VTX); // ���� 
	UINT iOffset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, g_pVB.GetAddressOf(), &iStride, &iOffset); // ���ݰ� ���� ��ġ �˸� 
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �ﰢ�� ����̴�,. 

	CONTEXT->VSSetShader(g_pVS.Get(), 0, 0); // �� �������� � ���̴��� ����� �������� �����Ѵ�. 
	CONTEXT->PSSetShader(g_pPS.Get(), 0, 0);


	CONTEXT->Draw(3, 0); // OffSet ���� ���� �󸶳� ����� �������� �˸���. 


	CDevice::GetInst()->Present();

}
