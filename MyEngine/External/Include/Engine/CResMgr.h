#pragma once

#include "Ptr.h"

#include "CPathMgr.h"


#include "CMaterial.h"
#include "CMesh.h"
#include "CTexture.h"
#include "CGraphicsShader.h"
#include "CPrefab.h"
//#include "CComputeShader.h"
//#include "CShound.h"

//#include "CMeshData.h"



class CResMgr
	: public CSingleton<CResMgr>
{
	SINGLE(CResMgr);

private:
	map<wstring, class CRes*> m_Res[(UINT)RES_TYPE::END];
	


public:
	void init();

private:
	void CreateEngineMesh();
	void CreateEngineTexture();
	void CreateEngineShader();
	void CreateEngineMaterial();

	void MakeInputLayoutInfo();


public:
	template<typename type>
	RES_TYPE GetResType();

	template<typename type>
	Ptr<type> Load(const wstring& _strKey, const wstring& _strRelativePath);


	template<typename type>
	Ptr<type> FindRes(const wstring& _strKey);


	template<typename type>
	void AddRes(const wstring& _strKey, type* _pRes);



};

template<typename type>
inline RES_TYPE CResMgr::GetResType()
{
	const type_info& info = typeid(type);


	if (info.hash_code() == typeid(CPrefab).hash_code())
		return RES_TYPE::PREFAB;
	else if (info.hash_code() == typeid(CMesh).hash_code())
		return RES_TYPE::MESH;
	else if (info.hash_code() == typeid(CGraphicsShader).hash_code())
		return RES_TYPE::GRAPHICS_SHADER;
	else if (info.hash_code() == typeid(CMaterial).hash_code())
		return RES_TYPE::MATERIAL;
	else if (info.hash_code() == typeid(CTexture).hash_code())
		return RES_TYPE::TEXTURE;

	/*else if (info.hash_code == typeid(CMesh).hash_code)
		return RES_TYPE::MESH;
	else if (info.hash_code == typeid(CMesh).hash_code)
		return RES_TYPE::MESH;*/
	

	return RES_TYPE::END;


}

template<typename type>
Ptr<type> CResMgr::Load(const wstring& _strKey, const wstring& _strRelativePath)
{
	RES_TYPE eType = GetResType<type>();


	// 이미 있으면 반환한다. 
	CRes* pRes = FindRes<type>(_strKey).Get();
	if (nullptr != pRes)
		return Ptr<type>((type*)pRes);
	
	wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
	wstring strFilePath = strContentPath + _strRelativePath;

	pRes = new type;
	if (FAILED(pRes->Load(strFilePath)))
	{
		MessageBox(nullptr, L"Resource Loading Failed!", L"REsource Loading Error", MB_OK);
		return nullptr;
	}

	pRes->SetKey(_strKey);
	pRes->SetRelativePath(_strRelativePath);


	m_Res[(UINT)eType].insert(make_pair(_strKey, pRes));

	return Ptr<type>((type*)pRes);
}



template<typename type>
Ptr<type> CResMgr::FindRes(const wstring& _strKey)
{

	RES_TYPE eType = GetResType<type>();

	map<wstring, CRes*>::iterator iter = m_Res[(UINT)eType].find(_strKey);
	if (iter == m_Res[(UINT)eType].end())
		return nullptr;


	return (type*)iter->second;

}

template<typename type>
void CResMgr::AddRes(const wstring& _strKey, type* _pRes)
{
	RES_TYPE eType = GetResType<type>();

	Ptr<type> pRes = FindRes<type>(_strKey);

	// pRes 가 nullptr가 아니라는 것은 해당 리소스가 이미 들어있다는 것
	assert(nullptr == pRes);


	// Resource 추가 
	m_Res[(UINT)eType].insert(make_pair(_strKey, _pRes));


}