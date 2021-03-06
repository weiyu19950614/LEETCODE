// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//和三数之和有点区别,它是找最接近的,而三数之和是找等于0的

//遍历法o(n3）,能通过76ms
int threeSumClosest1(vector<int>& nums, int target) {
	int result = 0, min = 0;
	if (nums.size() < 3) {
		for (int i = 0; i != nums.size(); ++i) {
			result += nums[i];
		}
		return result;
	}
	min = abs(nums[0] + nums[1] + nums[2] - target);
	result = nums[0] + nums[1] + nums[2];
	for (int i = 0; i != nums.size()-2; ++i) {
		for (int left = i + 1; left != nums.size() - 1; ++left) {
			for (int right = left + 1; right != nums.size() ; ++right) {
				if (abs(nums[i] + nums[left] + nums[right] - target) < min) {
					min = abs(nums[i] + nums[left] + nums[right] - target);
					result = nums[i] + nums[left] + nums[right];
				}
				if (abs(nums[i] + nums[left] + nums[right] - target) == 0) {
					return target;
				}
			}
		}
	}
	return result;
}

//先排序,16ms,类似找0,用时和标准答案一样
int threeSumClosest(vector<int>& nums, int target) {
	int result = 0,min=0;
	if (nums.size() < 3) {
		for (int i = 0; i != nums.size(); ++i) {
			result += nums[i];
		}
		return result;
	}
	min = abs(nums[0] + nums[1] + nums[2] - target);
	result = nums[0] + nums[1] + nums[2];
	sort(nums.begin(),nums.end());
	for (int i = 0; i != nums.size() - 2; ++i) {
		int m = target - nums[i];
		int left=i+1,right=nums.size()-1;
		while (left != right ) {
			if (abs(nums[left] + nums[right] - m) < min) {
				min = abs(nums[i] + nums[left] + nums[right] - target);
				result = nums[i] + nums[left] + nums[right];
			}
			if (nums[left] + nums[right] < m) {
				++left;
			}
			else if (nums[left] + nums[right] > m) {
				--right;
			}
			else {
				return target;
			}
		}
	}
	return result;
}
int main()
{
	vector<int> nums = { 0,2,1,-3 };
	cout << threeSumClosest(nums, 1) << endl;
	system("pause");
    return 0;
}

