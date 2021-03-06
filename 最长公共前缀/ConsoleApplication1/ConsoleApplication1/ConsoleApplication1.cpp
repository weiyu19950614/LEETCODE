// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

//48ms
string longestCommonPrefix(vector<string>& strs) {
	string res = "";
	size_t n = strs.size();
	int count = 0;
	if (strs.empty())
		return res;
	if (strs.size() == 1)
		return strs[0];
	for (size_t i = 0;; ++i) {//string下标
		for (size_t j = 0; j != (n - 1); ++j) {//vector下标
			if (i == strs[j].size())
				return res;
			if (strs[j][i] == strs[j + 1][i])
				++count;
			else {
				return res;
			}
			if (count == n - 1) {
				count = 0;
				res += strs[0][i];
			}
		}
	}
	return res;
}

//标准答案 4ms
class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		int slen = strs.size();
		//特例情况,和我写的一样
		if (slen == 0) return "";
		if (slen == 1) return strs.at(0);
		vector<string> vec = strs;
		string s = vec.at(0);//取第一个字符串
		int len = s.size();//取第一个字符串的长度
		string re = "";
		for (int i = 0; i < len; i++) {//字符串下标，最大是第一个字符串的长度
			for (int j = 1; j < slen; j++) {//向量下标
				if (i >= vec.at(j).size()) {//如果字符串下标大于当前向量索引的值（这里思路和我一样）
					break;//这里会有几次空break,思路没我用return好
				}
				if (vec.at(j).at(i) != s.at(i)) {//如果当前字符串的字符和第一个字符串的当前字符不同（这里思路不一样，他每次都是比第一个字符串，我是比下一个，两次索引所以慢了）
					return re;
				}
				if (j == slen - 1)//比到最后，这里思路一样
					re += s.at(i);
			}
		}
		return re;
	}
};

int main()
{
	vector<string> v = {"" };
	//cout << v[2][2] << endl;
	cout << longestCommonPrefix(v) << endl;
	system("pause");
    return 0;
}

