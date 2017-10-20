//主函数
#include "Controler.h"

void menu();											//主菜单
void newCustomer();										//新建用户
void login();											//登录
void quit();											//退出
void petSale();											//宠物售卖
void getPay();											//结账

Customer * cNow;										//当前用户指针

int main()												//主函数
{
	getCustomers();
	getPets();
	while(true)
	{
		menu();											//循环主菜单
	}
	return 0;
}

void menu()												//菜单
{
	cout << "+------------------------------+" << endl;
	cout << "+   欢迎来到只卖宠物的宠物店   +" << endl;
	cout << "+                              +" << endl;
	cout << "+        请选择:               +" << endl;
	cout << "+        1:用户注册            +" << endl;
	cout << "+        2:用户登录            +" << endl;
	cout << "+        3:购买宠物            +" << endl;
	cout << "+        4:结账                +" << endl;
	cout << "+        5:管理宠物店          +" << endl;
	cout << "+        0:退出                +" << endl;
	cout << "+------------------------------+" << endl << endl;
	cout << "请输入:" <<endl;
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
		cout << "输入有误,请重新输入." << endl;
		break;
	}
}

void newCustomer()										//新建用户
{
	string id;
	string name;
	string password;
	int level;
	int flag;
	do
	{
		flag = 0;
		cout << "请输入您的登录名" << endl;
		cin >> id;
		for(i=0; i<cNum; i++)
		{
			if(id==c[i]->getCustomerID())
			{
				flag = 1;
				cout << "此用户名已存在,请重新输入" << endl;
			}
		}
	}while(flag);
	cout << "请输入您的密码" << endl;
	cin >> password;
	cout << "请输入您的姓名" << endl;
	cin >> name;
	do
	{
		cout << "请问您办理几级会员,请输入0-5 (0表示非会员)" << endl;
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
			cout << "输入有误,请重新输入" << endl;
		}
	} while(true);
}

void login()											//登录
{
	getCustomers();
	int flag=0;
	do
	{
		string id;
		string password;
		cout << "请输入您的登录名" << endl;
		cin >> id;
		cout << "请输入您的密码" << endl;
		cin >> password;
		for(i=0; i<cNum; i++)
		{
			if(id==c[i]->getCustomerID() && password==c[i]->getCustomerPassword())
			{
				flag = 1;
				cout << "登录成功" << endl << endl;
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
			cout << "用户不存在或密码错误,请重新输入!" << endl<<endl;
		}
	} while(!flag);
}

void petSale()											//宠物售卖
{
	if(cNow!=NULL)
	{
		getPets();
		int index;										//记录选中的宠物下标
		int flag = 0;
		showPets();
		string type;
		cout << "请输入要购买的宠物种类:" << endl;
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
			cout << "不存在该类宠物!" << endl;
			return ;
		}
		flag = 0;
		do
		{
			cout << "请输入要购买的数量:" << endl;
			int num;
			cin >> num;
			if(num > p[index]->getNum())
			{
				cout << "剩余量不足,请重新输入!" << endl;
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
		cout << "请先登录!" << endl;
	}
}

void getPay()											//结账
{
	if(cNow!=NULL)
	{
		cout << "您一共消费" << cNow->getCost() << "元!" << endl;
		quit();
	}
	else
	{
		cout << "请先登录!" << endl;
	}
}

void quit()												//退出
{
	cout << "拜拜,欢迎您下次使用" << endl;
	system("pause");
	exit(0);
}