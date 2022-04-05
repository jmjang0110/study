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

			먼저 만들어진 싱글톤 객체들을 delete 할 떄 
			순서가 먼저 만들어진 객체부터 차례대로 
			없애야 하므로 atexit() 사용 - 4-1[화](2) _ 13분 
		*/
		
		atexit((DESTROY)CSingleton<T>::Destroy);


	}

	virtual ~CSingleton()
	{

	}


};


template<typename T>
T* CSingleton<T>::m_Inst = nullptr;

