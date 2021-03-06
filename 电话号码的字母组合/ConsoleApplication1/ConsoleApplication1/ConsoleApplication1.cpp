// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string>
#include<vector>
#include<iostream>
#include<map>
#include<algorithm>
#include<queue>
using namespace std;

//12ms,顺序添加
vector<string> letterCombinations(string digits) {
	vector<string> result = {};
	vector<string> res = {};
	map<char, string> m = { { '2',"abc" },{'3',"def"},{'4',"ghi"},{'5',"jkl"},{'6',"mno"},{'7',"pqrs"},{'8',"tuv"},{'9',"wxyz"} };
	//难点在于无法确定有几重循环
	for (size_t i = 0; i != digits.size(); ++i) {
		//对于不是0和1的有效数字
		if (digits[i] != '0'&&digits[i] != '1'&&digits[i] != '*'&&digits[i] != '#') {
			//初始化res
			if (res.size() == 0) {
				for (auto c : m[digits[i]]) {
					string s;
					s += c;
					result.push_back(s);
				}
			}
			//先重复之前的,并添加新的
			for (size_t j = 0; j != m[digits[i]].size(); ++j) {
				for (auto c : res) {
					string s = c + m[digits[i]][j];
					result.push_back(s);
				}
			}
			res = result;
			result = {};
		}
	}
	return res;
}

//标准答案12ms
vector<string> letterCombinations1(string digits) {
	// https://blog.csdn.net/Scarlett_Guan/article/details/79916603  宽搜 深搜
	vector<string> aa{ "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
	if (digits.empty()) return vector<string>{};
	queue<string>re;//双端队列
	re.push("");
	for (int i = 0; i < digits.size(); ++i) {
		int length = re.size();
		for (int j = 0; j<length; ++j) {
			string temp = re.front();
			re.pop();
			for (char x : aa[digits[i] - '0']) {
				re.push(temp + x);
			}
		}
	}
	vector<string>ans;
	while (!re.empty()) {
		ans.push_back(re.front());
		re.pop();
	}
	return ans;
}

int main()
{
	//没必要用vector,string本身也是容器
	//map<string, vector<string>> m = { {"2",{"a","b","c"}},{"3",{"d","e","f"}} };
	//map<string, string> m = { {"2","abc"} };
	//cout << *(m["5"].begin()) <<" "<<m["5"][0]<< endl;
	vector<string> v = letterCombinations("11*2#*34");
	for (string c : v) {
		cout << c << " ";
	}
	cout << endl;
	/*string s = "189*83#";
	s.erase(s.begin()+2);
	cout << s << endl;*/
	system("pause");
    return 0;
}

