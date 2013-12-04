/*************************************************************************
Author: zjut_polym
Created Time: 2013/12/4 22:07:28
File Name: min_cut.cpp
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
#define eps 1e-8
#define pi (2.0 * acos(0.0))
//--------------------------------------------------------------------------------
const int MAXN = 1005, MAXM = 50000, MAXV = inf; 
struct edge{
	int u, v, c, f, next;
}e[MAXM];
int N, M, S, T, E, head[MAXN];
int p[MAXN], dis[MAXN];
bool vis[MAXN];
queue<int> q;
void init(){
	memset(head, -1, sizeof(head));
	E = 0;
}
void add(int u, int v, int c, int f){
	e[E].u = u; e[E].v = v; e[E].c = c; e[E].f = f;
	e[E].next = head[u]; head[u] = E++;
}
void addedge(int u, int v, int c, int f){
	add(u, v, c, f);
	add(v, u, 0, -f);
}
bool SPFA(int S, int T, int N){
	memset(p, -1, N * sizeof(int));
	memset(vis, 0, N * sizeof(bool));
	memset(dis, 63, N * sizeof(int));
	int u, v;
	vis[S] = 1; dis[S] = 0; q.push(S);
	while(!q.empty()){
		u = q.front(); q.pop();
		vis[u] = 0;
		for(int i = head[u]; i != -1; i = e[i].next){
			if(e[i].c > 0){
				v = e[i].v;
				if(dis[v] > dis[u] + e[i].f){
					dis[v] = dis[u] + e[i].f;
					p[v] = i;
					if(!vis[v]){
						q.push(v);
						vis[v] = 1;
					}
				}
			}
		}
	}
	return dis[T] != MAXV;
}
int mincost(int S, int T, int N){
	int ans = 0, flow = MAXV;
	while(SPFA(S, T, N)){
		ans += dis[T];
		for(int i = p[T]; i != -1; i = p[e[i].u])
			if(e[i].c < flow) flow = e[i].c;
		for(int i = p[T]; i != -1; i = p[e[i].u]){
			e[i].c -= flow;
			e[i^1].c += flow;
		}
	}
	return ans;
}
int main() {
	while(scanf("%d%d", &N, &M) != EOF){
		init();
		int x, y, z;
		S = 0; T = N+1;
		for(int i = 0; i < M; i++){
			scanf("%d%d%d", &x, &y, &z);
			addedge(x, y, 1, z);
			addedge(y, x, 1, z);
		}
		addedge(S, 1, 2, 0);
		addedge(N, T, 2, 0);
		printf("%d\n", mincost(S, T, N+2));
	}
 	return 0;
}

