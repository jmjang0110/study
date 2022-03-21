#include "pch.h"
#include "Temp.h"

#include "CDevice.h"

void TestInit()
{


}

void TestUpdate()
{


}

void TestRender()
{
	CDevice::GetInst()->ClearTarget();

	// render 

	CDevice::GetInst()->Present();


}
