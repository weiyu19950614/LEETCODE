// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;

//遍历检查,20ms
int removeElement1(vector<int>& nums, int val) {
	for (size_t i = 0; i != nums.size(); ++i) {
		if (nums[i] == val) {
			nums.erase(nums.begin() + i);
			--i;
		}
	}
	return nums.size();
}

//取出不相等的,填入前面，避免删除,因为之后的不用管,48ms
int removeElement(vector<int>& nums, int val) {
	int cur = 0;
	for (size_t i = 0; i != nums.size(); ++i) {
		if (nums[i] != val) {
			nums[cur++] = nums[i];
		}
	}
	return cur;
}

int main()
{
	vector<int> nums = { 0,1,2,2,3,0,4,2 };
	cout << removeElement(nums, 2) << endl;
	system("pause");
    return 0;
}

