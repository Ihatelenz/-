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
	string name;	//存储敏感词
	int no;			//敏感词号
	int flag;		//中英文区别变量
}mg[200];

class text
{
public:
	string str;		//存储一行的待测文章
	int no;			//行号
}test[3000];

class ans
{
public:
	int wordno;		//所属敏感词号
	int textno;		//所属行号
	int front;		//变形后的敏感词的起始位置
	int end;		//变形后的敏感词的结束位置
}da[3000];


ifstream filew;		//敏感词输入文件
ifstream filet;		//待测文章输入文件
int wl, tl;			//敏感词数，文章行数
int dalen = 0;		//答案总数
ofstream out;		//答案输出文件



void shuru()										//处理输入数据并输入文件
{
	int i = 0;
	string str1, str2;
	cin >> str1;
	filew.open(str1);
	if (!filew)										//输入地址错误判断
	{
		cout << "error！" << endl;
	}
	while (filew >> str1)
	{
		mg[i].name = str1;
		mg[i].no = i;
		mg[i].flag = mg[i].name[0] > 0 ? 0 : 1;		//判断中文或英文
		i++;
	}
	wl = i;
	filew.close();
	i = 0;
	cin >> str2;
	filet.open(str2);
	if (!filet)										//输入地址错误判断
	{
		cout << "error！" << endl;
	}
	while (getline(filet, str2))					//一行一行录入text类
	{
		test[i].str = str2;
		test[i].no = i;
		i++;
	}
	tl = i;
	filet.close();
}

void charu(int front, int back, int wn, int tn)		//处理答案，并录入ans类
{
	da[dalen].textno = tn;
	da[dalen].wordno = wn;
	da[dalen].front = front;
	da[dalen].end = back;
	dalen++;
}

void find(word& W, text& T)							//查找对应敏感词段
{
	int i = 0, j = 0;
	int front = 0, back = 0;
	int sum = 0, l = 0;
	int fei = 0;
	string a;
	string  b;
	if (W.flag == 1)								//中文匹配
	{
		front = 0;
		back = 0;
		for (; j < T.str.length(); j++)
		{
			a = W.name.substr(i, 3);				//一个中文编码三字节，每三字节取出配对
			b = T.str.substr(j, 3);
			if (a==b)
			{
				if (i == 0)
				{
					front = j;
				}
				i += 3;
				j += 2;
				if (i == W.name.length())			//一个完整敏感词匹配结束，录入答案
				{
					charu(front, j, W.no, T.no);
					i = 0;
				}

			}


		}
	}
	else											//英文匹配
	{
		front = 0;
		back = 0;
		transform(T.str.begin(), T.str.end(), T.str.begin(), ::tolower);			//待测行和待测敏感词不区分大小写，全部转换成小写
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
				if (i == W.name.length())			//一个完整敏感词匹配结束，录入答案
				{
					charu(front, j, W.no, T.no);
					i = 0;
					fei = 0;
				}

			}
			else
				fei++;
			if (fei > 20)							//插入无关字符超过20个，结束匹配
				break;

		}
	}
}

void print()
{
	int i;
	string adr;
	cin >> adr;								//输出文件地址
	out.open(adr);
	if (!out)
	{
		cout << "error!" << endl;
	}
	out << "Total: " << dalen << endl;
	for (i = 0; i < dalen; i++)				//通过输出流输出答案到对应文档
	{
		out << "Line" << da[i].textno + 1 << ": " << '<' << mg[da[i].wordno].name << "> " << test[da[i].textno].str.substr(da[i].front, da[i].end - da[i].front + 1) << endl;
	}
	out.close();
}

int main()
{
	system("chcp 65001");

	shuru();								//输入两个测试文档地址，并处理数据

	for (int i = 0; i < tl; i++)			//每个敏感词和待测行一对一检测
	{
		for (int j = 0; j < wl; j++)
		{
			find(mg[j], test[i]);
		}
	}

	print();								//输入输出地址，并输出答案

	return 0;
}