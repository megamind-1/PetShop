//Customer.h		顾客类
#include"Pet.h"

class Customer											//顾客基类
{
public:
	string getCustomerID()								//返回顾客id
	{
		return customerID;
	}
	string getCustomerPassword()						//返回顾客密码
	{
		return customerPassword;
	}
	string getCustomerName()							//返回顾客姓名
	{
		return customerName;
	}
	int getCustomerLevel()								//返回顾客等级
	{
		return customerLevel;
	}
	void setCustomerLevel(int level)					//设置顾客等级,最高为5
	{
		if(level>=0 && level<=5)
		{
			customerLevel = level;
		}
		else
		{
			cout << "设置失败,只能设置(0-5)" << endl;
		}
	}
	void setCustomerPassword(string password)			//修改密码
	{
		customerPassword = password;
	}
	void setCustomerName(string name)					//修改姓名
	{
		customerName = name;
	}
	double getCost()									//获取消费金额
	{
		return cost;
	}
	void show()											//显示信息
	{
		cout << "欢迎您,"<< customerName << "\t";
		if(customerLevel != 0)
		{
			cout << "尊贵的"<< customerLevel << "级会员";
		}
		cout << endl;
		cout << "您的登录名是:" << customerID << endl;
		cout << "您的密码是:" << customerPassword << endl;
		cout << "请牢记您的密码" << endl << endl;
	}
	virtual void setCost(Pet *p) = 0;					//算账
protected:
	string customerName;								//顾客姓名
	string customerID;									//顾客用户名
	string customerPassword;							//顾客编号
	int customerLevel;									//顾客等级
	double cost;										//消费
};

class normalCustomer:public Customer					//普通顾客
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
	void setCost(Pet *p)								//普通顾客不打折
	{
		cost += p->getPrice();
	}
};

class memberCustomer:public Customer					//会员顾客
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
	void setCost(Pet *p)								//打折优惠,每高一级多打一折
	{
		cost += p->getPrice() * (1 - customerLevel * 0.1);
	}
};
