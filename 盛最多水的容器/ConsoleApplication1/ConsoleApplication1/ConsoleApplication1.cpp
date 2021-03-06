// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//708ms
int maxArea(vector<int>& height) {
	int res=0;
	int result=0;
	for (size_t i = 0; i != height.size(); ++i) {
		for (size_t j = i+1; j != height.size(); ++j) {
			res = (j - i)*min(height[i], height[j]);
			if (res > result) {
				result = res;
			}
		}
	}
	return result;
}

//标准答案,80ms，O（n)
int maxArea1(vector<int>& height) {
	int ans, left, right, h;
	ans = 0;
	left = 0;
	right = height.size() - 1;
	while (left<right)
	{
		h = min(height[left], height[right]);
		ans = max(ans, h*(right - left));
		if (height[left]<height[right])
			left++;
		else
			right--;
	}
	return ans;
}
int main()
{
	//vector<int> v = { 1,8,6,2,5,4,8,3,7 };
	vector<int> v = { 1,1 };
	cout << maxArea(v) << endl;
	system("pause");
    return 0;
}

