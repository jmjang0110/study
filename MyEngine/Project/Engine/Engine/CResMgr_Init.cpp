#include "pch.h"
#include "CResMgr.h"

void CResMgr::init()
{
	CreateEngineMesh();
	CreateEngineTexture();
	CreateEngineShader();
	CreateEngineMaterial();

}

void CResMgr::CreateEngineMesh()
{
	CMesh* pMesh = nullptr;
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;

	Vtx v;


	// RectMesh
	// 0 --- 1
	// |  \  |
	// 3 --- 2

	// 지역 변수들 
	// RectMesh
	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);


	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(2.f, 0.f);

	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUV = Vec2(2.f, 2.f);

	vecVtx.push_back(v);


	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 2.f);

	vecVtx.push_back(v);


	vecIdx.push_back(0); vecIdx.push_back(2); vecIdx.push_back(3);
	vecIdx.push_back(0); vecIdx.push_back(1); vecIdx.push_back(2);
	
	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(),(UINT)vecIdx.size());
	AddRes<CMesh>(L"RectMesh", pMesh);

	vecVtx.clear();
	vecIdx.clear();

	// CIrcke Mesh
	// cube
	// sphere
	// Cylinder
	// Frustum

}

void CResMgr::CreateEngineTexture()
{
}

void CResMgr::CreateEngineShader()
{

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

	MakeInputLayoutInfo();

	CGraphicsShader* pShader = nullptr;

	// Test
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\test.fx", "VS_Test"); // ( CreateInputLayout 함수내 존재 )
	pShader->CreatePixelShader(L"shader\\test.fx", "PS_Test");
	pShader->SetRSType(RS_TYPE::CULL_BACK);

	// SCALAR_PARAM::INT_0 가 빨간색인지의 여부인지에 대한 Info 정보
	pShader->AddScalarParamInfo(L"IsColorRed", SCALAR_PARAM::INT_0); 
	pShader->AddtexParamInfo(L"OutputTex", TEX_PARAM::TEX_0);
	

	AddRes<CGraphicsShader>(L"TestShader", pShader);

}

void CResMgr::CreateEngineMaterial()
{
	CMaterial* pMtrl = nullptr;

	// TestMtrl 생성 
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindRes<CGraphicsShader>(L"TestShader"));

	AddRes<CMaterial>(L"TestMtrl", pMtrl);

	}

void CResMgr::MakeInputLayoutInfo()
{
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

	tInputDesc.SemanticName = "TEXCOORD";
	tInputDesc.SemanticIndex = 0;
	tInputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tInputDesc.InstanceDataStepRate = 0;
	tInputDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
	tInputDesc.AlignedByteOffset = iOffset;
	iOffset += 8;


	CGraphicsShader::AddInputLayout(tInputDesc);


}
