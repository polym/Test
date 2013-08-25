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
#define N 120005
#define MOD 1000000007
#define PII pair <int, int>
char cnt[N], tmp[2 * N];
int p[2 * N];
void convert(){
	int len = strlen(cnt), size = 0;
	tmp[size++] = '$';
	tmp[size++] = '#';
	for(int i = 0; i < len; i++){
		tmp[size++] = cnt[i];
		tmp[size++] = '#';
	}
	tmp[size++] = '\0';
}
int gao(){
	int len = strlen(tmp), mx = 0, id;
	for(int i = 1; i < len; i++){
		if(mx > i){
			p[i] = min(p[2 * id - i], mx - i);
		}
		else{
			p[i] = 1;
		}
		for(; tmp[i+p[i]] == tmp[i - p[i]]; p[i]++);
		if(p[i] + i > mx){ 
			mx = p[i] + i; id = i;
		}
	}
	int ans = 0;
	for(int i = 0; i < len; i++){
		ans = max(ans, p[i] - 1);
	}
	return ans;
}
int main(){
	while(scanf("%s", cnt) != EOF){
		int len = strlen(cnt);
		if(len == 0) continue;
		convert();
		cout << gao() << endl; 
	}
}
