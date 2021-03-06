// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
using namespace std;
//字符串检查回文
bool hw(string s) {
	size_t right = s.size()-1;
	size_t left = 0;
	while (left != (s.size() / 2)) {
		if (s[left] != s[right]) {
			return false;
		}
		++left;
		--right;
	}
	return true;
}
//整数转字符串
string int2str(int a) {
	string str;
	string res;
	bool positive = true;
	if (a < 0) {
		a = -a;
		positive = false;
	}
	while (a != 0) {
		switch (a % 10) {//switch不遇到break会从开始的case一直往下走直到遇到break
		case 0:str += '0'; break;
		case 1:str += '1'; break;
		case 2:str += '2'; break;
		case 3:str += '3'; break;
		case 4:str += '4'; break;
		case 5:str += '5'; break;
		case 6:str += '6'; break;
		case 7:str += '7'; break;
		case 8:str += '8'; break;
		case 9:str += '9'; break;
		}
		a = a / 10;
	}
	if (positive == false)
		str += '-';
	for (auto it = str.crbegin(); it != str.crend(); ++it) {//倒序输出
		res += (*it);
	}
	return res;
}

int main()
{
	//cout << 5 / 2 << endl;
	int a = -214748364789;
	string s = int2str(a);
	cout << s << endl;
	cout << hw(s) << endl;
	system("pause");
    return 0;
}

