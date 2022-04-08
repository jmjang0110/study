#pragma once


#define SINGLE(TYPE) friend class CSingleton<TYPE>; \
					 private:\
						TYPE();\
						~TYPE();\

//#define SINGLE(TYPE) private:	\
//	TYPE();						\
//	~TYPE();					\
//public:							\
//	static TYPE* GetInst()		\
//	{							\
//		static TYPE mgr;		\
//		return &mgr;			\
//	}							\

#define DT CTimeMgr::GetInst()->GetDT()
#define KEY_TAP(key) KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(key) 
#define KEY_PRESSED(key) KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(key) 
#define KEY_AWAY(key) KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(key) 


#define DEVICE CDevice::GetInst()->GetDevice().Get()
#define CONTEXT CDevice::GetInst()->GetDeviceContext().Get()

#define MAX_LAYER 32

#define SAFE_DELETE(p) if(nullptr != p) delete p; p = nullptr;
#define CLONE_DISABLE(type) virtual type* Clone() { return nullptr; }
#define CLONE(type)virtual type* Clone() { return new type(*this); }



typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;


/*
	delete 순서도 고려했다.
	예를들어 Material 보다 Texture 가 더 빨리 삭제가 된다면 
	Material 이 지워질 때 이미 삭제된 Texture 를 또 삭제할려고 한다
	이미 존재하지 않는 곳에 접근을 할 수 있기 떄문에 crush 날 수 있다. 

*/
enum class RES_TYPE
{
	/*
		참조 우열 순위 
	*/
	PREFAB,
	MESHDATA,
	MATERIAL,
	MESH,
	TEXTURE,
	SOUND,
	GRAPHICS_SHADER,
	COMPUTE_SHADER,
	END,

};



enum class CB_TYPE
{
	TRANSFORM,			// b0 ( 0 번 레지스터에는 위치정보만 전달 ) 
	SCALAR_PARAM,		// b1
	GLOBAL,				// b2
	END,
};

// Rasterizer option
enum class RS_TYPE
{
	CULL_BACK,	// Default
	CULL_FRONT,
	CULL_NONE,
	WIRE_FRAME,
	END,

};

enum class DS_TYPE
{
	LESS,				// 깊이가 가까울 수록 통과 
	LESS_EQUAL,
	
	GREATER,			// 깊이가 멀어질 수록 통과 
	GREATER_EQUAL,
	
	NO_TEST,			// 깊이 테스트 X.		깊이 기록 O 
	NO_WRITE,			// 깊이 테스트 O,		깊이 기록 X  

	NO_TEST_NO_WRITE,	// 깊이 테스트 X,		깊이 기록 X 
	END,


};

enum class COMPONENT_TYPE
{
	TRANSFORM,			// 위치, 크기, 회전 ( Location )
			
	CAMERA,				// 화면을 찍는 카메라 역할 		

	COLLIDER2D,			// 2D 충돌체
	COLLIDER3D,			// 3D 충돌체 
	
	ANIMATOR2D,			// 2D Sprite Animation
	ANIMATOR3D,			// 3D Bone Skinning Animation

	BOUNDINGBOX,		// Picking, FrustumCulling

	// renderer
	MESHRENDER,			// Mesh Renderer
	TILEMAP,			// 2D Tile Map Renderer 
	PARTICLESYSTEM,		// 입자 렌더링	
	LANDSCAPE,			// 지형 
	DECAL,				// 데칼 오브젝트 
	

	// Update
	SCRIPT,				// 로직
	END,
		
};


enum class SCALAR_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,

	MAT_0,
	MAT_1,
	MAT_2,
	MAT_3,

	END,


};
enum class TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,

	TEX_CUBE_0,
	TEX_CUBE_1,

	TEX_ARR_0,
	TEX_ARR_1,

	END,

};

enum class PIPELINE_STAGE
{
	VS = 0x01, // Vertex
	HS = 0x02, // Hull
	DS = 0x04, // Domain
	GS = 0x08, // Geometry
	PS = 0x10, // Pixel
	

	NO_PS = VS | HS | DS | GS,
	ALL = VS | HS | DS | GS | PS,



};


enum class EVENT_TYPE
{
	CREATE_OBJ,			// lParam : Object Adress, wParam : Layer Index
	DELETE_OBJ,			// lParam : Object Adress
	ADD_CHILD,			// lParam : Parent Object Adress, wParam : child Object
	
	STAGE_CHANGE,		// lParam : Next Stage Enum
	CHANGE_AI_STATE,	// lParam : FSM Adress, wParam : Next State Type

	END,
};

