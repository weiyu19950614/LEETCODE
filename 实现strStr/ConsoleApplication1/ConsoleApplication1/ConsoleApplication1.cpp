// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
using namespace std;
//实现类似string中的find功能
int strStr(string haystack, string needle) {
	if (needle.size() == 0) return 0;
	if (haystack.find(needle) == string::npos) return -1;
	else return haystack.find(needle);
}

int main()
{
	//string haystack = "aaaaa", needle = "bba";
	//string haystack = "hello", needle = "ll";
	string haystack = "aaaaa", needle = "";
	//cout << haystack.find(needle) << endl;
	cout << strStr(haystack, needle) << endl;
	system("pause");
    return 0;
}

