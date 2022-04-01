#pragma once


struct Vertex
{

	Vec3 vPos;		// ��ǥ
	Vec4 vColor;	// ���� 
	Vec2 vUV;		// �ؽ���

};

typedef Vertex Vtx;


// ====================
// ������� ���� ����ü 
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