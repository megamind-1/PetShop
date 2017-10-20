//������
#include "Controler.h"

void menu();											//���˵�
void newCustomer();										//�½��û�
void login();											//��¼
void quit();											//�˳�
void petSale();											//��������
void getPay();											//����

Customer * cNow;										//��ǰ�û�ָ��

int main()												//������
{
	getCustomers();
	getPets();
	while(true)
	{
		menu();											//ѭ�����˵�
	}
	return 0;
}

void menu()												//�˵�
{
	cout << "+------------------------------+" << endl;
	cout << "+   ��ӭ����ֻ������ĳ����   +" << endl;
	cout << "+                              +" << endl;
	cout << "+        ��ѡ��:               +" << endl;
	cout << "+        1:�û�ע��            +" << endl;
	cout << "+        2:�û���¼            +" << endl;
	cout << "+        3:�������            +" << endl;
	cout << "+        4:����                +" << endl;
	cout << "+        5:��������          +" << endl;
	cout << "+        0:�˳�                +" << endl;
	cout << "+------------------------------+" << endl << endl;
	cout << "������:" <<endl;
	int m;
	cin >> m;
	system("cls");
	switch(m)
	{
	case 1:
		newCustomer();
		break;
	case 2:
		login();
		break;
	case 3:
		petSale();
		break;
	case 4:
		getPay();
		break;
	case 5:
		controlMenu();
		break;
	case 0:
		quit();
		break;
	default:
		cout << "��������,����������." << endl;
		break;
	}
}

void newCustomer()										//�½��û�
{
	string id;
	string name;
	string password;
	int level;
	int flag;
	do
	{
		flag = 0;
		cout << "���������ĵ�¼��" << endl;
		cin >> id;
		for(i=0; i<cNum; i++)
		{
			if(id==c[i]->getCustomerID())
			{
				flag = 1;
				cout << "���û����Ѵ���,����������" << endl;
			}
		}
	}while(flag);
	cout << "��������������" << endl;
	cin >> password;
	cout << "��������������" << endl;
	cin >> name;
	do
	{
		cout << "��������������Ա,������0-5 (0��ʾ�ǻ�Ա)" << endl;
		cin >> level;
		if(level == 0)
		{
			cNow = new normalCustomer(id,password,name);
			cNow->show();
			saveCustomer(cNow);
			break;
		}
		else if(level>0 && level<6)
		{
			cNow = new memberCustomer(id,password,name,level);
			cNow->show();
			saveCustomer(cNow);
			break;
		}
		else
		{
			cout << "��������,����������" << endl;
		}
	} while(true);
}

void login()											//��¼
{
	getCustomers();
	int flag=0;
	do
	{
		string id;
		string password;
		cout << "���������ĵ�¼��" << endl;
		cin >> id;
		cout << "��������������" << endl;
		cin >> password;
		for(i=0; i<cNum; i++)
		{
			if(id==c[i]->getCustomerID() && password==c[i]->getCustomerPassword())
			{
				flag = 1;
				cout << "��¼�ɹ�" << endl << endl;
				cNow = c[i];
				cNow->show();
				break;
			}
		}
		if(flag)
		{
			break;
		}
		else
		{
			cout << "�û������ڻ��������,����������!" << endl<<endl;
		}
	} while(!flag);
}

void petSale()											//��������
{
	if(cNow!=NULL)
	{
		getPets();
		int index;										//��¼ѡ�еĳ����±�
		int flag = 0;
		showPets();
		string type;
		cout << "������Ҫ����ĳ�������:" << endl;
		cin >> type;
		for(i=0; i<pNum; i++)
		{
			if(p[i]->getType() == type)
			{
				flag = 1;
				index = i;
				break;
			}
		}
		if(!flag)
		{
			cout << "�����ڸ������!" << endl;
			return ;
		}
		flag = 0;
		do
		{
			cout << "������Ҫ���������:" << endl;
			int num;
			cin >> num;
			if(num > p[index]->getNum())
			{
				cout << "ʣ��������,����������!" << endl;
			}
			else
			{
				flag = 1;
				p[index]->setNum(num);
				while(num--)
				{
					cNow->setCost(p[index]);
				}
			}
		}while(!flag);
		savePets();
	}
	else
	{
		cout << "���ȵ�¼!" << endl;
	}
}

void getPay()											//����
{
	if(cNow!=NULL)
	{
		cout << "��һ������" << cNow->getCost() << "Ԫ!" << endl;
		quit();
	}
	else
	{
		cout << "���ȵ�¼!" << endl;
	}
}

void quit()												//�˳�
{
	cout << "�ݰ�,��ӭ���´�ʹ��" << endl;
	system("pause");
	exit(0);
}