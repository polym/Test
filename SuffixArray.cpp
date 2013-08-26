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
char s[N];
int sa[N];
int t[N], t2[N], c[N];
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
int rank[N], height[N];
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
int M[22][N], lg2[N];
void initRMQ(int* x, int n){
	//for(int i = 0; i < n; i++){
	//	cout << height[i] << " ";
	//}
	//cout << endl;
	//for(int i = 0; i < n; i++){
	//	cout << sa[i] << " ";
	//}
	//cout << endl;
	memcpy(M[0], x, n * sizeof(int));
	for(int i = 1; (1 << i) <= n; i++){
		for(int j = 0; j + (1 << i) - 1 < n; j++){
			M[i][j] = min(M[i-1][j], M[i-1][j+(1<<(i-1))]);
		}
	}
}
int query(int l, int r){
	//cout << l << " " << r << endl;
	int k = lg2[r-l+1];
	return min(M[k][l], M[k][r-(1<<k)+1]);
}
//-------------------------------------------------------------------------
int gao(int n){
	int res = 0, tmp = 0;
	for(int i = 1; i < n; i++){
		tmp = (tmp > height[i]? height[i] : tmp);
		if(sa[i] < n / 2){
			int other = n - sa[i] - 1;
			int lcp = query(min(i, rank[other]) + 1, max(i, rank[other]));
			if(lcp > tmp){
				res += lcp - tmp;
				tmp = lcp;
			}
		}
	}
	tmp = 0;
	for(int i = 1; i < n; i++){
		tmp = (tmp > height[i]? height[i] : tmp);
		if(!sa[i]) continue;
		if(sa[i] < n / 2){
			int other = n - sa[i];
//			cout << sa[i] << "other" << other << endl;
			int lcp = query(min(i, rank[other]) + 1, max(i, rank[other]));
			if(lcp > tmp){
				res += lcp - tmp;
				tmp = lcp;
			}
		}
	}
	return res;
}
char cnt[N];
int main(){
	for(int i = 1; (1 << i) < N; i++){
		lg2[1 << i] = 1;
	}
	for(int i = 2; i < N; i++) lg2[i] += lg2[i-1];
	int cas = 1, C;
	scanf("%d", &C);
	while(C--){
		scanf("%s", cnt);
		int len = strlen(cnt), cur;
		cur = len;
		memcpy(s, cnt, len * sizeof(char));
		s[cur++] = '@';
		for(int i = len - 1; i >= 0; i--){
			s[cur++] = cnt[i];
		}
		s[cur] = '\0';
		build_sa('z'+1, cur);
		getheight(cur);
		initRMQ(height, cur);
		printf("Case #%d: %d\n", cas++, gao(cur));
	}
}
