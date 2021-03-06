// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
using namespace std;
string longestPalindrome(string s) {
	int iLen((int)s.length());//首先获取字符串的长度
	if (s.empty())//判断字符串是否为空
	{
		return "";
	}

	if (iLen == 1)//如果字符串长度为1
	{
		return s;
	}

	int iStart(0);//定义头尾状态符
	int iMaxLen(1);
	for (int i = 0; i < iLen; /*++i*/)
	{
		if (iLen - i <= iMaxLen / 2)//剩余长度小于imaxlen的一半之后就没必要继续了循环检查了
		{
			break;
		}

		int iLeft(i);//内部循环当前的左右状态符
		int iRight(i);
		while (iRight < iLen - 1 && s.at(iRight) == s.at(iRight + 1))//没有检索完且是重复字符时推进iright
		{
			//连续重复是特殊情况,无论有多少个都可以构成回文（看作一个字符）
			//没有其实也可以，只是次数要增加，浪费时间
			++iRight;
		}

		i = iRight + 1;//直接跳过重复的检索，将左右状态符都推进至重复末端

		while (iRight < iLen - 1 && iLeft > 0 && s.at(iLeft - 1) == s.at(iRight + 1))//判断i左右两个字符是否相等，一般情况,避免出现-1
		{
			//随着i移动后一直往左右两边探
			--iLeft;
			++iRight;
		}

		int iNewLen(iRight - iLeft + 1);
		if (iNewLen > iMaxLen)//新的回文是否大于原来的
		{
			iStart = iLeft;
			iMaxLen = iNewLen;
		}
	}

	return s.substr(iStart, iMaxLen);
}

int main()
{
	//回文的意思是一组对称的字符串,ccc/abcda/a/cbbd/bananas/babad/aaabaaaa/aaabaa
	string s("abcdeafghahgfaedcbaaaaaa");
	//cout << s[2] << " " << s[s.size() - 2 - 1] << endl;
	//cout << s.substr(0, 2) << endl;
	//cout << s.find_first_of('e') << " " << s.find_last_of('e') << endl;
	//longestPalindrome(s);
	cout << longestPalindrome(s) << endl;
	system("pause");
    return 0;
}

