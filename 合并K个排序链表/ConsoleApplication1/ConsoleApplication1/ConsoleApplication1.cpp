// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<queue>
using namespace std;


struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

//合并k个有序链表，返回合并后的有序链表
//思路：对容器内的所有链表顺序检查，当前节点找到最小值，然后将最小值的节点向后推进,复杂度：每次检索n个找到1个,如果n+1个链表有n个节点，找到一个点要遍历n次，O（n3）
//难点在于不确定链表的数量并且需要多个链表循环比较
//解决方案：lists.size()可以确定出有多少个链表，那么比较次数是size-1；->循环次数得到了确定
//比较方案可以利用lambda函数避免再写一个比较函数
//失败一：没有考虑特殊情况，即lists中有空指针（空节点）
//结果：复杂度太高768MS
ListNode* mergeKLists1(vector<ListNode*>& lists) {
	if (lists.size() == 0) return NULL;
	ListNode* result = new ListNode(0);
	ListNode* res = result;
	int min = 0,index=0;//记录当前的最小值和对应的索引
	auto f = [](int a, int b)->int {if (a < b)return a; else return b; };//定义lambda函数比较小值
	while (lists.size() > 1) {//大于1是避免出现有1个链表非常长的情况
		if (lists[0] == NULL) {
			lists.erase(lists.begin() + 0); continue;
		}//特殊情况处理
		min = lists[0]->val;//每次开始遍历比较前都要更新min
		for (size_t i = 0; i !=lists.size(); ++i) {
			if (lists[i] == NULL) { lists.erase(lists.begin() + i); --i; continue; }//特殊情况处理,当是空指针时i要往回
			min = f(lists[i]->val, min);
			if (min == lists[i]->val) index = i;//表明发生了更换
		}
		result->next = lists[index];
		result = result->next;
		lists[index] = lists[index]->next;
		if (lists[index] == NULL) lists.erase(lists.begin() + index);//推进到头可以删除了
	}
	result->next = lists[0];
	return res->next;
}

//思路2：基于两两合并的基础  312ms 假设有n+1个指针，每个链表n个节点，第一次n+n，第二次2n+n。。。第n次n2+n=O（n3）+O（n2）其实和思路1的时间量级是一样的（都是基于每个点重复遍历）
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

ListNode* mergeKLists2(vector<ListNode*>& lists) {
	//处理特殊情况
	if (lists.size() == 0) return NULL;
	if (lists.size() == 1 && lists[0] == NULL) return NULL;
	if (lists.size() == 1) return lists[0];
	//之后保证至少有两个可以合并，空指针在合并函数已经处理了
	ListNode* result = new ListNode(0);
	result = mergeTwoLists(lists[0], lists[1]);//容器中保存着头节点,合并后还是在的，只是指向的下一个不一定和原来一致
	for (size_t i = 2; i != lists.size(); ++i) {
		result = mergeTwoLists(result, lists[i]);
	}
	return result;
}

//思路3路人答案
void adjust(vector<int> &root, vector<ListNode*> &t, int n, int s) {
	int q = (n + s) / 2;
	int tmp;
	while (q != 0) {
		if (s == -1) {
			break;
		}
		if (root[q] == -1 || t[s]->val > t[root[q]]->val) {
			tmp = s;
			s = root[q];
			root[q] = tmp;
		}
		q /= 2;
	}
	root[0] = s;
}

void createLoserTree(vector<int> &root, vector<ListNode*> &t, int n) {
	for (int i = n - 1; i >= 0; i--) {
		adjust(root, t, n, i);
	}
}

ListNode* mergeKLists3(vector<ListNode*>& lists) {
	int n = lists.size();
	if (n == 0)    return NULL;
	vector<ListNode*> t;
	for (int i = n - 1; i >= 0; i--) {
		if (lists[i] != NULL) {
			t.push_back(lists[i]);
		}
		else {
			n--;
		}
	}
	ListNode* ans = new ListNode(0);
	ListNode* p = ans;
	vector<int> loserTree(n, -1);
	createLoserTree(loserTree, t, n);
	int live_runs = n;
	ListNode* max = new ListNode(INT_MAX);
	while (live_runs > 0) {
		int winner = loserTree[0];
		p->next = t[winner];
		p = p->next;
		if (t[winner]->next != NULL) {
			t[winner] = t[winner]->next;
		}
		else {
			t[winner] = max;
			live_runs--;
		}
		adjust(loserTree, t, n, winner);
	}
	return ans->next;
}

//标准答案基于两两合并，40ms
//两两合并函数
/*ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	if (!l1) return l2;
	if (!l2) return l1;
	ListNode res(-1);
	ListNode *cur = &res;
	while (l1 && l2) {
		if (l1->val < l2->val) {
			cur->next = l1;
			cur = l1;
			l1 = l1->next;
		}
		else {
			cur->next = l2;
			cur = l2;
			l2 = l2->next;
		}
	}
	if (l1)
		cur->next = l1;
	else
		cur->next = l2;
	return res.next;
}*/
//这个函数就是我的思路,但是这样很慢，所以标准答案换了一个思路（下一个函数
ListNode* mergeKLists000(vector<ListNode*>& lists) {
	int len = lists.size();
	if (len == 0) return NULL;
	if (len == 1) return lists[0];
	ListNode* res = lists[0];
	for (int i = 1; i<len; i++) {
		res = mergeTwoLists(res, lists[i]);
	}//合并好的和下一个合并
	return res;
}

//不是按顺序合并下去，跳着合并
ListNode* mergeKLists4(vector<ListNode*>&lists)
{//类似合并排序
	if (lists.size() == 0)return NULL;
	int length = lists.size();
	int interval = 1;
	while (interval<length)
	{
		for (int i = 0; i<length - interval; i += interval * 2)
		{
			lists[i] = mergeTwoLists(lists[i], lists[i + interval]);//跳着合并，例如有5个指针，i=0\2结束，即0和1合并 2和3 合并 剩4第一次while；第二次while，0和2合并；第三次while0和4合并
		}
		interval *= 2;//interval=1\2\4
	}
	return lists[0];
}
//为什么跳着合并比顺序合并快？这是因为分治算法，类似于2分法；假设n=2N，第一次N组2n次，第二次N/2组，4n次，每次消耗都是n2，总共的次数lg2n，因此O（n2lgn）大大减少了次数



//标准答案2，58ms
//定义了一个类priority
class priority {
public:
	//给类定义了一个函数调用运算符用于比较指针大小，小的放顶堆
	bool operator () (ListNode* a, ListNode* b) {
		//接收两个链表
		if (a == NULL)
			return false;
		else if (b == NULL)
			return true;
		else
			return a->val>b->val;//如果a当前节点的值大于b当前节点的值返回真，因此a空一定假b空一定真
	}
};
ListNode* mergeKLists5(vector<ListNode*>& lists) {
	if (lists.empty())
		return NULL;
	//模板中三个参数的意义：第一个是队列里的数据类型，第二个是保存数据的容器，第三个是比较方式//一般默认大顶堆，如果想要小顶堆需要三个参数
	priority_queue<ListNode*, vector<ListNode*>, priority> help;//C++<queue>中priority_queue自定义队列中数据优先级,让高优先级的排在队列前面，优先出队；这里优先级的比较采用之前定义的priority类
	ListNode* ret_val = new ListNode(0);//哑元节点
	auto temp_node = ret_val;//创建一个新的指针指向哑元节点
	for (auto i : lists)//范围for循环
		help.push(i);//遍历list，将所有指针压入help中
	while (!help.empty()) {//队列不为空时
		auto temp = help.top();//每次创建一个指针指向最小的
		help.pop();//help删掉最小的
		if (temp != NULL) {//最小的不是空指针时
			temp_node->next = temp;//哑元节点开始指向help当前最小的
			temp_node = temp_node->next;//推进哑元节点
			help.push(temp->next);//最小的指针被删除了然后插入最小指针的下一个节点
		}
	}
	return ret_val->next;
}
//复杂度分析，为什么快？感觉和遍历比较没有区别啊？->其实这个东西用法和sort类似就是排序,不同在于它在已经排好序的队列中插入一个数用时：不超过lgn（二分法插入，我不知道具体是怎么插入的）
//vector保存数据肯定很容易实现二分插入，因此找到一个点用lgn，所以O（n2lgn);


int main()
{
	ListNode* l1 = new ListNode(1);
	l1->next = new ListNode(4);
	l1->next->next = new ListNode(5);
	ListNode* l2 = new ListNode(1);
	l2->next = new ListNode(3);
	l2->next->next = new ListNode(4);
	ListNode* l3 = new ListNode(2);
	l3->next = new ListNode(6);
	vector<ListNode*> lists = { l1,l2,l3 };
	/*ListNode* l1 = new ListNode(-2);
	l1->next = new ListNode(-1);
	l1->next->next = new ListNode(-1);
	ListNode* l2 = NULL;
	vector<ListNode*> lists = { l1,l2 };*/
	/*ListNode* l1 = new ListNode(2);
	ListNode* l2 = NULL;
	ListNode* l3 = new ListNode(-1);
	vector<ListNode*> lists = { l1,l2,l3 }; */
	ListNode* res = mergeKLists5(lists);
	while (res != NULL) {
		cout << res->val << " ";
		res = res->next;
	}
	cout << endl;
	system("pause");
    return 0;
}

