#pragma once

 // Resource Smart Pointer class 

template<typename T>
class Ptr
{
private:
	T*			m_pRes;

public:
	T* Get() { return m_pRes; }
	T** GetAddressOf() { return &m_pRes; }

	T* Get() const { return m_pRes; }
	T** GetAddressOf() const{ return &m_pRes; }

public:
	Ptr& operator = (T* _ptr)
	{
		// 기존에 가리키고 있던게 있다면 
		if (nullptr != m_pRes)
			m_pRes->SubRef();

		m_pRes = _ptr;

		if (nullptr != m_pRes)
			m_pRes->AddRef();

		return *this;

	}

	Ptr& operator = (const Ptr<T>& _otherPtr)
	{
		// 기존에 가리키고 있던게 있다면 
		if (nullptr != m_pRes)
			m_pRes->SubRef();

		m_pRes = _otherPtr.m_pRes;

		if (nullptr != _otherPtr.m_pRes)
			m_pRes->AddRef();

		return *this;

	}

	T* operator ->()
	{

		return m_pRes;
	}

	bool operator == (T* _pRes)
	{
		if (m_pRes == _pRes)
			return true;
		else
			return false;

	}

	bool operator != (T* _pRes)
	{
		// 결과만 뒤집는다. 
		return !(*this == _pRes);


	}


	bool operator == (const Ptr<T>& _OtherPtr)
	{
		if (m_pRes == _OtherPtr.m_pRes)
			return true;
		else
			return false;
		
	}

	bool operator != (const Ptr<T>& _OtherPtr)
	{
		// 결과만 뒤집는다. 
		return !(*this == _OtherPtr);


	}

	//operator T*()
	//{
	//	return m_pRes;

	//}


public:
	Ptr()
		: m_pRes(nullptr)
	
	{}

	Ptr(T* _pRes)
		: m_pRes(_pRes)
	{
		// Resource 가 누군가에 의해서 
		// 가리켜 진거니까 RefCount 를 증가시킨다. 
		if (nullptr != m_pRes)
			m_pRes->AddRef();
	}

	Ptr(const Ptr<T>& _OtherPtr)
		:	m_pRes(_OtherPtr.m_pRes)
	{
		if (nullptr != m_pRes)
			m_pRes->AddRef();
	}
	~Ptr()
	{
		if (nullptr != m_pRes)
		{
			m_pRes->SubRef();

		}
	}

};

template<typename T>
bool operator == (void* _pRes, const Ptr<T>& _ptr)
{
	if (_pRes == _ptr.Get())
		return true;

	return false;

}

template<typename T>
bool operator != (void* _pRes, const Ptr<T>& _ptr)
{
	if (_pRes == _ptr.Get())
		return false;

	return true;

}
