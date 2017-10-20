//Controler.h		控制类
#include"Customer.h"

int selCustomer(string id);							//在数据中寻找要操作的值
void findCustomer();								//查找
void modCustomer();									//修改
void delCustomer();									//删除
void showCustomers();								//用户列表
void getCustomers();								//获取用户
void saveCustomer(Customer *c);						//存数据
void saveCustomers();								//保存修改

void addPet();										//添加宠物
void getPets();										//获取宠物
void savePet(Pet *p);								//存数据
void savePets();
void showPets();

Customer * c[100];									//顾客对象指针数组
int cNum;											//记录用户数量
Pet * p[100];										//宠物对象指针数组
int pNum;											//记录宠物数量
int i;												//循环变量

string adminPassword = "root";						//管理员密码

void controlMenu()									//管理模式主菜单
{
	getCustomers();
	string p;
	cout << "请输入管理员密码(密码为'root')" << endl;
	cin >> p;
	if(p!=adminPassword)
	{
		cout << "密码错误!!" << endl;
		return;
	}
	system("cls");
	cout << "欢迎来到管理模式" << endl;
	Sleep(1000);
	int flag = 1;
	do
	{
		cout << "+------------------------------+" << endl;
		cout << "+        管理模式              +" << endl;
		cout << "+                              +" << endl;
		cout << "+        请选择:               +" << endl;
		cout << "+        1:查找用户            +" << endl;
		cout << "+        2:修改用户            +" << endl;
		cout << "+        3:删除用户            +" << endl;
		cout << "+        4:用户列表            +" << endl;
		cout << "+        5:添加宠物            +" << endl;
		cout << "+        0:退出管理模式        +" << endl;
		cout << "+------------------------------+" << endl << endl;
		cout << "请输入:" <<endl;
		int s;
		cin >> s;
		system("cls");
		switch(s)
		{
		case 1:
			findCustomer();							//查找
			break;
		case 2:
			modCustomer();							//修改
			break;
		case 3:
			delCustomer();							//删除
			break;
		case 4:
			showCustomers();						//用户列表
			break;
		case 5:
			addPet();								//添加宠物
			break;
		case 0:
			flag = 0;								//返回上一级
			system("cls");
			break;
		default:
			cout << "输入有误,请重新输入." << endl;
			break;
		}

	} while(flag);
}

void findCustomer()									//查找
{
	getCustomers();
	string id;
	cout << "请输入要查找的用户名" << endl;
	cin >> id;
	int x = selCustomer(id);
	if(x!=-1)
	{
		cout << "已找到" << endl;
		c[x]->show();
	}
	else
	{
		cout << "未找到id为" << id << "的用户!" << endl;
	}
}

void modCustomer()									//修改
{
	getCustomers();
	showCustomers();
	string id;
	cout << "请输入要修改的用户名" << endl;
	cin >> id;
	int x = selCustomer(id);
	if(x!=-1)
	{
		string password;
		string name;
		int level;
		cout << "请输入修改后的密码,原密码为:" << c[x]->getCustomerPassword() << endl;
		cin >> password;
		c[x]->setCustomerPassword(password);
		cout << "请输入修改后的姓名,原姓名为:" << c[x]->getCustomerName() << endl;
		cin >> name;
		c[x]->setCustomerName(name);
		cout << "请输入修改后的等级,原等级为:" << c[x]->getCustomerLevel() << endl;
		cin >> level;
		c[x]->setCustomerLevel(level);
		saveCustomers();
		cout << "修改完成!" << endl;
		c[x]->show();
	}
	else
	{
		cout << "未找到id为" << id << "的用户!" << endl;
	}
}

void delCustomer()									//删除
{
	getCustomers();
	showCustomers();
	string id;
	cout << "请输入要删除的用户名" << endl;
	cin >> id;
	int x = selCustomer(id);
	if(x!=-1)
	{
		c[x] = NULL;
		cout << "已删除!" << endl;
		saveCustomers();
	}
	else
	{
		cout << "未找到id为" << id << "的用户!" << endl;
	}
}

int selCustomer(string id)							//寻找操作的客户对象
{
	for(i=0; i<cNum; i++)
	{
		if(id == c[i]->getCustomerID())
		{
			//c[i]->show();
			return i;								//返回下标
			break;
		}
	}
	return -1;										//未查找到返回-1
}

void saveCustomers()								//存储对象数组
{
	ofstream fout("customer.txt",ios::trunc);
	fout.close();
	for(i=0; i<cNum; i++)
	{
		if(c[i]!=NULL)
		{
			saveCustomer(c[i]);
		}
	}
}

void saveCustomer(Customer *c)						//存储单个用户
{
	ofstream fout("Customer.txt",ios::app);
	fout << endl;
	fout << c->getCustomerID() << endl;
	fout << c->getCustomerPassword() << endl;
	fout << c->getCustomerName() << endl;
	fout << c->getCustomerLevel();
	fout.close();
}

void getCustomers()									//获取用户
{
	fstream fin;
	fin.open("customer.txt",ios::in);
	if(!fin)
	{
		return;
	}
	cNum = 0;
	while(!fin.eof())
	{
		string id;
		string password;
		string name;
		int level;
		fin >> id;
		fin >> password;
		fin >> name;
		fin >> level;
		if(level == 0)
		{
			c[cNum++] = new normalCustomer(id,password,name);
		}
		else
		{
			c[cNum++] = new memberCustomer(id,password,name,level);
		}
	}
	fin.close();
}

void showCustomers()								//用户列表
{
	getCustomers();
	cout << "共有" << cNum << "个用户" << endl;
	cout << "登录名\t密码\t姓名\t会员等级" << endl << endl;
	for(i=0; i<cNum; i++)
	{
		cout << c[i]->getCustomerID() << "\t";
		cout << c[i]->getCustomerPassword() << "\t";
		cout << c[i]->getCustomerName() << "\t";
		cout << c[i]->getCustomerLevel() << endl;
	}
}

void addPet()										//添加宠物
{
	string type;
	int num;
	double price;
	int flag;
	do
	{
		flag = 0;
		cout << "请输入宠物类型" << endl;
		cin >> type;
		for(i=0; i<pNum; i++)
		{
			if(type==p[i]->getType())
			{
				flag = 1;
				cout << "此宠物已存在,请重新输入!" << endl;
			}
		}
	}while(flag);
	do
	{
		flag = 0;
		cout << "请输入宠物价格" << endl;
		cin >> price;
		if(price<0)
		{
			flag = 1;
			cout << "输入有误,请输入大于等于0的数!" << endl;
		}
	}while(flag);
	do
	{
		flag = 0;
		cout << "请输入宠物数量" << endl;
		cin >> num;
		if(num<0)
		{
			flag = 1;
			cout << "输入有误,请输入大于等于0的整数!" << endl;
		}
	}while(flag);
	savePet(new Pet(type,price,num));
}

void showPets()										//展示宠物信息
{
	getPets();
	cout << "共计" << pNum << "种宠物" << endl;
	cout << "种类\t价格\t剩余数量" << endl;
	for(i=0; i<pNum; i++)
	{
		cout << p[i]->getType() << "\t";
		cout << p[i]->getPrice() << "\t";
		cout << p[i]->getNum() << endl;
	}
}

void getPets()										//获取宠物
{
	fstream fin;
	fin.open("pet.txt",ios::in);
	if(!fin)
	{
		return;
	}
	pNum = 0;
	while(!fin.eof())
	{
		string type;
		int num;
		double price;
		fin >> type;
		fin >> price;
		fin >> num;
		p[pNum++] = new Pet(type,price,num);
	}
	fin.close();
}

void savePets()										//存储所有宠物
{
	ofstream fout("pet.txt",ios::trunc);
	fout.close();
	for(i=0; i<pNum; i++)
	{
		savePet(p[i]);
	}
}

void savePet(Pet *p)								//存储宠物
{
	ofstream fout("pet.txt",ios::app);
	fout << endl;
	fout << p->getType() << endl;
	fout << p->getPrice() << endl;
	fout << p->getNum();
	fout.close();
}