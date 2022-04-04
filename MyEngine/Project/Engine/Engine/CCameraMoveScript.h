#pragma once
#include "CScript.h"


class CCameraMoveScript
	: public CScript
{
private:
	float m_fCamSpeed;

public:
	virtual void update();

	CLONE(CCameraMoveScript);


public:
	CCameraMoveScript();
	~CCameraMoveScript();

};

