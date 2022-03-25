#pragma once

#include <wrl/client.h>
using namespace Microsoft::WRL;

// 수학 관련 헤더 
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>

using namespace::DirectX;
using namespace::DirectX::PackedVector;

//#pragma comment 에서 .lib 생략 가능하다.
#pragma comment(lib, "d3d11") // d3d11.lib
#pragma comment(lib,"d3dcompiler")
#pragma comment(lib, "dxguid")

#include "SimpleMath.h"
using namespace DirectX::SimpleMath;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <map>
using std::map;
using std::make_pair;

#include <string>
using std::string;
using std::wstring;

#include <assert.h>



#include "define.h"
#include "struct.h"
#include "func.h"
