// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;
/*s 可能为空，且只包含从 a - z 的小写字母。
p 可能为空，且只包含从 a - z 的小写字母，以及字符.和 *。*/
//有两种匹配思路。在文本中中匹配（快，但是不好写，这个bool就是基于此，DFA);在表达式中匹配（以表达式去套文本，NFA，p的第一个非.和非*）;还可以两者混合，看谁的size短用谁

/*正则表达式
'.' 匹配任意单个字符。
'*' 匹配零个或多个前面的元素。
p代表了一种模式,例如ab*c,那么可以代表ac、abc、abbbbbc等等
然后在s中，检测是不是有这样类型的字符串
比如s=a则没有
s=ac则有*/

//规则没搞清楚,哈哈哈
bool isMatch1(string s, string p) {
	//特殊情况
	if (s == p)//完全匹配
		return true;
	if (s == "") {
		return true;
	}
	if (s != ""&&p == "") {
		return false;
	}
	if (p == ".*") {//表示匹配任意
		return true;
	}
	if (p.find('*') == string::npos&&p.find('.') == string::npos) {//除了完全匹配的情况,必须含有.或*才能称之为正则匹配
		return false;
	}
	//直接能够进行匹配
	if (s.size() == 1 && p==".") {//如果s的size小于2则没有检索空间
		return true;
	}
	if (s.size() == 1) {
		return false;
	}
	if (p.find(s) != string::npos) {
		return true;
	}
	//匹配情况,并且s[0]在p中匹配的不是.
	string p1=p;
	while (p1.find(s[0]) != string::npos) {
		p1 = p1.substr(p1.find(s[0]) + 1);//更新p1
		size_t right = p.find(p1);
		size_t j = 0;
		for (size_t i = 1; i != s.size(); ) {//从第二位开始检测p1中这一段s[0]开头的字段是不是匹配
			if (s[i] == p1[j]||p1[j]=='.') {
				++i;//可以推进i
				++j;
			}
			//如果不是完全匹配或者.匹配,查看*匹配
			else {
				if (p1[j] != '*') {//暗含j推进到头但是i还没有的情况
					break;//匹配不对
				}
				else {//查看*
					//*有重复之前的
					if ((p.substr(0, right + j)).find(s[i]) != string::npos || (s.substr(0, i)).find(s[i]) != string::npos) {
						if (s.find_first_not_of(s[i], i)!=string::npos) {
							i = s.find_first_not_of(s[i], i);//推进到第一个不等于前者的地方
						}
						else {//已经到最后一个字符了
							++i;
						}
						++j;//无论如何j都是均匀往后推一位（遇到重复的*也是对每一个*都进行处理）
					}
					else {//*不重复之前的
						++j;
						//i的位置不能变,进行j之后的字符判断
					}
				}
			}
			if (i == s.size()) {//成功匹配
				return true;
			}
		}
	}
	//匹配情况,并且s[0]在p中匹配的是.
	string p2 = p;
	while (p2.find('.') != string::npos) {
		p2 = p2.substr(p2.find('.') + 1);
		size_t right = p.find(p2);
		size_t j = 0;
		for (size_t i = 1; i != s.size();) {
			if (s[i] == p2[j] || p2[j] == '.') {
				++i;
				++j;
			}
			else {
				if (p2[j] != '*') {
					break;
				}
				else {
					if ((p.substr(0, right + j)).find(s[i]) != string::npos|| (s.substr(0, i)).find(s[i]) != string::npos)  {
						if (s.find_first_not_of(s[i], i)!=string::npos) {
							i = s.find_first_not_of(s[i], i);//推进到第一个不等于前者的地方
						}
						else {
							++i;
						}
						++j;
					}
					else {//*不重复之前的
						++j;
					}
				}
			}
			if (i == s.size()) {
				return true;
			}
		}
	}
	//匹配情况,并且s[0]在匹配中是匹配*
	string p3 = p;
	while (p3.find('*') != string::npos) {
		p3 = p3.substr(p3.find('*') + 1);
		size_t right = p.find('*'+p3);//p3在p中的起始位置,即*的位置
		size_t j = 0;
		if ((p.substr(0, right)).find(s[0])!=string::npos) {//在*之前查询有没有出现s[0],有就可以对*之后进行判断比较
			size_t i = s.find_first_not_of(s[0]);
			if (i == string::npos) {
				return true;
			}
			else {
				for (; i != s.size();) {
					if (s[i] == p3[j] || p3[j] == '.') {
						++i;
						++j;
					}
					else {
						if (p3[j] != '*') {
							break;
						}
						else {
							if ((p.substr(0, right + j)).find(s[i]) != string::npos || (s.substr(0, i)).find(s[i]) != string::npos) {
								if (s.find_first_not_of(s[i], i) != string::npos) {
									i = s.find_first_not_of(s[i], i);//推进到第一个不等于前者的地方
								}
								else {
									++i;
								}
								++j;
							}
							else {//*不重复之前的
								++j;
							}
						}
					}
					if (i == s.size()) {
						return true;
					}
				}
			}
		}
	}
	//不匹配情况
	return false;
}

//标准答案
bool isMatch2(string s, string p) {
	auto m = s.size(), n = p.size();//记录s和p的长度
	vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));//二维容器m+1个，每一个容器里有n+1个bool量，false
	dp[0][0] = true;//第一个元素默认是匹配的
	for (int i = 0; i != m + 1; ++i) {//i是s里面的
		for (int j = 1; j != n + 1; ++j) {//j是p里面的
			if (p[j - 1] == '*') {//p检索，遇到*号时处理
				dp[i][j] = (j > 1 && dp[i][j - 2]) ||
					((i > 0 && j > 1 && (s[i - 1] == p[j - 2] || p[j - 2] == '.'))
						&& (i > 0 && dp[i - 1][j]));//||和&&按顺序，p检索不是第一个且上一个字符是匹配的，第一项正确；s不是第一个字符和p不是第二个字符，检索中前一个字符匹配，第二项正确；
			}
			else {//不是*号时处理
				dp[i][j] = (i > 0 && dp[i - 1][j - 1]) && (s[i - 1] == p[j - 1] || p[j - 1] == '.');//且只要有错就是错，或只要有正确就是正确
				//s不是第一个字符并且对角线前一项正确，第一项正确；检索中前一个字符匹配，第二项正确；
			}
		}
	}
	//逻辑是这样的,当s和p的长度都是0的时候是匹配的，s不是0而p是很明显都是不匹配
	//矩阵的逻辑就是逐渐增加长度,数字几就代表出几个长度的字符，例如a和a*，0，2代表''和'a*'判断是否匹配
	//匹配，所以[0][2]是True
	//所以矩阵添加的顺序就按字符一个个增加来判断
	//综上，第一列一定都是0（p是空字符除了s也是空字符外不可能匹配，所以j=1开始变化
	//递增逻辑,首先判断在p的当前位置是不是*（索引从0开始，所以对于当前j的长度的最后一个字符是j-1）


	//如果是*，j>1是因为第一个字符如果就是*则是非法的,除去非法情况，同一行前两个状态位置是否是正确(如果正确表明在这一行之前的p是匹配的），这个情况是*让元素为0
	//或者除了第0行和第一列，当前s的i位置字符（i-1表示最后一个）和p的导数第二个字符匹配，这个情况是*让元素重复并且需要检查s少一个字符的字段能否和当前的p匹配
	//即如果之前的已经不匹配了说明两个字段不匹配了adc和abc*）因为之前的条件只比较了当前位置字符
	//因为有*号可以直接略掉前一个字符，所以可以直接比较
	//以上两条满足一条则正确，表明*在这里是可以匹配的

	//如果不是*，i>0是因为p不是*如果s是空必然不匹配，同时由于该位置不是*，则需要比s和p各去掉一个字符是否匹配,第一个条件
	//第二个条件则是当前位置是否匹配

	/*for (int i = 0; i != m + 1; ++i) {
	for (int j = 0; j != n + 1; ++j) {
	cout << dp[i][j] << " ";
	}
	cout << endl;
	}*/
	return dp[m][n];
}


	bool isMatch(string s, string p) {
		if (p.length() == 0) {
			return s.length() == 0;
		}

		if (p.length() == 1) {
			return (s.length() == 1) && (s[0] == p[0] || p[0] == '.');
		}

		if (p[1] != '*') {
			if (s.length() == 0) {
				return false;
			}
			else {
				return (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
			}
		}
		else {
			while (s.length() > 0 && (s[0] == p[0] || p[0] == '.')) {
				if (isMatch(s, p.substr(2))) {
					return true;
				}
				s = s.substr(1);
			}
			return isMatch(s, p.substr(2));
		}
	}

	class Solution {
	public:
		bool a[1000][1000];//1000*1000的矩阵表征s和p的长度范围
		bool isMatch(string s, string p) {
			a[0][0] = 1;	//空串与空串一定匹配 
			a[0][1] = a[1][0] = 0;	//一定不匹配 
			for (int i = 1; i <= p.length(); i++)	//考虑空串和模式串的匹配情况 
				if (p[i - 1] == '*')
					a[0][i] = a[0][i - 2];
			for (int i = 1; i <= s.length(); i++)
			{
				for (int j = 1; j <= p.length(); j++)
				{
					char t1 = s[i - 1], t2 = p[j - 1];	//当前字符 
					if (t2 == '.')		//只用看前面匹配与否 
						a[i][j] = a[i - 1][j - 1];
					else if (t2 == '*')	//唯一难点 
					{
						//如果 * 前一个是'.' 去掉.*能直接匹配或者不去掉.*与前i-1匹配 
						if (p[j - 2] == '.')
							a[i][j] = a[i][j - 2] | a[i - 1][j];
						//如果t1与重复的字符相同，该字符重复个数为 非0 或 0 任一能匹配就行 
						else if (t1 == p[j - 2])
							a[i][j] = a[i - 1][j] | a[i][j - 2];
						//不同,如果能匹配该字符重复个数必定为0。 
						else
							a[i][j] = a[i][j - 2];
					}
					else	//一定要当前字符相等且前面也匹配 
						a[i][j] = (t1 == t2)&a[i - 1][j - 1];
				}
			}
			return a[s.length()][p.length()];
		}
	};
int main()
{
	/*string s = "heeeello";
	string p = "whellworld";
	cout << p.find(s) << endl;
	cout << s.find('l') << endl;
	cout << s.substr(2) << endl;
	cout << s.find_first_not_of('e',1) << endl;*/
	//aa和a F;aa和a* T;ab and .* T;aab and c*a*b T;mississippi and mis*is*p*. F;abbbbc and a.**c T;abc and *a***b*c T;ab and .*c F;aaa and aaaa F;aa and aa T;aaa and a*a T;aaa and ab*ac*a T;
	//abc and ab*ac**c T;abc and ba*c T;aac and .*c T;a and . T;aa and . F;a and ab*a F;
	string s ="ab", p = "abc*";
	cout << isMatch2(s, p) << endl;
	/*string s = "weofgx";
	cout << (s.substr(2,5)).find('f') <<' '<<s[6]<< endl;
	if (s[6] != '*')
		cout << "it is right" << endl;*/
	//cout << ((true && false || true)&&(false)) << endl;
	system("pause");
    return 0;
}

