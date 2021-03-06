// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//四数之和，可以在三数之后的基础上遍历(因为之前是找0所以要去掉一些条件,变成普遍的找数字）
//84ms
//标准答案36ms
vector<vector<int>> threeSum(vector<int>& nums,int t) {
	vector<vector<int>> res;
	sort(nums.begin(), nums.end());//思路一样，先排序
	for (int k = 0; k < nums.size(); ++k) {//同样是以left为基准
		int target = t - nums[k];//构建一个差额
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

vector<vector<int>> fourSum1(vector<int>& nums, int target) {
	if (nums.size() < 3)return {};
	int nt = 0;
	vector<int> nn = {};
	vector<vector<int>> res = {};
	vector<vector<int>> result = {};
	for (size_t i = 0; i != nums.size()-3; ++i) {
		nt = target - nums[i];
		//cout << nt << endl;
		nn = nums;
		nn.erase(nn.begin(),nn.begin() + i+1);
		/*for (auto c : nn) {
			cout << c << " ";
		}
		cout << endl;*/
		res = threeSum(nn, nt);
		for (vector<int> & c : res) {//引用改变res
			c.push_back(nums[i]);
			/*for (auto d : c) {
				cout << d << " ";
			}
			cout << endl;*/
		}
		result.insert(result.end(), res.begin(),res.end());
	}
	//处理重复的
	for (vector<int> & c : result) {
		sort(c.begin(), c.end());
	}
	for (int i = 0; i != result.size(); ++i) {
		for (int j = i + 1; j != result.size(); ++j) {
			if (result[i] == result[j]) {
				result.erase(result.begin() + j);
				--j;
			}
		}
	}
	return result;
}

//在三数之和的基础上求四数,改进版本，68ms
vector<vector<int>> fourSum2(vector<int>& nums, int target) {
	if (nums.size() < 3)return {};
	vector<vector<int>> res;
	sort(nums.begin(), nums.end());//先排序避免在找三的时候还要排序
	for (size_t i = 0; i != nums.size() - 3; ++i) {
		if (i>0&&nums[i] == nums[i - 1]) continue;//避免重复,相同的看作一个就行了
		if (nums[i]>0&&target < nums[i]) return res;//已经超过了没必要往后检查,nums[i]>0确保在往上加是增大而不是减小
		for (int j = i + 1; j != nums.size() - 2; ++j) {//j是三数之和的目标值
			if (j>i+1&&nums[j] == nums[j - 1]) continue;//避免重复,也避免略掉和i相同
			if (nums[i]+nums[j]>0&&target < nums[i]+nums[j]) break;//j已经没必要加了,检查下一个i,大于0是确保往后是增大而不是减小
			int left = j + 1, right = nums.size() - 1;//开始三数之和的检索
			while (left < right) {
				if (nums[i] + nums[j]+nums[left]+nums[right] == target) {//找到的情况下
					res.push_back({ nums[i], nums[j], nums[left],nums[right] });
					while (left < right && nums[left] == nums[left + 1]) ++left;//避免重复
					while (left < right && nums[right] == nums[right - 1]) --right;
					++left; --right;//继续找
				}
				else if (nums[i] + nums[j]+nums[left]+nums[right] < target) ++left;
				else --right;
			}
		}
	}
	return res;
}

//标准答案,36ms
vector<vector<int>> fourSum(vector<int>& nums, int target) {
	vector<vector<int>> res;
	int n = nums.size();
	if (n < 4) return res;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < n - 3; i++)
	{
		if (i > 0 && nums[i] == nums[i - 1])
		{
			continue;
		}//以上思路一致
		if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
		{
			break;
		}//这里是当前的最小和，如果最小和都已经大过target就不用在往下加了
		if (nums[i] + nums[n - 1] + nums[n - 2] + nums[n - 3] < target)
		{
			continue;
		}//最大的和还比target小，需要移动i
		for (int j = i + 1; j < n - 2; j++)//对j的处理是和i一样，这里我们想到一起了
		{
			if (j > i + 1 && nums[j] == nums[j - 1])//用i+1避免重复
			{
				continue;
			}
			if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
			{
				break;
			}
			if (nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target)
			{
				continue;
			}
			int left = j + 1;
			int right = n - 1;
			while (left < right)
			{
				if (nums[i] + nums[j] + nums[left] + nums[right] < target)
				{
					left++;
				}
				else if (nums[i] + nums[j] + nums[left] + nums[right] > target)
				{
					right--;
				}
				else {
					res.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
					do {
						left++;
					} while (left < right && nums[left] == nums[left - 1]);
					do {
						right--;
					} while (left < right && nums[right] == nums[right + 1]);
				}
			}
		}
	}//总结：唯一差距就是最小和和最大和的条件我没有写
	return res;
}
int main()
{
	//vector<int> nums = { 1,0,-1,0,-2,2 };//原始测试,target 0
	//vector<int> nums = {};//空集测试,0
	//vector<int> nums = { 5,5,3,5,1,-5,1,-2 };//重复测试,4
	//vector<int> nums = { 0,4,-5,2,-2,4,2,-1,4 };//测试,target 12,会不会略过.ij往回比往前推可以避免
	//vector<int> nums = { -493, -470, -464, -453, -451, -446, -445, -407, -406, -393, -328, -312, -307, -303, -259, -253, -252, -243, -221, -193, -126, -126, -122, -117, -106, -105, -101, -71, -20, -12, 3, 4, 20, 20, 54, 84, 98, 111, 148, 149, 152, 171, 175, 176, 211, 218, 227, 331, 352, 389, 410, 420, 448, 485 };//1057
	//vector<int> nums = { 84, 98, 111, 148, 149, 152, 171, 175, 176, 211, 218, 227, 331, 352, 389, 410, 420, 448, 485 };//1057,这个检测有没有去掉条件
	//vector<int> nums = { -1,0,1,2,-1,-4};//测试ij(第一和第二数字）相同会不会被略掉,target -1
	//vector<int> nums = { 1,-2,-5,-4,-3,3,3,5};//break和continue测试,target -11
	vector<int> nums = { -5,-5,-3,-1,0,2,4,5};//重复测试,target -11
	/*nums.erase(nums.begin(), nums.begin() + 2);
	cout << nums[0] << endl;*/
	vector<vector<int>> result = fourSum(nums, -11);
	for (vector<int> c : result) {//拷贝输出不改变result
		for (int d : c) {
			cout << d << " ";
		}
		cout << endl;
	}
	system("pause");
    return 0;
}

