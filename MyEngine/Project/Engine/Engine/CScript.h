#pragma once
#include "CComponent.h"
class CScript :
    public CComponent
{

private:
    const int m_iScriptID; // ��ũ��Ʈ �����뵵 ( ��ũ��Ʈ Ÿ�� )

public:
    virtual void start() {};
    virtual void update() {};
    virtual void lateupdate() {};
    virtual void finalupdate() final{}; // final : ���̻� �ڽĿ��� �Ļ���Ű�� �ʴ´�. 
                                        // �� ������ ���̻� �����Լ��� ������ �� ����. 
    // �̷��� �� ������ finalupdate : ���� ������Ʈ�� ������ �ε� ������Ʈ �� �ϰ� ���� 
    // ��ũ��Ʈ�� finalupdate �� �� �ع����� �������� ���δ�. 




public:
    CScript();
    ~CScript();


};

