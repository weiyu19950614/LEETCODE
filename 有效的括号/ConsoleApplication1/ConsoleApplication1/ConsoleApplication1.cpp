// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<map>
#include<stack>
using namespace std;

//括号要闭合,先处理内圈括号,遍历法,1536ms
bool isValid1(string s) {
	if (s=="")return true;
	//先剔除掉s里面的空格
	/*for (int i = 0; i != s.size(); ++i) {
		if (s[i] == ' ') {
			s.erase(s.begin() + i);
			--i;
		}
	}*/
	//建立map对应关系
	map<char, char>  brackets = { {'(',')'},{'[',']'},{'{','}'} };
	size_t left = 0, right = 0;
	if (s.size() % 2) return false;
	while (s.size()!=0) {
		right = s.find_first_of(brackets[s[left]]);//先消除内圈的括号
		if (right == string::npos) return false;
		if (right != left + 1) {
			++left;
			continue;
		}
		else {
			//删除配对括号
			s.erase(s.begin() + left,s.begin()+right+1);
			left = 0;
		}
	}
	return true;
}

//stack压栈数据结构先进后出很适合
bool isValid(string s) {
	if (s.empty()) return true;
	stack<char> paren;
	for (int i = 0; i < s.size(); i++) {
		switch (s[i]) {
		case '(':
		case '[':
		case '{': paren.push(s[i]); break;
		case ')': {
			if (paren.empty() || paren.top() != '(') return false;
			paren.pop();
			break;
		}
		case ']': {
			if (paren.empty() || paren.top() != '[') return false;
			paren.pop();
			break;
		}
		case '}': {
			if (paren.empty() || paren.top() != '{') return false;
			paren.pop();
			break;
		}
		default: break;
		}
	}
	if (!paren.empty()) return false;
	return true;
}

int main()
{
	//string s = "()";
	//string s = "()[]{}";
	//string s = "(]";
	//string s = "([)]";
	//string s = "{[]}";
	//string s = "{[]{}}";
	//string s = "(())";
	//string s = "[({(())}[()])]";//最外层括号内有两组括号应该分开拆
	string s = "(())()";
	cout << isValid(s) << endl;
	system("pause");
    return 0;
}

