// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;


int main()
{
	vector<int> nums1 = { 1,2 };
	vector<int> nums2 = { 3,4 };
	double Mid;
	nums2.insert(nums2.begin(), nums1.begin(), nums1.end());
	sort(nums2.begin(), nums2.end());
	for (auto c : nums2)
		cout << c << " ";
	cout << endl;
	if ((nums2.size() % 2)) {
		Mid = nums2[nums2.size() / 2 ]*1.0;
	}
	else{
		Mid = ((nums2[nums2.size() / 2]*1.0 + nums2[nums2.size() / 2 - 1]*1.0) / 2);
	}
	cout << Mid<< endl;
	system("pause");
    return 0;
}

