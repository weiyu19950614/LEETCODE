// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
//三数之和找0

//全部遍历法是O(n³),可以利用盛水容器算法的思路 344ms
vector<vector<int>> threeSum2(vector<int>& nums) {
	//首先进行排序,排序算法最快O(n)二分法至少是O(nlogn)
	sort(nums.begin(), nums.end());//int排序,可以使用默认的排序方法
	/*for (auto &c : nums)
		cout << c << " ";
	cout << endl;*/
	size_t right = nums.size() - 1;
	size_t left = 0;
	size_t free = left + 1;
	vector<vector<int>> res = {};
	set<vector<int>> result;//避免重复
	//处理特殊情况
	if (nums.size()<3)
		return res;
	if (nums[right] < 0 || nums[left]>0)
		return res;

	while (left != right-1&&nums[left]<=0) {
		//cout <<left<<" "<< free<<" "<<right << " "<<endl;
		//free永远在left和right中间
		//就像调砝码平衡一样先移动free,如果free不行则改变两边砝码
		//free在极左或极右时可以调两边
		//关键问题在于出现变号的时候应该怎么处理
		//以left为基准,每次调整left的时候right要回去
		//让free一直往右走,那么一定不会出现由大于0变成小于0的情况,所以变号问题非常简单只可能从小于变成相等或者大于
		if ((nums[left] + nums[right] + nums[free]) > 0) {
			//cout << "test" << endl;
			if (free == right - 1) {
				++left;
				free = left + 1;
				right = nums.size() - 1;
			}
			else {
				--right;
			}
		}
		else if ((nums[left] + nums[right] + nums[free] < 0)) {
			//cout << "test1" << endl;
			if (free == right-1) {
				++left;
				free = left + 1;
				right= nums.size() - 1;//回调右侧,避免缺漏
			}
			else {
				++free;
			}
		}
		else {
			//调回原始状态
			//cout << "test2" << endl;
			result.insert({ nums[left],nums[free],nums[right] });
			if (free == right - 1) {
				++left;
				free = left + 1;
				right = nums.size() - 1;
			}
			else {
				--right;
			}
		}
	}
	if (result.empty())
		return res;
	for (const vector<int> &c : result) {
		res.push_back(c);
	}
	return res;
}

//遍历法,会超出时间限制
vector<vector<int>>threeSum1(vector<int>&nums) {
	size_t n = nums.size();
	set<vector<int>> result;
	vector<vector<int>>res = {};
	if (nums.size()<3)
		return res;
	for (size_t i = 0; i != n-2; ++i) {
		for (size_t j =i + 1; j != n-1; ++j) {
			for (size_t z =j+1; z != n; ++z) {		
				if (nums[i] + nums[j] + nums[z] == 0) {
					vector<int> v = { nums[i],nums[j],nums[z] };
					sort(v.begin(), v.end());
					result.insert(v);
				}
			}
		}
	}
	if (result.empty())
		return res;
	for (const vector<int> &c : result) {
		res.push_back(c);
	}
	return res;
}

//标准答案,76 ms
vector<vector<int>> threeSum(vector<int>& nums) {
	vector<vector<int>> res;
	sort(nums.begin(), nums.end());//思路一样，先排序
	if (nums.empty() || nums.back() < 0 || nums.front() > 0) return {};
	for (int k = 0; k < nums.size(); ++k) {//同样是以left为基准
		if (nums[k] > 0) break;
		if (k > 0 && nums[k] == nums[k - 1]) continue;//left相等直接推进,这里比我省时间了
		int target = 0 - nums[k];//构建一个差额
		int i = k + 1, j = nums.size() - 1;//free是i,j是right这里思路一样，每次推进left都让right回去
		while (i < j) {
			if (nums[i] + nums[j] == target) {//找到的情况下
				res.push_back({ nums[k], nums[i], nums[j] });//放进去
				while (i < j && nums[i] == nums[i + 1]) ++i;//遇到重复的free可以直接推进,省时间的地方
				while (i < j && nums[j] == nums[j - 1]) --j;//.....
				++i; --j;//继续检索,出现相等我没有处理好,其实可以动free的,主要是我对于重复的问题没有解决
			}
			else if (nums[i] + nums[j] < target) ++i;//偏小要移动i <0 ++free
			else --j;//偏大移动j，>0 --right
		}//总结：我的问题有两点：1、重复的没有推进 2、没有把left独立出来看,所以思路没有理清right的移动写复杂了
	}
	return res;
}

int main()
{
	//vector<int> nums = { -1,0,1,2,-1,-4 };//[-1 -1 2] [1 0 -1]
	//vector<int> nums = { 0,1,1};
	//vector<int> nums = {};
	//vector<int> nums = { 0,1};
	//vector<int> nums = { 3,0,-2,-1,1,2};//[-2 -1 3] [-2 0 2] [-1 0 1]
	//vector<int> nums = { 0};
	//vector<int> nums = {1,2,-2,1};//[-2 1 1]
	//vector<int> nums = { -4,-2,-1,1,2,4 };//不返回，检测是否死循环
	//vector<int> nums = { -4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6 };//[[-4,-2,6],[-4,0,4],[-4,1,3],[-4,2,2],[-2,-2,4],[-2,0,2]]//检测是否会错过
	vector<int> nums = { -4, -2, 1, -5, -4, -4, 4, -2, 0, 4, 0, -2, 3, 1, -5, 0 }; //[[-5, 1, 4], [-4, 0, 4], [-4, 1, 3], [-2, -2, 4], [-2, 1, 1], [0, 0, 0]]
	/*sort(nums.begin(),nums.end());
	for (int &c : nums) {
		cout << c << " ";
	}
	cout << endl;*/
	vector<vector<int>> v = threeSum(nums);
	for (const vector<int> & c : v) {
		for (const int & c1 : c) {
			cout << c1 << " ";
		}
		cout << endl;
	}
	system("pause");
    return 0;
}

