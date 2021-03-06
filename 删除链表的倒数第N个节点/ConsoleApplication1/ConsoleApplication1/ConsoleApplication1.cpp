// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
//链表数据结构
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
//逆序删除第n个节点,返回链表的头节点
//有两种思路，核心思想都是逆序变为顺序：1、先统计整个链表的长度,然后算出顺序第几个删除(比如长度5，倒数第2个，就删除掉第4个）
//2、直接算逆序的,比如倒数第二个p->next->next==NULL时p就是倒数第二个节点
//方法1，16ms，官方叫法叫两次遍历算法O（L）（利用一个指针）
ListNode* removeNthFromEnd1(ListNode* head, int n) {
	ListNode *res = head;//保存头节点
	int Length = 0;
	while (head != NULL) {
		Length += 1;
		head = head->next;
	}
	if (n > Length)return res;
	else if (n == Length) {
		//删掉头节点
		res = res->next;
		return res;
	}
	head = res;//从头开始往下找寻
	for (int i = 0; i != Length - n-1; ++i) {//删除必须找到要删除的前一个,必须修改数据成员的值
		head = head->next;
	}
	head->next = head->next->next;
	return res;
}
//标准答案24ms，思路和方法二一致，官方名称叫一次遍历算法O（L）（利用两个指针）
ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode* h = new ListNode(0);
	h->next = head;//在头节点上游创建一个新的节点
	ListNode* p = head;
	ListNode* q = h;
	//p、q是为了方便表达了
	while (n--) {//将p往前推n
		p = p->next;
	}
	while (p) {//p还不是空的时候
		p = p->next;
		q = q->next;
	}
	q->next = q->next->next;
	return h->next;
}
int main()
{
	ListNode* head = new ListNode(1);
	/*head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(5);*/
	head=removeNthFromEnd(head, 1);
	while (head != NULL) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
	system("pause");
    return 0;
}

