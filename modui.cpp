#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 500005
#define ll long long
#define PII pair <int, int>
struct query{
	int l, r, id, sq;
}Q[N];
PII ans[N];
int n, q, sqrtn;
bool cmp(query a, query b){
	if(a.sq != b.sq) return a.sq < b.sq;
	return a.r < b.r;
}
ll gcd(ll a, ll b){
	for(ll tmp; b; a = b, b = tmp){
		tmp = a % b;
	}
	return a;
}
int num[N], cnt[N];
void gao(){
	memset(num, 0, sizeof(num));
	int L = 1, R = 1, cur = 0;
	num[cnt[1]]++;
	ll s = 0, d;
	while(cur < q){
		while(L < Q[cur].l){
			s -= num[cnt[L]] - 1;
			num[cnt[L]]--;
			L++;
		}
		while(L > Q[cur].l){
			L--;
			s += num[cnt[L]];
			num[cnt[L]]++;
		}
		while(R < Q[cur].r){
			R++;
			s += num[cnt[R]];
			num[cnt[R]]++;
		}
		while(R > Q[cur].r){
			s -= num[cnt[R]] - 1;
			num[cnt[R]]--;
			R--;
		}
		d = (ll)(R - L + 1) * (R - L) / 2; 
		ll g = gcd(s, d);
		ans[Q[cur].id].first = s / g;
		ans[Q[cur].id].second = d / g;
		cur++;
	}
	for(int i = 0; i < q; i++){
		printf("%d/%d\n", ans[i].first, ans[i].second);
	}
}
int main(){
	while(scanf("%d%d", &n, &q) != EOF){
		sqrtn = sqrt(n * 1.0);
		for(int i = 1; i <= n; i++){
			scanf("%d", &cnt[i]);
		}
		for(int i = 0; i < q; i++){
			scanf("%d%d", &Q[i].l, &Q[i].r);
			Q[i].id = i;
			Q[i].sq = Q[i].l / sqrtn;
		}
		sort(Q, Q + q, cmp);
		gao();
	}

}
