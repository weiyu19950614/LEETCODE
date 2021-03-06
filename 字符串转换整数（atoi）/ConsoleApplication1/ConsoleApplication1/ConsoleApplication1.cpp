// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
using namespace std;

int myAtoi(string str) {
	long long result = 0;
	const int min32 = 0x80000000;//-2的31次方
	const int max32 = 0x7fffffff;//2的31次方-1
	int zf = 0;
	for (int i = 0; i != str.size(); ++i) {
		char c = '0';
		if (str[i] != ' ') {
			if ('0' <= str[i]&& str[i] <= '9') {//&&是必须的的,C++没有连续运算符
				for (int j = 0; j != 10; ++j) {
					if (str[i] == c) {
						result = result * 10 + (c - 48);
					}
					++c;
				}
			}
			else if (str[i] == '-') {
				zf = 1;
			}
			else if (str[i] == '+') {
				zf = 0;
			}
			else {
				return 0;
			}
			if (result > max32&&zf == 0)
				return max32;
			if (-result < min32&&zf == 1)
				return min32;
			if (str[i + 1] > '9' || str[i + 1] < '0')
				break;
		}
	}
	if (zf == 0) {
		return result;
	}
	else {
		return -result;
	}
}

class Solution {
public:
	int myAtoi(string str) {
		int res = 0;
		int pos = 0;
		int len = str.length();
		bool isPositive = true;
		while (str[pos] == ' ' && pos < len)
			++pos;
		if (str[pos] == '-' && pos < len)
		{
			++pos;
			isPositive = false;
		}
		else if (str[pos] == '+' && pos < len)
			++pos;
		while (pos < len)
		{
			if (str[pos] > '9' || str[pos] < '0')
				break;
			else if (str[pos] >= '0' && str[pos] <= '9')
			{
				if (res >= INT_MAX / 10)
				{
					if (isPositive && (res > INT_MAX / 10 || str[pos] - '0' > 7))//正数
						return INT_MAX;
					else if (!isPositive && (res > INT_MAX / 10 || str[pos] - '0' > 8))//负数
						return INT_MIN;
					else
					{
						res = res * 10 + (str[pos] - '0');
						break;
					}
				}
				else
					res = res * 10 + (str[pos] - '0');
			}
			pos++;
		}
		if (isPositive)
			return res;
		return -res;
	}
};



int main()
{
	/*string s = "-12";//C++标准库atoi自带转换功能
	int a = atoi(s.c_str());
	cout << a << endl;*/
	/*char c = '0';
	int b = int(c);
	cout << c << " "<<b<<endl;//0对应48，4对应52,5对应53。。。ASCI码
	cout << char(c+1)<<" "<<c + 1 << endl;
	if (c == char(48))
		cout << "zero correspone 48" << endl;*/
	//cout << myAtoi("2147483649") << endl;//超过会从-的最小加上超过的值因此要没加一步就检查是否超过限制
	//cout << myAtoi("9223372036854775808") << endl;//避免使用longlong投机取巧
	cout << myAtoi("2147483649") << endl;
	system("pause");
    return 0;
}

