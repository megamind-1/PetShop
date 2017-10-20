//Pet.h			宠物类
#include<string>
#include<windows.h>
#include<iostream>
#include<fstream>

using namespace std;

class Pet											//宠物类
{
public:
	Pet(string type,double price,int num)
	{
		this->type = type;
		this->price = price;
		this->num = num;
	}
	string getType()								//返回宠物类型
	{
		return type;
	}
	double getPrice()								//返回宠物价格
	{
		return price;
	}
	int getNum()									//返回宠物数量
	{
		return num;
	}
	void setNum(int num)							//设置数量
	{
		this->num -= num;
	}
	void show()										//显示信息
	{
		cout << "宠物类型:" << type << endl;
		cout << "价格:    " << price << endl;
		cout << "剩余数量:" << num << endl;
	}
private:
	string type;									//类型
	double price;									//价格
	int num;										//数量
};
