// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

//定义链表数据结构,C++没有自带的链表
//易于控制,但访问困难
//有两个难点：1、链表怎么逆序（与数组不同，地址不连续）；2、想加进位怎么处理

struct ListNode {
	int val;//数据成员,当前对象存储的整数
	ListNode *next;//数据成员,ListNode类型的指针,用于指向下一个对象
	ListNode(int x) : val(x), next(NULL) {}//构造函数,默认指向空,在创建节点的时候会隐式的使用
	
};

//化成整数在相加是取巧的方法 39999999+7就不行,会超出整数范围
ListNode* addTwoNumbers1(ListNode* l1, ListNode* l2) {
	int a = l1->val, b = l2->val;
	while (l1->next != NULL) {
		a = a * 10 + l1->next->val;
		l1 = l1->next;
	}
	while (l2->next != NULL) {
		b = b * 10 + l2->next->val;
		l2 = l2->next;
	}
	int c = a + b;
	ListNode* result=new ListNode(c%10);
	c /= 10;
	ListNode* res = result;//记住当前位置
	while (c != 0) {
		result->next = new ListNode(c % 10);
		c /= 10;
		result = result->next;
	}
	return res;
}
//96ms
ListNode* addTwoNumbers2(ListNode* l1, ListNode* l2) {
	int a = l1->val, b = l2->val;
	ListNode* result = new ListNode((a + b)%10);
	int passten = 0;
	if (a + b > 9) passten = 1;
	ListNode* res = result;
	while (l1->next != NULL&&l2->next != NULL) {
		a = l1->next->val;
		b = l2->next->val;
		int c = 0;
		//cout << passten << endl;
		//cout << a << " " << b << " " << endl;
		if (passten == 0) c = a + b;
		else c = a + b + 1;
		if (c > 9) passten = 1;
		else passten = 0;
		//cout << c << " " << c % 10 << endl;
		result->next = new ListNode(c%10);
		l1 = l1->next;
		l2 = l2->next;
		result = result->next;
	}
	while (l1->next != NULL) {
		if (passten == 1) { 
			l1->next->val += 1; 
			//相加为10的情况
			if (l1->next->val == 10) {
				l1->next->val = 0;
				passten = 1;
			}
			else {
				passten = 0;
			}
		 }
		result->next = new ListNode(l1->next->val);
		l1 = l1->next;
		result = result->next;
	}
	while (l2->next != NULL) {
		if (passten == 1) { 
			l2->next->val += 1; 
			passten = 0;
			if (l2->next->val == 10) {
				l2->next->val = 0;
				passten = 1;
			}
			else {
				passten = 0;
			}
		}
		result->next = new ListNode(l2->next->val);
		l2 = l2->next;
		result = result->next;
	}
	//最后一位相加大于10,且二者都没有位了
	if (passten == 1) { result->next=new ListNode(1); passten = 0; }
	return res;
}

//标准答案,68ms
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	bool UpFlag = false;//0、1判断是否进位，这里思路一样
	ListNode *Ret = NULL;
	int TempResult = 0;

	TempResult = l1->val + l2->val;//用来表示每一个当前和

	if (TempResult >= 10) {
		UpFlag = true;
		Ret = new ListNode(TempResult - 10);
	}
	else {
		UpFlag = false;
		Ret = new ListNode(TempResult);
	}

	ListNode *pTemp = Ret;//保存当前地址
	l1 = l1->next;
	l2 = l2->next;

	while ((l1 != NULL) && (l2 != NULL)) {
		if (UpFlag) {
			TempResult = l1->val + l2->val + 1;
		}
		else {
			TempResult = l1->val + l2->val;
		}

		if (TempResult >= 10) {
			pTemp->next = new ListNode(TempResult - 10);
			UpFlag = true;
		}
		else {
			pTemp->next = new ListNode(TempResult);
			UpFlag = false;
		}

		l1 = l1->next;
		l2 = l2->next;
		pTemp = pTemp->next;
	}
	//之前的思路都一样，处理两者都不为NULL的情况
	//检测l1是否为空,然而我感觉我while的检测就很简洁
	ListNode *l3 = l1;
	if (l3 == NULL) {
		l3 = l2;
	}

	while (l3 != NULL) {
		if (UpFlag) {
			TempResult = l3->val + 1;
		}
		else {
			TempResult = l3->val;
		}

		if (TempResult >= 10) {
			pTemp->next = new ListNode(TempResult - 10);
			UpFlag = true;
		}
		else {
			pTemp->next = new ListNode(TempResult);
			UpFlag = false;
		}

		l3 = l3->next;
		pTemp = pTemp->next;
	}
	//两者都没有下一位然而还是有进位
	if (UpFlag) {
		pTemp->next = new ListNode(1);
	}

	return Ret;
}//整体思路完全一样。。。不知道为什么标准答案是68ms

int main()
{
	//建立题目要求的链表
	/*ListNode *l2=new ListNode(5);//动态分配一个对象给该类型指针//先创建对象在取地址也是可以的
	l2->next = new ListNode(6);//给下一个赋值
	l2->next->next = new ListNode(4);
	ListNode *l1 = new ListNode(2);
	l1->next = new ListNode(4);
	l1->next->next = new ListNode(3);
	l1->next->next->next = new ListNode(3);
	l1->next->next->next->next = new ListNode(3);
	l1->next->next->next->next->next = new ListNode(3);
	l1->next->next->next->next->next->next = new ListNode(3);
	l1->next->next->next->next->next->next->next = new ListNode(3);*/
	ListNode *l1 = new ListNode(5);
	ListNode *l2 = new ListNode(5);
	//cout <<l1<<" "<< l1->val<<" "<<l1->next->val<<" " <<l1->next->next<< endl;//测试部分,->等价于(*).//链表地址是不连续的
	//测试部分，逆序访问
	/*ListNode *p = l1;
	int a = p->val;
	while (p->next != NULL) {
		a = a * 10 + p->next->val;
		p = p->next;
	}
	cout << a<<endl;*/
	//cout << 8 % 10 << endl;
	ListNode *r=addTwoNumbers(l1, l2);
	cout << r->val << " ";
	while (r->next != NULL) {
		cout << r->next->val << " ";
		r = r->next;
	}
	cout << endl;
	system("pause");
    return 0;
}

