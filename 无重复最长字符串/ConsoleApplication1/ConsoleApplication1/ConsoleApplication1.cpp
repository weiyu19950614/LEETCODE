// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string>
#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	string s = "adefbbbbb";
	//逻辑思维和暴力法起始是一样的，不断移动左值，只是不用find来移动左值，因为知道只有128个字符或者256个字符
		vector <int>hax(128, -1);//字符集128个，初始化为-1
		int res = 0;
		int left = -1;
		for (int i = 0; i<s.size(); ++i)
		{
			left = max(left, hax[s[i]]);//对字符进行int转换,如果不重复出现一直是-1
			hax[s[i]] = i;//该字符位置的值由原值变为i（两次间隔即是长度）
			res = max(i - left, res);
		}
	system("pause");
    return 0;
}

