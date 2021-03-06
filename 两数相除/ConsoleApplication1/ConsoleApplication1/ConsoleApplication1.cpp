// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include"math.h"
#include<bitset>//这个真香,可以看二进制
using namespace std;
//两数相除,不能使用乘法、除法、mod运算符（C++中一个求余函数)
//32位有符号整数2^31-1和-2^31（32位计算机里面int是16位,现在64位的是32位)
//偷懒的话可以都先化成long比较
//思路利用减法（或者加法），统计次数
//太慢了,会超出时间限制
int divide1(int dividend, int divisor) {
	int res = 0;
	const int min32 = 0x80000000;//-2的31次方=-2147483648
	const int max32 = 0x7fffffff;//2的31次方-1=2147483647
	//确定符号
	bool Ispositive = true;
	//把两个数都变成正整数
	//有一个隐患问题,如果是min32反过来会超过max32
	//但是max32反过来并不会超过min32,因此把两个数都变成负整数计算反而更简洁
	if (dividend > 0) { dividend = -dividend; Ispositive = !Ispositive; }
	if (divisor > 0) { divisor = -divisor; Ispositive = !Ispositive; }
	while (dividend <= divisor) {
		dividend -= divisor;
		--res;
	}
	if (Ispositive) {
		if (res == min32) {
			return max32;
		}
		return -res;
	}
	else return res;
}


//利用对数和指数,math.h头文件
//log只能处理正整数
//通过32ms
int divide(int dividend, int divisor) {
	bool Ispositive = true;
	//特殊情况处理-2147483648
	if (divisor == INT_MIN) {
		if (dividend == INT_MIN) return 1;
		else return 0;
	}
	if (dividend == INT_MIN&&divisor!=INT_MIN) {
		if (divisor == 1)return INT_MIN;
		else if (divisor == -1)return INT_MAX;
		//其他情况不会超出范围了,把2的31次方拆成2的15次和16次
		else {
			if (divisor < 0) {
				divisor = -divisor;
				return int(exp(log(32768) + log(65536) - log(divisor)));
			}
			else {
				return -int(exp(log(32768) + log(65536) - log(divisor)));
			}
		}
	}
	if (dividend < 0) { dividend = -dividend; Ispositive = !Ispositive; }
	if (divisor < 0) { divisor = -divisor; Ispositive = !Ispositive; }
	int res=exp(log(dividend) - log(divisor));
	if (!Ispositive) return -res;
	return res;
}

//标准答案就我这两种
int main()
{
	int dividend = INT_MIN;//十六进制\INT_MIN可以接受,但-2147483648这样输入就不行//两个cpp的sdl都要改成否
	int divisor =-3;
	cout <<divide(dividend,divisor) << endl;
	//cout << std::hex<<INT_MIN << endl;//看16进制,0x表示是十六进制
	//cout << bitset<32>(INT_MIN) << endl;
	//cout << int(exp(log(10)-log(3))) << endl;
	system("pause");
    return 0;
}

