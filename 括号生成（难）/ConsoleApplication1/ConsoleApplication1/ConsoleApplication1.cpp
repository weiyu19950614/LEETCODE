// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<list>
using namespace std;

//括号生成思路,在n-1的情况下有q种形式,对于每一个形式再加入一个括号有多少组合的问题.
//扩展方式无外乎左右和包括->会遗漏偶数的特殊情况,额外处理,会以(())这类形式插入
//问题变成如何避免重复,如果每次都遍历问题规模很大(哪怕每次查找都是nlogn依然很大)->n²logn,所以总时间是mn²logn，m是输入的括号对数
vector<string> generateneParthesis1(int n) {
	if (n == 0) return {};
	vector<string> res = {"()"};
	vector<string> result = {};
	int counter = 1;
	while (counter != n) {
		for (size_t i = 0; i !=res.size() ; ++i) {
			result.push_back("(" + res[i] + ")");
			if (find(result.begin(), result.end(), "()" + res[i]) == result.end()) result.push_back("()" + res[i]);
			if (find(result.begin(), result.end(), res[i]+"()") == result.end()) result.push_back(res[i]+"()");
		}
		res = result;
		result = {};
		++counter;
	}
	return res;
}

//有这样一种暴力的方法，每个位置2个选择,n个有2的2n次方种组合,然后在找出有效的
vector<string> generateneParthesis2(int n) {
	if (n == 0) return {};

}


//最快的
char s[10000];//看作字符串就好了,字符数组,索引也和字符串一样
vector<string>res;
int up, c0, c1;//c0记录有多少个（,c1记录有多少个）
//循环函数填所有可能性，算法的思路没搞清楚
void dfs(int step) {//step是记录填到第几位
	cout << step << " " << s << " " << c0 << " " << c1 << endl;
	if (step == up) {//up是2*n,可以填的长度（位数）
		res.push_back(s);//填完了,将该种可能保存
		return;//难点，提前结束当前迭代函数
	}
	if (c1<up / 2 && c0>c1) {//只有当（多于）时才能填入）
		c1++;
		s[step] = ')';//当前位置填入')';
		dfs(step + 1);//填下一个位置
		c1--;
	}
	if (c0<up / 2) {//（的个数不可能超过长度位数的一半
		c0++;
		s[step] = '(';//当前位置填入'('
		dfs(step + 1);//填下一个位置
		c0--;//c0在减少前已经进入下一次函数迭代
	}
}
vector<string> generateneParthesis(int n) {
	up = 2 * n; c0 = c1 = 0; dfs(0); return res;
}

//每一种都试过，保存有效的,比较慢一点，错了往回一步
/*void Next(vector<string> &returnAns, string ans, int count1, int count2, int n) {//第一个是保存结果,ans是每一种可能
	cout << ans << " " << count1 << " " << count2 << endl;
	if (count1>n || count2>n || count2>count1) return;
	if (count1 == n&&count2 == n) {
		returnAns.push_back(ans);
		return;
	}
	Next(returnAns, ans + "(", count1 + 1, count2, n);
	Next(returnAns, ans + ")", count1, count2 + 1, n);
	return;
}

vector<string> generateneParthesis(int n) {
	vector<string> returnAns;
	int count1 = 0;
	int count2 = 0;
	Next(returnAns, "", count1, count2, n);
	return returnAns;

}*/

//总结,算法的思路都是利用迭代函数
int main()
{
	/*vector<string> v = { "hello","hi","wow" };
	vector<string>::iterator it= find(v.begin(),v.end(), "hii");
	if (it != v.end()) {
		cout << "find" << endl;
	}*/
	vector<string> v = generateneParthesis(3);//4->14
	for (auto c : v) {
		cout << c <<endl;
	}
	/*char s[3] = "wf";
	cout << s[0] << endl;*/
	//cout << Mi(3, 3) << endl;
	system("pause");
    return 0;
}

