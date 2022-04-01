#pragma once


struct Vertex
{

	Vec3 vPos;		// 좌표
	Vec4 vColor;	// 색상 
	Vec2 vUV;		// 텍스쳐

};

typedef Vertex Vtx;


// ====================
// 상수버퍼 대응 구조체 
// ====================
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;

};

struct tScalarParam
{

	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matArr[4];


};