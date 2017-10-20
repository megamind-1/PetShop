//Controler.h		������
#include"Customer.h"

int selCustomer(string id);							//��������Ѱ��Ҫ������ֵ
void findCustomer();								//����
void modCustomer();									//�޸�
void delCustomer();									//ɾ��
void showCustomers();								//�û��б�
void getCustomers();								//��ȡ�û�
void saveCustomer(Customer *c);						//������
void saveCustomers();								//�����޸�

void addPet();										//��ӳ���
void getPets();										//��ȡ����
void savePet(Pet *p);								//������
void savePets();
void showPets();

Customer * c[100];									//�˿Ͷ���ָ������
int cNum;											//��¼�û�����
Pet * p[100];										//�������ָ������
int pNum;											//��¼��������
int i;												//ѭ������

string adminPassword = "root";						//����Ա����

void controlMenu()									//����ģʽ���˵�
{
	getCustomers();
	string p;
	cout << "���������Ա����(����Ϊ'root')" << endl;
	cin >> p;
	if(p!=adminPassword)
	{
		cout << "�������!!" << endl;
		return;
	}
	system("cls");
	cout << "��ӭ��������ģʽ" << endl;
	Sleep(1000);
	int flag = 1;
	do
	{
		cout << "+------------------------------+" << endl;
		cout << "+        ����ģʽ              +" << endl;
		cout << "+                              +" << endl;
		cout << "+        ��ѡ��:               +" << endl;
		cout << "+        1:�����û�            +" << endl;
		cout << "+        2:�޸��û�            +" << endl;
		cout << "+        3:ɾ���û�            +" << endl;
		cout << "+        4:�û��б�            +" << endl;
		cout << "+        5:��ӳ���            +" << endl;
		cout << "+        0:�˳�����ģʽ        +" << endl;
		cout << "+------------------------------+" << endl << endl;
		cout << "������:" <<endl;
		int s;
		cin >> s;
		system("cls");
		switch(s)
		{
		case 1:
			findCustomer();							//����
			break;
		case 2:
			modCustomer();							//�޸�
			break;
		case 3:
			delCustomer();							//ɾ��
			break;
		case 4:
			showCustomers();						//�û��б�
			break;
		case 5:
			addPet();								//��ӳ���
			break;
		case 0:
			flag = 0;								//������һ��
			system("cls");
			break;
		default:
			cout << "��������,����������." << endl;
			break;
		}

	} while(flag);
}

void findCustomer()									//����
{
	getCustomers();
	string id;
	cout << "������Ҫ���ҵ��û���" << endl;
	cin >> id;
	int x = selCustomer(id);
	if(x!=-1)
	{
		cout << "���ҵ�" << endl;
		c[x]->show();
	}
	else
	{
		cout << "δ�ҵ�idΪ" << id << "���û�!" << endl;
	}
}

void modCustomer()									//�޸�
{
	getCustomers();
	showCustomers();
	string id;
	cout << "������Ҫ�޸ĵ��û���" << endl;
	cin >> id;
	int x = selCustomer(id);
	if(x!=-1)
	{
		string password;
		string name;
		int level;
		cout << "�������޸ĺ������,ԭ����Ϊ:" << c[x]->getCustomerPassword() << endl;
		cin >> password;
		c[x]->setCustomerPassword(password);
		cout << "�������޸ĺ������,ԭ����Ϊ:" << c[x]->getCustomerName() << endl;
		cin >> name;
		c[x]->setCustomerName(name);
		cout << "�������޸ĺ�ĵȼ�,ԭ�ȼ�Ϊ:" << c[x]->getCustomerLevel() << endl;
		cin >> level;
		c[x]->setCustomerLevel(level);
		saveCustomers();
		cout << "�޸����!" << endl;
		c[x]->show();
	}
	else
	{
		cout << "δ�ҵ�idΪ" << id << "���û�!" << endl;
	}
}

void delCustomer()									//ɾ��
{
	getCustomers();
	showCustomers();
	string id;
	cout << "������Ҫɾ�����û���" << endl;
	cin >> id;
	int x = selCustomer(id);
	if(x!=-1)
	{
		c[x] = NULL;
		cout << "��ɾ��!" << endl;
		saveCustomers();
	}
	else
	{
		cout << "δ�ҵ�idΪ" << id << "���û�!" << endl;
	}
}

int selCustomer(string id)							//Ѱ�Ҳ����Ŀͻ�����
{
	for(i=0; i<cNum; i++)
	{
		if(id == c[i]->getCustomerID())
		{
			//c[i]->show();
			return i;								//�����±�
			break;
		}
	}
	return -1;										//δ���ҵ�����-1
}

void saveCustomers()								//�洢��������
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

void saveCustomer(Customer *c)						//�洢�����û�
{
	ofstream fout("Customer.txt",ios::app);
	fout << endl;
	fout << c->getCustomerID() << endl;
	fout << c->getCustomerPassword() << endl;
	fout << c->getCustomerName() << endl;
	fout << c->getCustomerLevel();
	fout.close();
}

void getCustomers()									//��ȡ�û�
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

void showCustomers()								//�û��б�
{
	getCustomers();
	cout << "����" << cNum << "���û�" << endl;
	cout << "��¼��\t����\t����\t��Ա�ȼ�" << endl << endl;
	for(i=0; i<cNum; i++)
	{
		cout << c[i]->getCustomerID() << "\t";
		cout << c[i]->getCustomerPassword() << "\t";
		cout << c[i]->getCustomerName() << "\t";
		cout << c[i]->getCustomerLevel() << endl;
	}
}

void addPet()										//��ӳ���
{
	string type;
	int num;
	double price;
	int flag;
	do
	{
		flag = 0;
		cout << "�������������" << endl;
		cin >> type;
		for(i=0; i<pNum; i++)
		{
			if(type==p[i]->getType())
			{
				flag = 1;
				cout << "�˳����Ѵ���,����������!" << endl;
			}
		}
	}while(flag);
	do
	{
		flag = 0;
		cout << "���������۸�" << endl;
		cin >> price;
		if(price<0)
		{
			flag = 1;
			cout << "��������,��������ڵ���0����!" << endl;
		}
	}while(flag);
	do
	{
		flag = 0;
		cout << "�������������" << endl;
		cin >> num;
		if(num<0)
		{
			flag = 1;
			cout << "��������,��������ڵ���0������!" << endl;
		}
	}while(flag);
	savePet(new Pet(type,price,num));
}

void showPets()										//չʾ������Ϣ
{
	getPets();
	cout << "����" << pNum << "�ֳ���" << endl;
	cout << "����\t�۸�\tʣ������" << endl;
	for(i=0; i<pNum; i++)
	{
		cout << p[i]->getType() << "\t";
		cout << p[i]->getPrice() << "\t";
		cout << p[i]->getNum() << endl;
	}
}

void getPets()										//��ȡ����
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

void savePets()										//�洢���г���
{
	ofstream fout("pet.txt",ios::trunc);
	fout.close();
	for(i=0; i<pNum; i++)
	{
		savePet(p[i]);
	}
}

void savePet(Pet *p)								//�洢����
{
	ofstream fout("pet.txt",ios::app);
	fout << endl;
	fout << p->getType() << endl;
	fout << p->getPrice() << endl;
	fout << p->getNum();
	fout.close();
}