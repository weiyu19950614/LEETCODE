// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

//给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。需要实际的节点交换
//不需要考虑复杂度线性时间,利用中间变量记录地址
//难点在于交换后怎么和前一组建立联系
//解决方案采取在移动head前记录它的地址
//8ms
ListNode* swapPairs1(ListNode* head) {
	ListNode* temp = NULL;
	ListNode* res = new ListNode(0);
	res->next = head;
	ListNode* front = res;
	while (head != NULL&&head->next!=NULL) {//防止出现单数情况
		temp = head->next;
		head->next = head->next->next;
		temp->next = head;
		front->next = temp;
		front = head;
		head = head->next;
	}
	res = res->next;
	return res;
}

//标准答案52ms
ListNode* swapPairs(ListNode* head) {
	if (!head) return NULL;
	if (!head->next) return head;
	ListNode res(-1);
	res.next = head;
	ListNode* last = &res;//相当于front,因为是对象所以要取地址
	ListNode* cur = head;
	while (cur && cur->next) {
		ListNode* tmp = cur->next->next;//中间变量记录的是第三位地址
		last->next = cur->next;//front指向第二个的地址，这里其实没有必要啊？->有必要的相当于建立0和2的链接，它这里叫last也就是上一组的最后一个，建立和下一组的联系
		last = cur;//front变成head,第一个，一起变化
		cur->next->next = cur;//指向第三个变成指向自己，即第二个指向第一个
		cur->next = tmp;//第一个指向第三个，完成了交换
		cur = tmp;//head变成第三个，即没有交换的第一个
	}
	return res.next;//不用调整res=res->next，反正返回的是地址
}


int main()
{
	ListNode* head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	ListNode* res = swapPairs(head);
	while (res) {
		cout << res->val << " ";
		res = res->next;
	}
	cout << endl;
	system("pause");
    return 0;
}

