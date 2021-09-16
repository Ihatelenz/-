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
	string name;
	int no;
	int flag;
}mg[200];

class text
{
public:
	string str;
	int no;
	int flag;
}test[3000];

class ans
{
public:
	int wordno;
	int textno;
	string yuanwen;
}daan[3000];


ifstream filew;
ifstream filet;
int wl, tl;
int dalen=0;
ofstream out;



void shuru(string str1, string str2)
{
	int i=0;
	filew.open(str1);
	if (!filew)
	{
		cout << "error£¡" << endl;
	}
	while (filew >> str1)
	{
		mg[i].name = str1;
		mg[i].no = i;
		mg[i].flag = mg[i].name[0]>0?0:1;
		i++;
	}
	wl = i;
	i = 0;
	filet.open(str2);
	if (!filet)
	{
		cout << "error£¡" << endl;
	}
	while (getline(filet, str2))
	{
		test[i].str = str2;
		test[i].no = i;
		i++;
	}
	tl = i;
}

void charu(int front, int back, int wn, int tn, string wen)
{
	daan[dalen].textno = tn;
	daan[dalen].wordno = wn;
	daan[dalen].yuanwen = wen.substr(front, back);
	dalen++;
}

void find(word& W, text& T)
{
	int i=0,j=0;
	int front=0, back=0;
	int sum = 0,l=0;
	string a,b;
	if (W.flag == 1)
	{
		front = 0;
		back = 0;
		for (; j < T.str.length(); j++)
		{
			if(T.str[j] == W.name[i] && T.str[j + 1] == W.name[i + 1] && T.str[j + 2] == W.name[i + 2])
			{
				if (i==0)
				{
					front = j;
				}
				i += 3;
				j += 2;
				if (i >= W.name.length())
				{
					charu(front, j, W.no, T.no, T.str);
					i = 0;
				}
				
			}
			
			
		}
	}
	else
	{
		front = 0;
		back = 0;
		transform(T.str.begin(), T.str.end(), T.str.begin(), ::tolower);
		transform(W.name.begin(), W.name.end(), W.name.begin(), ::tolower);
		for (; j < T.str.length();j++ )
		{
			if (W.name[i] == T.str[j])
			{
				if (i==0)
				{
					front = j;
				}
				i++;
				if (i >= W.name.length())
				{
					charu(front,j, W.no, T.no, T.str);
					i = 0;
				}
				
			}
			
		}
	}
}

void print(string adr)
{
	int i;
	out.open(adr);
	if(!out)
	{
		cout<<"error!"<<endl;
	}
	out << "Total: " << dalen << endl;
	for (i = 0; i < dalen; i++)
	{
		out << "Line" << daan[i].textno+1 << ": <" << mg[daan[i].wordno].name << "> " << daan[i].yuanwen << endl;
	}
}

int main()
{
	system("chcp 65001"); 
	string str, adrw,adrt,adra;
	int i=0,sum=0,j=0;
	cin >> adrw;
	cin >> adrt;
	cin >> adra;
	shuru(adrw, adrt);
	for (i = 0; i < tl; i++)
	{
		for (j = 0; j < wl; j++)
		{
			find(mg[j], test[i]);
		}
	}
	print(adra);

	return 0;
}