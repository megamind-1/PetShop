//Pet.h			������
#include<string>
#include<windows.h>
#include<iostream>
#include<fstream>

using namespace std;

class Pet											//������
{
public:
	Pet(string type,double price,int num)
	{
		this->type = type;
		this->price = price;
		this->num = num;
	}
	string getType()								//���س�������
	{
		return type;
	}
	double getPrice()								//���س���۸�
	{
		return price;
	}
	int getNum()									//���س�������
	{
		return num;
	}
	void setNum(int num)							//��������
	{
		this->num -= num;
	}
	void show()										//��ʾ��Ϣ
	{
		cout << "��������:" << type << endl;
		cout << "�۸�:    " << price << endl;
		cout << "ʣ������:" << num << endl;
	}
private:
	string type;									//����
	double price;									//�۸�
	int num;										//����
};
