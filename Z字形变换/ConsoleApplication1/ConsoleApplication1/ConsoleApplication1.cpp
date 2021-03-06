// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;
string convert(string s, int numRows) {

	if (numRows == 1) return s;

	vector<string> rows(min(numRows, int(s.size())));
	int curRow = 0;
	bool goingDown = false;

	for (char c : s) {
		rows[curRow] += c;
		if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
		curRow += goingDown ? 1 : -1;
	}

	string ret;
	for (string row : rows) ret += row;
	return ret;
}

int main()
{
	//cout << 5 / 2 << " " << 5 % 2 << endl;
	cout << convert("LEETCODEISHIRING", 14) << endl;
	/*string s("helloworld");
	int j = 3;
	size_t i=j ;
	if (i < s.size()) {
		cout << "*****" << endl;
	}*/
	system("pause");
    return 0;
}

