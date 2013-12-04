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
#define N 55
#define eps 1e-8
#define pi (2.0 * acos(0.0))
#define MAXN 4002
//--------------------------------------------------------------------------------
struct Edge{
	int v, val, next;
}E[100000];
int list[MAXN], e;
void ini(){
	e = 0; memset(list, -1, sizeof(list));
}
inline void insert(int u, int v, int val1, int val2){
	E[e].v = v; E[e].val = val1; E[e].next = list[u]; list[u] = e++;
	E[e].v = u; E[e].val = val2; E[e].next = list[v]; list[v] = e++;
}
struct Dinic{
	int t_L[MAXN], _qu[MAXN], lev[MAXN];
	int _st[MAXN], source, sink;
	int BFS(){
		int p, u, v, val, temp, s = 0, t = 0;
		memset(lev, 0, sizeof(lev));
		lev[source] = 1; _qu[t++] = source;
		while(s < t){
			temp = _qu[s++];
			s = (s == MAXN ? 0:s);
			for(int p = list[temp]; p != -1; p = E[p].next){
				u = temp, v = E[p].v, val = E[p].val;
				if(!lev[v] && val){
					lev[v] = lev[u] + 1;
					_qu[t++] = v; t = (t == MAXN? 0:t);
				}
			}
		}
		return lev[sink];
	}
	int DFS(){
		memcpy(t_L, list, sizeof(list));
		int temp, top = -1, flow = 0, v, p;
		while(true){
			if(top < 0){
				v = source;
				for(p = t_L[v]; p != -1; p = E[p].next){
					if(E[p].val && lev[E[p].v] == 2) break;
				}
				if(p == -1) break;
				_st[++top] = p, t_L[source] = p;
			}
			temp = _st[top];
			if(E[temp].v != sink){
				int u = E[temp].v;
				for(p = t_L[u]; p != -1; p = E[p].next){
					if(E[p].val && lev[u]+1 == lev[E[p].v]) break;
				}
				if(p == -1) lev[u] = inf, top--;
				else t_L[u] = p, _st[++top] = p;
			}
			else{
				int t_flow = inf+1, ind;
				for(int i = 0; i <= top; i++){
					if(E[_st[i]].val < t_flow){
						t_flow = E[_st[i]].val;
						ind = i;
					}
				}
				flow += t_flow;
				for(int i = 0; i <= top; i++){
					E[_st[i]].val -= t_flow;
					E[_st[i] ^ 1].val += t_flow;
				}
				top = --ind;
			}
			
		}
		return flow;
	}
	int dinic(){
		int ans = 0, flow;
		while(BFS()) while(flow = DFS()) ans += flow;
		return ans;
	}
}maxflow;
//--------------------------------------------------------------------------------
struct point{
	int x, y, z;
	point(int _x = 0, int _y = 0, int _z = 0):x(_x), y(_y), z(_z){}
}cnt[N];
int pwl(point a, point b){
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}
bool has[N], out[N];
int main() {
	int n, m, u, v;
	double R;
	while(scanf("%d%d%lf", &n, &m, &R) != EOF){
		memset(has, 0, sizeof(has));
		memset(out, 0, sizeof(out));
		has[0] = 1;
		cnt[0] = point(0, 0, 0);
		ini();
		maxflow.source = 0, maxflow.sink = n+1;
		for(int i = 1; i <= n; i++){
			scanf("%d%d%d", &cnt[i].x, &cnt[i].y, &cnt[i].z);
			if(pwl(cnt[i], cnt[0]) <= R * R){
				has[i] = 1;
			}
		}
		for(int i = 0; i < m; i++){
			scanf("%d%d", &u, &v);
			if(has[u] && has[v]){
				insert(u, v, pwl(cnt[u], cnt[v]), 0);
				insert(v, u, pwl(cnt[u], cnt[v]), 0);
			}
			else{
				if(has[u] && !has[v]){
					insert(u, v, pwl(cnt[u], cnt[v]), 0);
//					insert(v, u, pwl(cnt[u], cnt[v]), 0);
					out[v] = 1;
				}
				if(has[v] && !has[u]){
					insert(v, u, pwl(cnt[u], cnt[v]), 0);
					out[u] = 1;
				}
			}
		}
		for(int i = 1; i <= n; i++){
			if(!has[i]){
				insert(i, n+1, inf, 0);
			}
		}
		cout << maxflow.dinic() << endl;
	}
 	return 0;
}

