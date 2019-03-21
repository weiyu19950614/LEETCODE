// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;
long long f1(long b, long e) {
	long long res = 1;
	for (int i = 0; i != e; ++i) {
		res *= b;
	}
	return res;
}
int reverse(int x) {

	if (x == -2147483648)
		return 0;

	long long ri=0;
	int count = 0;
	int r = 0;
	if (x < 0)
	{
		count = 1;
		x = -x;
	}
	if (x == 0)
		return x;

	while (!(x % 10)) {
		x /= 10;
	}

	if (x < 10&&count==0)
		return x;
	if (x < 10 && count == 1)
		return -x;



	for (int e = 10; e != 0; --e) {
		if (x / f1(10, e)) {
			ri += x / f1(10, e)*f1(10, r);
			++r;
			x = x - x / f1(10, e)*f1(10, e);
			if (x < f1(10, e-1)) {
				for (int j = e - 1; x<f1(10,j); --j) {
					++r;
				}
			}
			if (x < 10) {
				ri += x*f1(10, r);
			}
		}
	}
	if (ri >2147483647 )
		return 0;
	if (count == 1)
		ri = -ri;
	return ri;
}
int reverse1(int x) {
	const int min32 = 0x80000000;
	const int max32 = 0x7fffffff;
	long long result = 0;
	for (; x != 0;) {
		result = result * 10 + x % 10;//关键所在
		x = x / 10;
	}
	if (result < min32 || result > max32) {
		return 0;
	}
	return result;
}

int main()
{
	/*int inw = 1;
	for (int i = 1; i != 32; ++i) {
		inw *= 2;
	}
	cout << inw-1 <<" "<<-inw<< " "<<reverse(2247483647)<<" "<<f1(2,3)<<endl;
	/*int inw = -321;
	cout << inw / 100 << endl;
	cout << inw / f1(10,2)*f1(10, 2) << endl;*/
	/*long long we = 1234567891011;
	int s = 1;
	we += s;
	cout << we << endl;*/
	//cout << f1(2, 61) << endl;
	cout << reverse1(1463847412) << endl;
	//cout << 10 % 10 << endl;
	//int ww = -2147483648;
	system("pause");
    return 0;
}

