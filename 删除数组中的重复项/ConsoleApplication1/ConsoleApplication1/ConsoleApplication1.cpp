// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;

//372ms，题目要求不能使用多余空间
int removeDuplicates1(vector<int>& nums) {
	if (nums.size() == 0) return 0;
	if (nums.size() == 1) return 1;
	for (size_t i = 1; i != nums.size(); ++i) {
		if (nums[i] == nums[i - 1]) {
			nums.erase(nums.begin() + i);
			--i;
		}
	}
	return nums.size();
}

//标准答案,64ms，因为只需要修改前面几个不同的后面并不用管
int removeDuplicates(vector<int>& nums) {
	int cur = 0;
	int l = nums.size();
	if (l == 0) return 0;
	for (int i = 1; i < l; i++) {
		if (nums[i] != nums[cur]) {//从0开始找,出现不等的开始往下一位
			nums[++cur] = nums[i];
		}
	}
	return cur + 1;
}


int main()
{
	//vector<int> nums = { 1,1,2 };
	vector<int> nums = { 0,0,1,1,1,2,2,3,3,4 };
	cout << removeDuplicates(nums) << endl;
	for (auto c : nums) {
		cout << c << " ";
	}
	cout << endl;
	system("pause");
    return 0;
}

