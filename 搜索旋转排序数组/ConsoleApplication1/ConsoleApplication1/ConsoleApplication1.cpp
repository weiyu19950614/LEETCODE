// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>//懒得写查找的二分了,STL的binary search只能判断有没有
#include<Windows.h>
using namespace std;


//有一按升序排序的数组在某个节点处发生了翻转：0124567->4567012
//给定目标值查询，返回索引，不存在返回-1
//时间复杂度不能超过logn
//思路：二分查找明显是可以的，但是问题是目前的排序不是正序的，如果盲目排序是nlogn
//二分查找旋转点logn，查找值logn，那么算法复杂度O（logn）
//特征：旋转点要不是低谷要不是高峰
//20ms
int search1(vector<int>& nums, int target) {
	if (nums.empty()) return -1;
	if (nums.size() == 1) {
		if (nums[0] == target) return 0;
		else return -1;
	}
	int n = nums.size();
	int left = -1; int right = nums.size(); int mid = (left + right) / 2;
	bool Isgf = false;
	//二分查找找到断点其实很难//断点一定存在找到即可跳出循环
	while (right!=0) {//完全顺序的话，right会降为0
		//两个if避免到达边界之后还检索下一个报错
		if (mid == 0) {
			if (nums[mid] >= nums[mid + 1]) {//高峰
				Isgf = true; break;
			}
			else {//完全顺序
				right = mid;
				break;
			}
		}
		if (mid == n - 1) {
			if (nums[mid] <= nums[mid - 1]) {
				break;
			}
		}
		if (nums[mid] >= nums[mid + 1]) {//高峰
			Isgf = true; break;
		}
		if (nums[mid] <= nums[mid - 1]) {//低谷
			break;
		}
		//两个队列都是升序怎么推进left和right->通过和尾值比较
		if (nums[mid] > nums[n - 1]) {
			left = mid; mid = (right + left) / 2;
		}
		else {
			right = mid; mid = (right + left) / 2;
		}
	}
	//如果完全顺序
	if (left == -1 && right == left + 1) {
		right = n; left = -1; mid = (right + left) / 2;
		if (target > nums[n - 1]) return -1;
		if (target < nums[0]) return -1;
		while (right != left + 1) {
			if (nums[mid] < target) {
				left = mid; mid = (right + left) / 2;
			}
			else if (nums[mid] > target) {
				right = mid; mid = (right + left) / 2;
			}
			else {
				return mid;
			}
		}
		return -1;
	}
	if (Isgf) {//高峰情况
		//确定在哪个半区检索
		if (target > nums[mid] || nums[mid+1] > target) return -1;
		if (target<=nums[mid] && target>=nums[0]) {
			left = -1; right = mid + 1; mid = (right + left) / 2;
		}
		if (target >= nums[mid + 1] && target <= nums[n - 1]) {
			left = mid; right = n; mid = (right + left) / 2;
		}
		while (right != left + 1) {
			if (nums[mid] < target) {
				left = mid; mid = (right + left) / 2;
			}
			else if (nums[mid] > target) {
				right = mid; mid = (right + left) / 2;
			}
			else {
				return mid;
			}
		}
	}
	else {//低谷情况
		if (target > nums[mid-1] || nums[mid] > target) return -1;
		if (target <= nums[mid-1] && target >= nums[0]) {
			left = -1; right = mid ; mid = (right + left) / 2;
		}
		if (target >= nums[mid] && target <= nums[n - 1]) {
			left = mid-1; right = n; mid = (right + left) / 2;
		}
		while (right != left + 1) {
			if (nums[mid] < target) {
				left = mid; mid = (right + left) / 2;
			}
			else if (nums[mid] > target) {
				right = mid; mid = (right + left) / 2;
			}
			else {
				return mid;
			}
		}
	}
	return -1;
}

//思路二，其实两个部分都是升序的，我们每次二分查找的时候看看mid是不是还在原队列即可，12ms
int search(vector<int>& nums, int target) {
	int l = 0, r = nums.size() - 1;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		//cout << mid << endl;
		if (nums[mid] == target) return mid;
		if (nums[mid] >= nums[0]) {//落在第一队列
			//前半部分有序
			if (nums[mid]>target&&target >= nums[0]) r = mid - 1;//如果target比第一个小那么应该去第二队列找因此把l提上来
			else l = mid + 1;
		}
		else {//落在第二队列
			//后半部分有序
			if (nums[mid]<target&&target <= nums.back()) l = mid + 1;
			else r = mid - 1;
		}
	}
	return -1;
}

int main()
{
	DWORD start = GetTickCount64();
	vector<int> nums = { 4,5,6,7,0,1,2 };//4567012-0;
	cout << search(nums, 0) << endl;
	DWORD end = GetTickCount64();
	cout << (end-start) << " "<<"ms"<<endl;
	system("pause");
    return 0;
}

