// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>//如果不用这个库函数,string类型是数组
#include<vector>
#include<set>//用来查询有没有出现重复项
#include<unordered_map>//内部是哈希表，无序但是查找高效->标准答案都是利用了hash性质
#include<bitset>
using namespace std;
//给定一个字符串s和一些长度相同的words
//找出words组成的子串在s中的位置，组成子串的顺序不重要
//思路：确定word的长度，在s中每组推进，O（nm），m一般而言是较小的常数
//停止找寻的情况，s剩下的长度已经小于words
//特殊情况：s是0，words是0之类的;s是0直接小过words的长度会直接返回空的res
//难点：s中不完全是words里的片段因此只能在s中一个一个字符推进
//失误点一：words里面的词可以是重复的，那么就允许了s中有重复的出现，所以需要对words进行删除查询不需要用set了
//用时4268ms,因为遍历了s
vector<int> findSubstring(string s, vector<string>& words) {
	//如果words不是空的但是里面的单词有空的,应该先将words里面的空字符串全部去掉(因为空字符串可以匹配任何）
	for (int i = 0; i < words.size(); ++i) {
		if (words[i] == "") {
			words.erase(words.begin() + i);
			--i;
		}
	}
	//如果words是空的
	if (words.empty()) return {};
	int slength = s.size();
	int wlength = words[0].size();
	int wwlength = words.size();
	int wslength = wlength*wwlength;
	vector<string> re;
	vector<int> res = {};
	string sstr = "";
	for (int i = 0; slength-i >= wslength;++i) {
		//对当前字符开始检查
		re = words;
		int k = i;
		for (int z = 0; z != wwlength;++z) {//已经在当前i的s中检查完了words中所有word的长度之和,次数不会超过长度
			sstr = s.substr(k, wlength);
			//查找words中匹配的word
			int relength = re.size();
			for (int j = 0; j != relength; ++j) {
				if (re[j] == sstr) {//能找到匹配的
					re.erase(re.begin() + j);
					break;//找到之后删除掉就行了，可以进行下一轮的比较了
				}
			}
			k += wlength;
			if (re.empty()) { res.push_back(i); break; }
			if (re.size() == relength) break;//意味着没有找到匹配项
		}
	}
	return res;
}

//换一个思路,基于words去s中寻找
//因为words里的字串是不需要顺序的，只需要将words内的所有内容在s中出现的位置分别统计（得的m组顺序）在对比能否等间隔连起来。。。感觉更花时间,找到所有的就已经是O（mn)了


//标准答案一 44ms  没有了m还是遍历s  O（n）  有可能m会很大，因此这个思路变快了
	vector<int> findSubstring1(string s, vector<string>& words) {
		if (s.empty() || words.empty()) return vector<int>();//如果两者之一是空返回空集
		unordered_map<string, int> count;//建立无序map
		int m = words[0].length(), k = words.size(), n = k*m, l = s.length();//m保存单词长度，k保存容器长度，n保存总长度，l保存字符长度
		int left, right, cnt = 0;//左右两个类似指针的索引和计数变量
		string sub1, sub2;//子段字符串
		vector<int> ans;//保存结果的vector
		for (string v : words)
			count[v]++;//将words里的单词读取一遍建立unorderedmap
		for (int start = 0; start < m; start++) {//left和right的起始值在单词长度里变化，因为每次加单词的长度，因此起始从第一个单词里变化即可遍历了
			left = right = start;//给left和right进行初始化
			while (right<l && l - left >= n) {//这里是L不是1，意思是right没有超过s的长度并且s剩下的长度比总长度长时才有继续的意义
				sub1 = s.substr(right, m);//从s中以right开始取出单词长度的字符串
				if (count.count(sub1) && count[sub1]>0) {//count操作是在um（unorderedmap）里sub1字段出现的次数，这里的意思是sub1出现//个人觉得两个语句是一样的意思
					count[sub1]--;//um中sub1少1
					cnt++;//匹配了一个单词
				}
				else {//没有在um中找到匹配的
					sub2 = s.substr(left, m);//在s中从left开始取出单词长度的字符段
					while (sub1.compare(sub2)) {//比较字符串，相等返回0，sub1大，返回大于0的数，反之返回小于1的数；注意while只要不为0都认为正确，应该执行
						//sub1和sub2不一样时
						count[sub2]++;//它们两个不一样意味着刚刚right走过的字符段里出现过匹配，因为之前减一了现在要补回去
						cnt--;//补了一个回去因此减去一个
						left += m;//开始移动单词长度
						sub2 = s.substr(left, m);//追上right为止
					}
					left += m;//left往前推进单词长度
				}
				if (cnt == k)//检索完成
					ans.push_back(left);//记录下刚出现的位置
				right += m;//right往前推进单词长度
			}
			//下面这个循环是解决这样一个情况的，right最后几个是匹配的但是因为没有经历不匹配了那么left落在后面因此要补充消掉的并把计数调回去（例如例子里最后的man没有）
			while (left < right) {
				count[s.substr(left, m)]++;
				cnt--;
				left += m;
			}
		}
		return ans;
	}
	//利用unorderedmap补充和减少来进行推进比较

	//标准答案二 24ms
	class Solution {
	public:
		int m;//全局变量用来保存单词长度
		const unsigned int p1 = 10007u, p2 = 1000000007u;//后缀u表示无符号的意思,二进制10007u=0010011100010111  1000000007u=00111011100110101100101000000111
		//内联函数，获取哈希表
		inline unsigned int get_hash(const char* str) {//接收一个char数组顶层const不改变里面的值
			unsigned int x = 0;
			for (int i = 0; i < m; i++)//单词字符长度内的哈希值超过这个长度的字符数组也不会计算，即以单词为基本单位建立哈希值
				x = (x ^ p1) * str[i];//^不是幂的意思，是按位异或运算符，相应位相同返回0否则为1，不带进位
			return x;
		}
		vector<int> findSubstring(string s, vector<string>& words) {
			vector<int> ans;
			int k = words.size();//容器长度
			if (k == 0) return ans;
			int n = s.length();
			k *= m = words[0].length();//由容器长度变成字符串总长度
			//char* cstr = s.data();//虽然data是返回数组并且有结束符但是是常量,要求有顶层const即const char*，也就是说数组里的char不能改变
			char* cstr = &(s[0]);//cstr指向数组第一个
			unsigned int* h = new unsigned int[n - m + 1];
			unsigned int r = 0;
			for (string i : words) r += get_hash(i.data());//创建哈希表，字符数组，words里的所有单词的哈希值相加
			for (int i = 0; i <= n - m; i++)
				h[i] = get_hash(cstr + i);//对s中剩下的字符（最后去掉m个）建立哈希表（因为以m长度建立哈希，最后剩余的字符数不超过m自然建立不起来），存在h数组中，h[0]是s从0开始的字符哈希值（barfoothefoobar只取bar建立单词哈希值),h[2]则是从s中2开始的字符的哈希值(rfo)
			for (int i = 0; i < m; i++) {//这里i也小于单词长度跳着检查字符，因为哈希值是以m为单位的字符组成的
				unsigned int t = 0;
				for (int j = i; j < k - m; j += m)//小于k-m总长度字符差一个单词的哈希值已经得到了
					t += h[j];//开始按间隔把当前开始的字符哈希值读进t
				for (int j = i; j <= n - k; j += m) {//小于等于n-k意味着最后已经构不成长度k了
					//第一个for循环是把当前哈希值建立到差一个单词，第二个是跳m加进来比较然后删掉最前面的形成推进
					t += h[j + k - m];//k-m是定值，即除去一个单词后剩下的长度，因为之前差了一个单词
					if (t == r) ans.push_back(j);//t表和r表的哈希值之和对上了说明当前i开始检索的是对的
					t -= h[j];
				}
			}
			delete[] h;
			return ans;
		}
	};
	//其实也是遍历搜索，通过比较哈希值而不是字符是否完全相等来进行推进比较   O（n)
int main()
{
	/*string s ("hello");
	cout << s.substr(0,2) << endl;*/
	/*set<int> ex = { 3,5,8,6 };//ex.find返回的是迭代器
	if (ex.find(33) != ex.end()) {
		cout << "FIND" << endl;
	}
	else {
		cout << "NOT FIND" << endl;
	}
	cout << ex.size() << endl;*/
	/*string s = "wordgoodgoodgoodbestword";
	vector<string> words = { "word","good","best","word" };*/
	/*string s = "wordgoodgoodgoodbestword";
	vector<string> words = { "word", "good", "best", "good" };*/
	string s = "barfooahefoobarman";
	/*string sub1 = s.substr(6, 3);
	string sub2 = s.substr(0, 3);
	cout << sub1.compare(sub2) << endl;
	while (sub1.compare(sub2)) {
		cout << "yes" << endl;
	}*/

	vector<string> words = { "foo", "bar" };
	Solution sss;
	vector<int> res = sss.findSubstring(s, words);
	for (int c : res) {
		cout << c << " ";
	}
	bitset<32> bit(1000000007u);
	cout << bit << endl;
	//cout << 1*(21 ^ 56) << endl;//21是0000000000010101 56是0000000000111000 所以异或运算后是0000000000101101=45
	cout << endl;
	system("pause");
    return 0;
}

