// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<map>
using namespace std;

int romanToInt(string s) {
	int res=0;
	map<char, int > Roman = { { 'I', 1 },{ 'V',5 },{ 'X',10 },{ 'L',50 },{ 'C',100 },{ 'D',500 },{ 'M',1000 } };
	for (size_t i = 0; i != (s.size()-1); ++i) {
		if (Roman[s[i]] < Roman[s[i + 1]])
			res += (-Roman[s[i]]);
		else
			res += Roman[s[i]];
	}
	res += Roman[s[s.size() - 1]];
	return res;
}

//标准答案,用数组做存储,比用map快一点,数组的下标用字符码表示
class Solution {
public:
	int romanToInt(string s) {
		// https://blog.csdn.net/net_wolf_007/article/details/51770112 
		// 以ASCII中字母对应位置保存，该字符的roman数字
		int tagVal[256];
		tagVal['I'] = 1;
		tagVal['V'] = 5;
		tagVal['X'] = 10;
		tagVal['C'] = 100;
		tagVal['M'] = 1000;
		tagVal['L'] = 50;
		tagVal['D'] = 500;
		int val = 0;
		for (int i = 0; i < s.length(); i++) {
			// 如果是最后一个字符，或者前一个字符比后一个字符大，即左边的字符比右边的字符大时
			if (i + 1 >= s.length() || tagVal[s[i + 1]] <= tagVal[s[i]])
				val += tagVal[s[i]];
			// 如果是特例情况，前一个字符比后一个字符小，即左边的字符比右边的字符小时
			else
				val -= tagVal[s[i]];
		}
		return val;

	}
};

int main()
{
	/*map<char, int > Roman= { {'I', 1}, { 'V',5 }, { 'X',10 }, { 'L',50 }, { 'C',100 }, { 'D',500 }, { 'M',1000 }};
	cout << Roman['V'] << endl;
	if (Roman['V'] > Roman['I'])
		cout << true << endl;*/
	cout << romanToInt("MMDCCXCII") << endl;
	system("pause");
    return 0;
}

