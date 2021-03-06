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
//K个节点一组进行链表翻转,最后一组不足K不翻转
//难点一在于最后不足k个的要保持顺序，解决方案是建立一个判断指针先走k步
//难点二在于不同组直接怎么建立联系，可以利用判断指针
//第一组的头地址怎么返回来
//思路：利用三个指针推进
//特殊情况,k<=1或者链表为空或者k大于节点数(题目规定k大于长度是返回原来的样子。。。）
//44ms
ListNode* reverseKGroup1(ListNode* head, int k) {
	if (head == NULL) return NULL;
	if (k == 1) return head;
	ListNode* p = new ListNode(0);
	ListNode* x = new ListNode(0);//每一组的末尾
	ListNode* y = head;//每一组的开头
	ListNode* z = head->next;//每一组的第二个
	p->next = head;
	ListNode* res = p;
	bool once = true;
	while (p != NULL) {
		//判断当前能否做逆序操作
		for (int i = 0; i != k; ++i) {
			if (p == NULL) break;
			p = p->next;
		}
		/*if (p == NULL && once == true) {//逆序了不应该
			//k大于节点数
			x = NULL;
			while (y != NULL) {
				z = y->next; y->next = x; x = y; y = z;
			}
			return x;
		}*/
		if (p == NULL) {//最后已经不足以逆序了
			x->next = y;//上一组直接和后面链接即可
			break;
		}
		x->next = p;//上一组的尾端指向下一组的头端（经过逆序的）
		//对当前组进行逆序操作
		for (int i = 0; i != k-1; ++i) {
			x = z->next; z->next = y; y = z; z = x;
		}
		if (once) { res = p; once = false; }//第一次的逆序是整个表头
		//建立组间联系，p现在是当前组头地址，先将p移动到尾地址
		for (int i = 0; i != k - 1; ++i) {
			p = p->next;
		}
		//p指向未经逆序的下一组
		x = p;//x和z进入下一组了因此要把它返回上一组尾端
		p->next = z;
		y = z;//y在上一组头部应该放到下一组的开始
		if(z!=NULL) z = z->next;//避免正好走到NULL了
	}
	if (once == true) return head;//完全没交换过,k大于链表长度
	return res;
}


//标准答案,32ms
ListNode*& reverseSingle(ListNode*& head, int k)//将链表整个逆序，返回最后一个节点，该节点指向NULL
{
	ListNode* p = head;//相当于y
	ListNode* m = head->next;//相当于z
	ListNode* q = m->next;//直接把x放到z后面

	while (--k)
	{
		m->next = p;
		if (nullptr == q) break;
		p = m;
		m = q;
		q = q->next;
	}
	head->next = nullptr;
	return head;
}
ListNode* reverseKGroup(ListNode* head, int k)
{
	if (1 == k || nullptr == head) return head;//k=1和空指针的特殊情况
	ListNode* pp = head;
	for (int i = 1; i < k; i++)
	{
		pp = pp->next;
		if (!pp) return head;//找到第一组最后一个，若最后一个是NULL（k比链表长）返回链表
	}
	ListNode* p = head;
	ListNode* re = head;
	ListNode* tt = head;
	bool isBreak = false;//判断是否将这个链表遍历完
	for (int i = 1; i < k; i++)
	{
		re = re->next;//找到第一组最后一个，即答案链表的首节点
	}
	while (p)
	{
		ListNode* q = p;//每次创建一个q记录当前组第一个地址
		for (int i = 0; i < k; i++)
		{
			if (!p)//如果p遍历完整个链表了
			{
				isBreak = true;
				break;//结束
			}
			p = p->next;//推进至下一组第一个
		}
		if (isBreak)//在遍历完的情况下（即最后一组不足k个）
		{
			tt->next = q;//顺序链接，调整最后一组链接的不是最后一个
			break;
		}
		ListNode* temp = p;//每次创建一个temp记录当前组最后一个地址的下一个地址（下一组的第一个地址）
		for (int i = 1; i < k; i++)
		{
			if (nullptr == temp) break;//当前组的下一组（最后一组）不足k个（即下一轮循环，p会遍历的最后一组）
			temp = temp->next;//推进至下一组的最后一个，用以解决组和组相连接的问题
		}
		tt = reverseSingle(q, k);//调用函数将当前k个逆序，返回的是当前组最后一个节点
		tt->next = temp;//当前组指向下一组最后一个，完成链接（有可能最后一组不足k个时tt这时候逆序链接是错的，但是在p遍历完后有一个tt调整）
	}
	return re;
}
//区别在于答案的p已经到下一组了，没必要再通过链接往后走（算法复杂度本身来说一样）


int main()
{
	ListNode* l = new ListNode(1);
	l->next = new ListNode(2);
	l->next->next = new ListNode(3);
	l->next->next->next = new ListNode(4);
	l->next->next->next->next = new ListNode(5);
	ListNode* res = reverseKGroup(l, 2);
	while (res != NULL) {
		cout << res->val << " ";
		res = res->next;
	}
	cout << endl;
	system("pause");
    return 0;
}

