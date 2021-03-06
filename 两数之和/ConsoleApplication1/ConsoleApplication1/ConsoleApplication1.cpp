// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<vector>
#include<iostream>
#include<utility>
using namespace std;
class Solution {
public:
	Solution(vector<int>& nums, int target) :Num(nums), Target(target) {}
	vector<pair<std::size_t, std::size_t>> twoSum() {
		vector<pair<std::size_t, std::size_t>> v;
		for (std::size_t i = 0; i != Num.size(); ++i) {
			for (std::size_t j = i + 1; j != Num.size(); ++j) {
				if (Num[i] + Num[j] == Target)
					v.push_back(make_pair(i, j));
			}
		}
		return v;
	}
private:
	vector<int> Num;
	int Target;
};


int main()
{
	vector<int> ivec = { 2,7,11,15,6 };
	int target = 13;
	Solution s(ivec, target);
	for (size_t i = 0; i != s.twoSum().size(); ++i) {
		cout << (s.twoSum())[i].first << " " << (s.twoSum())[i].second << endl;
	}
	/*for (vector<pair<size_t,size_t>>::iterator i = s.twoSum().begin(); i != s.twoSum().end(); ++i) {//每次调用成员函数开辟新的地址,所以迭代器不匹配,解决办法是用一个对象接受返回值
		cout << (*i).first << " " << (*i).second << endl;
	}*/
	system("pause");
    return 0;
}

