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

	// ���� ������ 
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

	MakeInputLayoutInfo();

	CGraphicsShader* pShader = nullptr;

	// Test
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\test.fx", "VS_Test"); // ( CreateInputLayout �Լ��� ���� )
	pShader->CreatePixelShader(L"shader\\test.fx", "PS_Test");
	pShader->SetRSType(RS_TYPE::CULL_BACK);

	// SCALAR_PARAM::INT_0 �� ������������ ���������� ���� Info ����
	pShader->AddScalarParamInfo(L"IsColorRed", SCALAR_PARAM::INT_0); 
	pShader->AddtexParamInfo(L"OutputTex", TEX_PARAM::TEX_0);
	

	AddRes<CGraphicsShader>(L"TestShader", pShader);

}

void CResMgr::CreateEngineMaterial()
{
	CMaterial* pMtrl = nullptr;

	// TestMtrl ���� 
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindRes<CGraphicsShader>(L"TestShader"));

	AddRes<CMaterial>(L"TestMtrl", pMtrl);

	}

void CResMgr::MakeInputLayoutInfo()
{
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

	tInputDesc.SemanticName = "TEXCOORD";
	tInputDesc.SemanticIndex = 0;
	tInputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tInputDesc.InstanceDataStepRate = 0;
	tInputDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
	tInputDesc.AlignedByteOffset = iOffset;
	iOffset += 8;


	CGraphicsShader::AddInputLayout(tInputDesc);


}
