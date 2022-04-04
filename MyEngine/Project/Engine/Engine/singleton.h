#pragma once



template<typename T>
class CSingleton
{
	typedef void(*DESTROY)(void);


private:
	static T* m_Inst;



public:
	static T* GetInst()
	{
		if (nullptr == m_Inst)
		{
			m_Inst = new T;
		}

		return m_Inst;

	}

	static void Destroy()
	{
		if (nullptr != m_Inst)
		{
			delete m_Inst;
			m_Inst = nullptr;
		}
	}


public:
	CSingleton()
	{
		/*
			함수 포인터를 전달을 받는데
			main 함수 종료 될때 atexit() 함수들을 stack 구조로 호출한다. 

		*/
		
		atexit((DESTROY)CSingleton<T>::Destroy);  


	}

	~CSingleton()
	{

	}


};


template<typename T>
T* CSingleton<T>::m_Inst = nullptr;

