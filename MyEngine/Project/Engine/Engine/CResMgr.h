#pragma once

#include "Ptr.h"

#include "CMaterial.h"
#include "CMesh.h"
//#include "CTexture.h"
#include "CGraphicsShader.h"
//#include "CComputeShader.h"
//#include "CShound.h"

//#include "CMeshData.h"



class CResMgr
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
	Ptr<type> FindRes(const wstring& _strKey);


	template<typename type>
	void AddRes(const wstring& _strKey, type* _pRes);



};

template<typename type>
inline RES_TYPE CResMgr::GetResType()
{
	const type_info& info = typeid(type);

	if (info.hash_code() == typeid(CMesh).hash_code())
		return RES_TYPE::MESH;
	else if (info.hash_code() == typeid(CGraphicsShader).hash_code())
		return RES_TYPE::GRAPHICS_SHADER;
	else if (info.hash_code() == typeid(CMaterial).hash_code())
		return RES_TYPE::MATERIAL;
	/*else if (info.hash_code == typeid(CMesh).hash_code)
		return RES_TYPE::MESH;
	else if (info.hash_code == typeid(CMesh).hash_code)
		return RES_TYPE::MESH;
	else if (info.hash_code == typeid(CMesh).hash_code)
		return RES_TYPE::MESH;*/
	

	return RES_TYPE::END;


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