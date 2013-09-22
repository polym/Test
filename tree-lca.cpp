#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <list>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
//#pragma comment(linker, "/STACK:16777216")
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define N 100010
#define M 2000000
int u[M][2] , v[M] , cnt;
int n , m , a[N] , L[N] , f[17][N] , pre[N] , mcnt;
struct edge
{
  int x , next;
}e[N << 1];
int str[20];
int root[N];
int newnode()
{
  memset(u[cnt] , 0 , sizeof(u[cnt]));
  v[cnt] = 0;
  return cnt ++;
}

void insert(int x , int y , int val)
{
    x = root[x] , y = root[y];
    for (int i = 0 ; i < 16 ; ++ i)
    {
        int c = val >> (16 - i - 1) & 1;
        if (!u[x][c])
          u[x][c] = newnode() , u[x][!c] = u[y][!c] , v[u[x][c]] = v[u[y][c]];
        x = u[x][c] , y = u[y][c];
        ++ v[x];
    }
}
int query(int x , int y , int z , int val)
{
    int ans = 0 , res = a[z] ^ val;
    x = root[x] , y = root[y] , z = root[z];
    for (int i = 0 ; i < 16 ; ++ i)
    {
        int c = !(val >> (16 - i - 1) & 1);
        if (v[u[x][c]] + v[u[y][c]] - v[u[z][c]] - v[u[z][c]] > 0)
            ans |= 1 << (16 - i - 1);
        else
            c = !c;
        x = u[x][c] , y = u[y][c] , z = u[z][c];
    }
    return max(ans , res);
}


void dfs(int x , int fa)
{
    f[0][x] = fa , L[x] = L[fa] + 1 ;
    root[x] = newnode();
    insert(x , fa , a[x]);
    for (int i = pre[x] ; ~i ; i = e[i].next)
        if (e[i].x != fa)
            dfs(e[i].x , x);
}

int LCA(int x , int y)
{
    if (L[x] > L[y]) swap(x , y);
    for (int i = 16 ; i >= 0 ; -- i)
        if (L[y] - L[x] >= 1 << i)
            y = f[i][y];
    if (x == y) return y;
    for (int i = 16 ; i >= 0 ; -- i)
        if (f[i][x] && f[i][x] != f[i][y])
            x = f[i][x] , y = f[i][y];
    return f[0][x];
}

void work()
{
    int  i , j , x , y , z , w;
    memset(pre , -1 , sizeof(pre));
    mcnt = 0 , cnt = 1;
    for (i = 1 ; i <= n ; ++ i)
        scanf("%d",&a[i]);
    for (i = 1 ; i < n ; ++ i)
    {
        scanf("%d%d",&x,&y);
        e[mcnt].x = y , e[mcnt].next = pre[x] , pre[x] = mcnt ++;
        e[mcnt].x = x , e[mcnt].next = pre[y] , pre[y] = mcnt ++;
    }
    memset(f , 0 , sizeof(f));
    dfs(1 , 0);
    for (j = 1 ; 1 << j < n ; ++ j)
        for (i = 1 ; i <= n ; ++ i)
            f[j][i] = f[j - 1][f[j - 1][i]];
    while (m --)
    {
        scanf("%d%d%d",&x,&y,&w);
        z = LCA(x , y);
        printf("%d\n" , query(x , y , z , w));
    }
}

int main()
{
    freopen("~input.txt" , "r" , stdin);
    while (~scanf("%d%d",&n,&m))
        work();
    return 0;
}
