SA求LCP  后缀数组模版
#include<cmath>
#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include<string.h>
using namespace std;
#define DEBUG(a) cout<<#a"=="<<a<<endl
const int MAXN = 200005;
char s[MAXN];
int sa[MAXN];
int t[MAXN], t2[MAXN], c[MAXN];
//sa[i]表示字典树为i的是哪个后缀
//rank[i]表示第i个后缀在sa中的排名
//height[i]表示sa[i]与sa[i-1]这两个后缀的lcp
//构造字符串S的后缀数组，每个字符串值必须为0~M-1
void build_sa(int m, int n) {//m == 130靠谱？
	memset(t, -1, sizeof(t));
	memset(t2, -1, sizeof(t2));
	int i, *x = t, *y = t2;
	//基数排序
	for(i = 0; i < m; i++) c[i] = 0;//个数清0
	for(i = 0; i < n; i++) c[x[i] = s[i]]++; //对应的字母个数++  同时s[i]值复制给x[i]
	for(i = 1; i < m; i++) c[i] += c[i-1];
	for(i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
	//---------------------------------------------------------
	for(int k = 1; k <= n; k <<= 1) {//目测枚举长度
		int p = 0;
		//直接利用sa数组排序第二关键字
		for(i = n - k; i < n; i++) y[p++] = i;
		for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
		//基数排序第一关键字
		for(i = 0; i < m; i++) c[i] = 0;
		for(i = 0; i < n; i++) c[x[y[i]]]++;
		for(i = 0; i < m; i++) c[i] += c[i-1];
		for(i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
		//根据sa和y数组计算新的x数组
		swap(x, y);
		p = 1;  x[sa[0]] = 0;
		for(i = 1; i < n; i++)
			x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		if(p >= n) break;
		m = p;
	}
}
//--------------以下为LCP
int rank[MAXN], height[MAXN];
void getheight(int n) {
	int i, k = 0;
	for(i = 0; i < n; i++) rank[sa[i]] = i;
	for(i = 0; i < n; i++) {
		if(k) k--;
	  if(rank[i] - 1 >= 0) {	
		int j = sa[rank[i]-1];
		while(s[i+k] == s[j+k]) k++;
		height[rank[i]] = k;
		}
	}
}
//----------------模板结束
int M[MAXN][22];
void initRMQ(int n) {
	for(int i = 0; i < n; i++)
		M[i][0] = height[i];
	for(int j = 1; 1<<j <= n; j++)
		for(int i = 0; i + (1<<j)-1 < n; i++)
			M[i][j] = min(M[i][j-1], M[i+(1<<(j-1))][j-1]);
}
int RMQ(int l, int r) {
	int m = (int)floor(log(double(r-l+1))/log(2.0));
	return min(M[l][m], M[r-(1<<m)+1][m]);
}
//----------------------RMQ----------
char s2[MAXN];
int main() {
#ifdef TIOPLATO
	freopen("in.txt", "r", stdin);
#endif
	while(scanf("%s", s) != EOF) {
		scanf("%s", s2);
		int lenl = strlen(s);
		int lenr = strlen(s2);
		s[lenl] = '@';
		for(int i = 0; i < lenr; i++) {
			s[i+1+lenl] = s2[i];
		}
		int n  = lenl + lenr + 1;
		build_sa(130,n);
		getheight(n);
		int ans = 0;
		for(int i = 1; i < n; i++) {
			if(sa[i-1] < lenl &&  lenl < sa[i])
				ans = max(ans, height[i]);
			if(sa[i-1] > lenl && sa[i] < lenl)
				ans = max(ans, height[i]);
		}
		printf("%d\n", ans);
	}
}

