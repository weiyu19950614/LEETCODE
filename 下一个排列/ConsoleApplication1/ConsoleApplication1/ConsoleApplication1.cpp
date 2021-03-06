// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<queue>
#include<functional>//greater在functional里,less自带（a<b)
#include<forward_list>//先进的后出，可以访问尾端和前端，但是只能删除前端，当然它可以支持反向，但是操作也变多了
#include<list>//双端队列，前访问后访问都可以
using namespace std;

//将给定序列变成下一个更大的序列
//只能原地修改，使用额外常数空间
//算法逻辑：下一个更大就要求我们尽可能的维持原数列，因此从后往前找到第一个递减对，交换它们的顺序之后，从该位置开始要把之后的顺序变成升序
//方法一：利用额外空间，利用容器接收出来的值
//在找到第一个递减对之前的元素都是顺序的，但是递减对缓过来要加入排序，因此使用priority_queue先进先出(利用标准库的话每次加入元素都排序用时nlogn,本来可以只是logn的)
//链表的next指向自己那么每次进来都是下一个是上一个点意味着后进先出
//不如自己写一个插入排序了，利用vector
//失误一：思路错了，下一个并不是第一个递减对，而是在另一个容器里出现比当前值大的数，但是发生的地点确实是出现第一个递减对的时候
void nextPermutation1(vector<int>& nums) {
	if (nums.size() == 0 || nums.size() == 1) return;
	vector<int> v = {};
	int temp = 0,temp1 = 0;
	int last = nums.size() - 1;
	for (; last != 0; --last) {
		if (nums[last] > nums[last - 1]) {
			//nums.swap()//是交换容器内容的，里面接收容器对象名字
			//出现了第一个递减对
			temp = nums[last]; temp1 = nums[last - 1];
			nums.pop_back();
			break;
		}
		else {
			v.push_back(nums[last]);
			nums.pop_back();
		}
	}
	//第一组就递减的情况
	if (v.empty()) {
		nums[last - 1] = temp; nums.push_back(temp1); return;
	}
	//将temp插入v中
	//如果nums是完全逆序
	if (last == 0) {
		v.push_back(nums[last]);
		nums.pop_back();
		int n = v.size();
		for (int i = 0; i != n; ++i) {
			nums.push_back(v[i]);
		}
		return;
	}
	else {
		nums.pop_back();
		int n = v.size();
		int nn = nums.size();
		//在有序的v中找到第一个比temp1大的
		//可以改成二分查找能够更快
		for (int i = 0; i != n; ++i) {
			if (v[i] > temp1) {
				nums.push_back(v[i]);
				v[i] = temp1;
				break;
			}
		}
		//如果没有找到
		if (nn == nums.size()) {
			nums.push_back(temp); temp=temp1;
		}
		int mid = n / 2; int mid_right = n; int mid_left = 0;
		//先考虑最大和最小的情况
		if (temp <= v[0]) {
			nums.push_back(temp);
			for (int i = 0; i != n; ++i) {
				nums.push_back(v[i]);
			}
			return;
		}
		if (temp >= v[n - 1]) {
			for (int i = 0; i != n; ++i) {
				nums.push_back(v[i]);
			}
			nums.push_back(temp);
			return;
		}
		while (!(v[mid] <= temp && temp <= v[mid+1])) {
			if (v[mid] < temp) { mid_left = mid; mid = (mid + mid_right) / 2; }
			else { mid_right = mid; mid = (mid+mid_left) / 2; }
		}
		v.insert(v.begin() + mid+1, temp);//插入是在迭代器指向的位置之前插入
		n = v.size();
		for (int i = 0; i != n; ++i) {
			nums.push_back(v[i]);
		}
	}
}

//思路二：不用开辟新的容器直接操作，利用两个指针
void nextPermutation(vector<int>& nums) {
	if (nums.size() == 0 || nums.size() == 1) return;
	int temp = 0;
	int n = nums.size();
	int last = n - 1;
	int last_f = last - 1;
	for (; last != 0; --last,--last_f) {
		if (nums[last] > nums[last_f]) {
			temp = nums[last];
			break;
		}
	}
	if (last != 0) {
		//一定有比最后一个数大的数
		last = n-1 ;
		for (; last != last_f; --last) {
			if (nums[last] > nums[last_f]) {
				temp = nums[last_f];
				nums[last_f] = nums[last];
				nums[last]= temp;
				break;
			}
		}
		last = n-1;
		last_f++;
		while (last > last_f) {
			temp = nums[last];
			nums[last] = nums[last_f];
			nums[last_f] = temp;
			++last_f; --last;
		}
	}
	else {
		last = n - 1;
		last_f++;
		while (last > last_f) {
			temp = nums[last];
			nums[last] = nums[last_f];
			nums[last_f] = temp;
			++last_f; --last;
		}
	}
}

//和标准答案思路一模一样,只是标准答案在排序过程中直接用sort，全部反向用的是reverse

int main()
{
	vector<int> nums = { 2 };//132答案是213；123758743应该是123773458而不是123783457;测试115、123、321、1、12、227543221
	nextPermutation(nums);
	for (int c : nums) {
		cout << c << " ";
	}
	cout << endl;
	/*priority_queue<int,vector<int>,greater<int>> qe = {};
	for (int c : nums) {
		qe.push(c);
	}
	while (!qe.empty()) {
		cout << qe.top() << " ";
		qe.pop();
	}*/
	/*forward_list<int> fl = {};
	for (int c : nums) {
		fl.push_front(c);
	}
	fl.reverse();
	while (!fl.empty()) {
		cout << fl.front() << " ";
		fl.pop_front();
	}*/
	/*int i[] = { 1,2,3 };
	cout << size(i) << endl;//size_of是内存空间*/
	system("pause");
    return 0;
}

