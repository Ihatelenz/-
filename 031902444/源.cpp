#include<iostream>
#include<fstream>
#include<sstream>
#include<list>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <algorithm>


using namespace std;

class word
{
public:
	string name;	//�洢���д�
	int no;			//���дʺ�
	int flag;		//��Ӣ���������
}mg[200];

class text
{
public:
	string str;		//�洢һ�еĴ�������
	int no;			//�к�
}test[3000];

class ans
{
public:
	int wordno;		//�������дʺ�
	int textno;		//�����к�
	int front;		//���κ�����дʵ���ʼλ��
	int end;		//���κ�����дʵĽ���λ��
}da[3000];


ifstream filew;		//���д������ļ�
ifstream filet;		//�������������ļ�
int wl, tl;			//���д�������������
int dalen = 0;		//������
ofstream out;		//������ļ�



void shuru()										//�����������ݲ������ļ�
{
	int i = 0;
	string str1, str2;
	cin >> str1;
	filew.open(str1);
	if (!filew)										//�����ַ�����ж�
	{
		cout << "error��" << endl;
	}
	while (filew >> str1)
	{
		mg[i].name = str1;
		mg[i].no = i;
		mg[i].flag = mg[i].name[0] > 0 ? 0 : 1;		//�ж����Ļ�Ӣ��
		i++;
	}
	wl = i;
	filew.close();
	i = 0;
	cin >> str2;
	filet.open(str2);
	if (!filet)										//�����ַ�����ж�
	{
		cout << "error��" << endl;
	}
	while (getline(filet, str2))					//һ��һ��¼��text��
	{
		test[i].str = str2;
		test[i].no = i;
		i++;
	}
	tl = i;
	filet.close();
}

void charu(int front, int back, int wn, int tn)		//����𰸣���¼��ans��
{
	da[dalen].textno = tn;
	da[dalen].wordno = wn;
	da[dalen].front = front;
	da[dalen].end = back;
	dalen++;
}

void find(word& W, text& T)							//���Ҷ�Ӧ���дʶ�
{
	int i = 0, j = 0;
	int front = 0, back = 0;
	int sum = 0, l = 0;
	int fei = 0;
	string a;
	string  b;
	if (W.flag == 1)								//����ƥ��
	{
		front = 0;
		back = 0;
		for (; j < T.str.length(); j++)
		{
			a = W.name.substr(i, 3);				//һ�����ı������ֽڣ�ÿ���ֽ�ȡ�����
			b = T.str.substr(j, 3);
			if (a==b)
			{
				if (i == 0)
				{
					front = j;
				}
				i += 3;
				j += 2;
				if (i == W.name.length())			//һ���������д�ƥ�������¼���
				{
					charu(front, j, W.no, T.no);
					i = 0;
				}

			}


		}
	}
	else											//Ӣ��ƥ��
	{
		front = 0;
		back = 0;
		transform(T.str.begin(), T.str.end(), T.str.begin(), ::tolower);			//�����кʹ������дʲ����ִ�Сд��ȫ��ת����Сд
		transform(W.name.begin(), W.name.end(), W.name.begin(), ::tolower);
		for (; j < T.str.length(); j++)
		{
			if (W.name[i] == T.str[j])
			{
				if (i == 0)
				{
					front = j;
				}
				i++;
				if (i == W.name.length())			//һ���������д�ƥ�������¼���
				{
					charu(front, j, W.no, T.no);
					i = 0;
					fei = 0;
				}

			}
			else
				fei++;
			if (fei > 20)							//�����޹��ַ�����20��������ƥ��
				break;

		}
	}
}

void print()
{
	int i;
	string adr;
	cin >> adr;								//����ļ���ַ
	out.open(adr);
	if (!out)
	{
		cout << "error!" << endl;
	}
	out << "Total: " << dalen << endl;
	for (i = 0; i < dalen; i++)				//ͨ�����������𰸵���Ӧ�ĵ�
	{
		out << "Line" << da[i].textno + 1 << ": " << '<' << mg[da[i].wordno].name << "> " << test[da[i].textno].str.substr(da[i].front, da[i].end - da[i].front + 1) << endl;
	}
	out.close();
}

int main()
{
	system("chcp 65001");

	shuru();								//�������������ĵ���ַ������������

	for (int i = 0; i < tl; i++)			//ÿ�����дʺʹ�����һ��һ���
	{
		for (int j = 0; j < wl; j++)
		{
			find(mg[j], test[i]);
		}
	}

	print();								//���������ַ���������

	return 0;
}