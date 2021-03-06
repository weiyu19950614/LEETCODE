// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

string intToRoman(int num) {
	string res = "";
	if (num / 1000 != 0) {
		for (int i = 0; i != (num / 1000); ++i) {
			res += 'M';
		}
		num = num % 1000;
	}
	if (num / 100 != 0) {
		if (num / 100 == 9) {
			res += "CM";
		}
		else if (num / 100 == 4) {
			res += "CD";
		}
		else if (num / 100 < 4) {
			for (int i = 0; i != (num / 100); ++i) {
				res += 'C';
			}
		}
		else if (num / 100 == 5) {
			res += 'D';
		}
		else {
			res += 'D';
			for (int i = 5; i != (num / 100); ++i) {
				res += 'C';
			}
		}
		num = num % 100;
	}
	if (num / 10 != 0) {
		if (num / 10 == 9) {
			res += "XC";
		}
		else if (num / 10 == 4) {
			res += "XL";
		}
		else if (num / 10 < 4) {
			for (int i = 0; i != (num / 10); ++i) {
				res += 'X';
			}
		}
		else if (num / 10 == 5) {
			res += 'L';
		}
		else {
			res += 'L';
			for (int i = 5; i != (num / 10); ++i) {
				res += 'X';
			}
		}
		num = num % 10;
	}
		if (num  == 9) {
			res += "IX";
		}
		else if (num  == 4) {
			res += "IV";
		}
		else if (num  < 4) {
			for (int i = 0; i != (num); ++i) {
				res += 'I';
			}
		}
		else if (num  == 5) {
			res += 'V';
		}
		else {
			res += 'V';
			for (int i = 5; i != (num); ++i) {
				res += 'I';
			}
		}
	return res;
}


//标准答案,思路一样快一点点
class Solution {
public:
	string intToRoman(int num) {
		int q = num / 1000;
		int b = num % 1000 / 100;
		int s = num / 10 % 10;
		int g = num % 10;

		string str;

		while (q-->0)
			str += 'M';

		if (b<4)
			while (b-->0)
				str += 'C';
		else if (b == 4)
			str += "CD";
		else if (b<9)
		{
			str += "D";
			while (b-->5)
				str += 'C';
		}
		else if (b == 9)
			str += "CM";

		if (s<4)
			while (s-->0)
				str += 'X';
		else if (s == 4)
			str += "XL";
		else if (s<9)
		{
			str += "L";
			while (s-->5)
				str += 'X';
		}
		else if (s == 9)
			str += "XC";

		if (g<4)
			while (g-->0)
				str += 'I';
		else if (g == 4)
			str += "IV";
		else if (g<9)
		{
			str += "V";
			while (g-->5)
				str += 'I';
		}
		else if (g == 9)
			str += "IX";

		return str;
	}
};
int main()
{
	for (int i = 1; i != 4000; ++i) {
		cout << intToRoman(i) <<' ';
		if (!(i % 10))
			cout << endl;
	}
	cout << endl;
	system("pause");
    return 0;
}

