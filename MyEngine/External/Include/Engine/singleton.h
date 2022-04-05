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
			�Լ� �����͸� ������ �޴µ�
			main �Լ� ���� �ɶ� atexit() �Լ����� stack ������ ȣ���Ѵ�. 

			���� ������� �̱��� ��ü���� delete �� �� 
			������ ���� ������� ��ü���� ���ʴ�� 
			���־� �ϹǷ� atexit() ��� - 4-1[ȭ](2) _ 13�� 
		*/
		
		atexit((DESTROY)CSingleton<T>::Destroy);


	}

	virtual ~CSingleton()
	{

	}


};


template<typename T>
T* CSingleton<T>::m_Inst = nullptr;

