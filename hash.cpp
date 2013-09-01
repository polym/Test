/*************************************************************************
Author: zjut_polym
Created Time:   2013/9/1 18:47:03
File Name: hash.cpp
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
#include <queue>
using namespace std;


//----------------------[ZJUT-polym for div2]-------------------------------------
#define ll long long
#define ull unsigned long long
#define MOD 1000000007
#define PII pair<int, int>
#define ff first
#define ss second
#define sz(v) (int)v.size()
#define _mst(buf, val) memset(buf, val, sizeof(buf))
#define rep(i, l, r) for(i = (l); i <= (r); i++)
#define srep(i, l, r) for(i = (l); i >= (r); i--)
#define repi(it, c) for(typeof(c.begin())it = c.begin(); it != c.end(); it++)
#define inf 0x3f3f3f3f
#define N 100005
#define eps 1e-8
#define pi (2.0 * acos(0.0))
//--------------------------------------------------------------------------------

ull factor = 1007;
ull pw[N];
void init(){
	pw[0] = 1;
	for(int i = 1; i < N; i++)
		pw[i] = pw[i-1] * factor;
}
void hashInit(char* ch, ull* sum , ull* rsum = NULL){
	sum[0] = 0;
	int len = strlen(ch+1);
	for(int i = 1; i <= len; i++){
		sum[i] = sum[i-1] * factor + (ull)ch[i];
	}
	rsum[0] = 0;
	if(rsum != NULL){
		for(int i = len; i >= 1; i--){
			rsum[len-i+1] = rsum[len-i] * factor + (ull)ch[i];
		}
	}
}
ull hashval(ull* sum, int l, int r){
	return sum[r] - sum[l-1] * pw[r-l+1];
}

//-------------------------------------------------------------------------------
