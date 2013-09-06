/*************************************************************************
Author: zjut_polym
Created Time:   2012/9/17 11:47:14
File Name: Tree.cpp
************************************************************************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <climits>
using namespace std;
#define ll long long
#define N 100005
#define MOD 1000000007
int d[N], tmp[N];
void merge(int st, int pos, int ed){   // st ~ pos-1  pos ~ed-1
	int size = 0, i = st, j = pos;
	while(i < pos && j < ed){
		if(d[i] > d[j]){
			tmp[size++] = d[j]; j++;
		}
		else{
			tmp[size++] = d[i]; i++;
		}
	}
	while(i < pos){
		tmp[size++] = d[i++];
	}
	while(j < pos){
		tmp[size++] = d[j++];
	}
	memcpy(d + st, tmp, size * sizeof(int));
}
void display(int st, int ed){
	if(st == ed){
		cout << endl; return;
	}
	cout << d[st];
	for(int i = st+1; i < ed; i++){
		cout << " " << d[i];
	}
	cout << endl;
}
struct edge{
	int v, nxt, w;
}E[2 * N];
int head[N], esize, size, ans, k;
void addedge(int u, int v, int w){
	E[esize].v = v; E[esize].w = w; E[esize].nxt = head[u]; head[u] = esize++;
}
void _cal(int st, int pos, int ed){
	int j = pos, tmp;
	for(;j < ed; j++){
		tmp = upper_bound(d + st, d + pos, k - d[j]) - d - st;
		ans += tmp;
	}
}
void cal(int st, int pos, int ed){
	int i = pos - 1, j = pos;
	while(i >= st && j < ed){
		if(d[i] + d[j] <= k){
			ans += i - st + 1;
			j++;
		}
		else{
			i--;
		}
	}
}
void dfs(int src, int pre){
	//cout << src << " " << pre << endl;
	int st = size, pos, ed;
	d[size++] = 0;
	pos = size;
	for(int i = head[src]; i != -1; i = E[i].nxt){
		int v = E[i].v;
		if(v == pre) continue;
		dfs(v, src);
		ed = size;
		for(int j = pos; j < ed; j++){
			d[j] += E[i].w;
		}
	//	cout << "V "<<v << endl;
	//	display(st, ed);
		cal(st, pos, ed);
	//	cout << "Ans " << ans << endl;
		merge(st, pos, ed);
		pos = ed;
	}
}
int main() {
	int n, u, v, w;
	while(scanf("%d%d", &n, &k) && (n || k)){
		memset(head, -1, sizeof(head));
		esize = size = ans = 0;
		for(int i = 1; i < n; i++){
			scanf("%d%d%d", &u, &v, &w);
			addedge(u, v, w);
			addedge(v, u, w);
		}
		dfs(1, 0);
		printf("%d\n", ans);
	}
    return 0;
}
