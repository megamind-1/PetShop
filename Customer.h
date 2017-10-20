//Customer.h		�˿���
#include"Pet.h"

class Customer											//�˿ͻ���
{
public:
	string getCustomerID()								//���ع˿�id
	{
		return customerID;
	}
	string getCustomerPassword()						//���ع˿�����
	{
		return customerPassword;
	}
	string getCustomerName()							//���ع˿�����
	{
		return customerName;
	}
	int getCustomerLevel()								//���ع˿͵ȼ�
	{
		return customerLevel;
	}
	void setCustomerLevel(int level)					//���ù˿͵ȼ�,���Ϊ5
	{
		if(level>=0 && level<=5)
		{
			customerLevel = level;
		}
		else
		{
			cout << "����ʧ��,ֻ������(0-5)" << endl;
		}
	}
	void setCustomerPassword(string password)			//�޸�����
	{
		customerPassword = password;
	}
	void setCustomerName(string name)					//�޸�����
	{
		customerName = name;
	}
	double getCost()									//��ȡ���ѽ��
	{
		return cost;
	}
	void show()											//��ʾ��Ϣ
	{
		cout << "��ӭ��,"<< customerName << "\t";
		if(customerLevel != 0)
		{
			cout << "����"<< customerLevel << "����Ա";
		}
		cout << endl;
		cout << "���ĵ�¼����:" << customerID << endl;
		cout << "����������:" << customerPassword << endl;
		cout << "���μ���������" << endl << endl;
	}
	virtual void setCost(Pet *p) = 0;					//����
protected:
	string customerName;								//�˿�����
	string customerID;									//�˿��û���
	string customerPassword;							//�˿ͱ��
	int customerLevel;									//�˿͵ȼ�
	double cost;										//����
};

class normalCustomer:public Customer					//��ͨ�˿�
{
public:
	normalCustomer(string ID,string password,string name)
	{
		customerLevel = 0;
		customerID = ID;
		customerPassword = password;
		customerName = name;
		cost = 0;
	}
	void setCost(Pet *p)								//��ͨ�˿Ͳ�����
	{
		cost += p->getPrice();
	}
};

class memberCustomer:public Customer					//��Ա�˿�
{
public:
	memberCustomer(string ID,string password,string name,int level)
	{
		customerID = ID;
		customerPassword = password;
		customerName = name;
		customerLevel = level;
		cost = 0;
	}
	void setCost(Pet *p)								//�����Ż�,ÿ��һ�����һ��
	{
		cost += p->getPrice() * (1 - customerLevel * 0.1);
	}
};
