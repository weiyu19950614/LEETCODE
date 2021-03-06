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

//将两个有序的链表合并成一个新的有序链表
//其实问题的难点在于不开辟新的空间
//遍历比较，感觉链表的算法基本都是线性的,20ms
ListNode* mergeTwoLists1(ListNode* l1, ListNode* l2) {
	ListNode* res=new ListNode(0);
	/*if (l1->val >= l2->val) { res = l2; res->next = l1; }
	else { res = l1; res->next = l2; }
	l1 = l1->next; l2 = l2->next;*/
	ListNode* result = res;
	//两者都非空的情况
	/*while (l1 != NULL&&l2 != NULL) {
		if ((l1->val) >= (l2->val)) { 
			res->next = l2; //注意当前res->next和l2的地址是一样的,所以下一步res->next->next = l1;会使得l2->next指向l1
			//解决办法有两个：1、给res开辟新的空间（不符合题目要求）2、利用已有节点
			l2 = l2->next;//先将l2往后推，如此一来修改res->next->next不会是修改l2->next
			res->next->next = l1; 
			l1=l1->next;
		}
		else { res->next = l1; res->next->next = l2; }
		//res = res->next->next;
		l1 = l1->next; 
		l2 = l2->next;
	}*/
	//不开辟新空间的关键就在于res不能两连跳
	while (l1 != NULL && l2 != NULL) {
		if (l1->val >= l2->val) {
			res->next = l2;
			l2 = l2->next;
		}
		else {
			res->next = l1;
			l1 = l1->next;
		}
		res = res->next;
	}
	//l1和l2当前值不是NULL意味着剩下来了还没有拼进res中
	while (l1 != NULL) {
		res->next = l1;
		res = res->next;
		l1 = l1->next;
	}

	while (l2 != NULL) {
		res->next = l2;
		res = res->next;
		l2 = l2->next;
	}
	res = result->next;
	return res;
}

//标准答案,28ms
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	ListNode *res = new ListNode(-1), *cur = res;
	while (l1 && l2) {
		if (l1->val <= l2->val) {
			cur->next = l1;
			cur = cur->next;
			l1 = l1->next;
		}
		else {
			cur->next = l2;
			cur = cur->next;
			l2 = l2->next;
		}
	}
	if (l1) {
		cur->next = l1;
	}
	if (l2) {
		cur->next = l2;
	}
	//标准答案快的地方在于后面其实根本不用在排序,只需要if语句把链接建立起来就行了，因为l后面的本身就是有序了
	return res->next;
}

int main()
{
	ListNode* l1 = new ListNode(1);
	l1->next = new ListNode(2);
	l1->next->next = new ListNode(4);
	l1->next->next->next = new ListNode(8);
	l1->next->next->next->next = new ListNode(9);
	ListNode* l2 = new ListNode(1);
	l2->next = new ListNode(3);
	l2->next->next = new ListNode(5);
	ListNode* res = mergeTwoLists(l1, l2);
	while (res) {
		cout << res->val << " ";
		res = res->next;
	}
	cout << endl;
	system("pause");
    return 0;
}

