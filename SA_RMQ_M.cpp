/*************************************************************************
Author: zjut_polym
Created Time:   2013/9/2 20:09:28
File Name: sa.cpp
************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
#define ll long long
#define N 220005
#define MOD 1000000007
#define PII pair <int, int>
int lg2[N];
struct Rmq{
	int M[22][N], cnt[N];
	void initRMQ(int* x, int n){
		memcpy(cnt, x, n * sizeof(int));
		for(int i = 0; i < n; i++) M[0][i] = i;
		for(int i = 1; (1 << i) <= n; i++){
			for(int j = 0; j + (1 << i) - 1 < n; j++){
				if(x[M[i-1][j]] < x[M[i-1][j+(1<<(i-1))]])
					M[i][j] = M[i-1][j];
				else
					M[i][j] = M[i-1][j+(1<<(i-1))];
			}
		}
	}
	int query(int l, int r, int flag = 1){
		int k = lg2[r-l+1], ind;
		if(cnt[M[k][l]] < cnt[M[k][r-(1<<k)+1]])
			ind = M[k][l];
		else
			ind = M[k][r-(1<<k)+1];
		if(flag) return cnt[ind];
		return ind;
	}
}alp;
struct Sa{
	char s[N];
	int sa[N], rank[N], height[N];
	int t[N], t2[N], c[N];
	Rmq rmq;
	//sa[i]表示字典序为i的是哪个后缀
	//rank[i]表示第i个后缀在sa中的排名
	//height[i]表示sa[i]与sa[i-1]这两个后缀的lcp
	//构造字符串S的后缀数组，每个字符串值必须为0~M-1
	void build_sa(int m, int n){
		//cout << s << endl;
		memset(t, -1, sizeof(t));
		memset(t2, -1, sizeof(t));
		//基数排序
		int i, *x = t, *y = t2;
		for(i = 0; i < m; i++) c[i] = 0;
		for(i = 0; i < n; i++) c[x[i]=s[i]]++;
		for(i = 1; i < m; i++) c[i] += c[i-1];
		for(i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
		//-----------------------------------------------
		for(int k = 1; k <= n; k <<= 1){
			int p = 0;
			for(i = n - k; i < n; i++) y[p++] = i;
			for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
			for(i = 0; i < m; i++) c[i] = 0;
			for(i = 0; i < n; i++) c[x[y[i]]]++;
			for(i = 1; i < m; i++) c[i] += c[i-1];
			for(i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
			swap(x, y);
			p = 1; x[sa[0]] = 0;
			for(i = 1; i < n; i++){
				x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k]? p-1: p++;
			}
			if(p >= n) break;
			m = p;
		}
	}
	//-------------------------------------------------------------------------
	void getheight(int n){
		int i, k = 0;
		for(i = 0; i < n; i++) rank[sa[i]] = i;
		for(i = 0; i < n; i++){
			if(k) k--;
			if(rank[i]-1 >= 0){
				int j = sa[rank[i]-1];
				while(s[i+k] == s[j+k]) k++;
				height[rank[i]] = k;
			}
		}
	}
	//-------------------------------------------------------------------------
	void init(char* cnt){
		int len = strlen(cnt);
		memcpy(s, cnt, (len+1) * sizeof(char));
		build_sa(130, len);
		getheight(len);
		rmq.initRMQ(height, len);
	}
}sa1, sa2;
