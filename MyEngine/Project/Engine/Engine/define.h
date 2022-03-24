#pragma once


#define SINGLE(TYPE) private:	\
	TYPE();					\
	~TYPE();					\
public:							\
	static TYPE* GetInst()		\
	{							\
		static TYPE core;		\
		return &core;			\
	}							\

#define DT CTimeMgr::GetInst()->GetDT()
#define KEY_TAP(key) KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(key) 
#define KEY_PRESSED(key) KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(key) 
#define KEY_AWAY(key) KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(key) 


#define DEVICE CDevice::GetInst()->GetDevice().Get()
#define CONTEXT CDevice::GetInst()->GetDeviceContext().Get()

#define SAFE_DELETE(p) if(nullptr != p) delete p; p = nullptr;


typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;

enum class RES_TYPE
{
	MATERIAL,
	MESHDATA,
	MESH,
	TEXTURE,
	SOUND,
	END,

};



enum class CB_TYPE
{
	TRANSFORM, // b0 ( 0 번 레지스터에는 위치정보만 전달 ) 
	MATERIAL_PARAM, // b1
	GLOBAL, // b2
	END,
};