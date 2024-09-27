#include<cstdio>
#include<vector>

using namespace std;

int n, m, dfn;

vector<int> Edge[10000];
vector<int> Type[10000];//1 parent, 2 child 3 back/forward
int Dfn[10000];
int L[10000];
int Cut[10000];

void dfs(int x, int p){
	int s, i;
	Dfn[x] = ++dfn;
	s = Edge[x].size();
	for (i = 0; i < s; i++) {
		if (Edge[x][i] == p) //parent
			Type[x][i] = 1;
		else if (Dfn[Edge[x][i]] == 0) {//child
			Type[x][i] = 2;
			dfs(Edge[x][i], x);
		}
		else //back/forward
			Type[x][i] = 3;
	}
}
int dfs2(int x, int p) {
	int s, i, rv, cc;
	L[x] = Dfn[x];
	s = Edge[x].size();
	for (i = 0; i < s; i++) {
		if (Type[x][i] == 1) //parent
			printf("");
		else if(Type[x][i] == 2){
			rv = dfs2(Edge[x][i], x);
			L[x] = min(L[x], rv);
		}
		else {//back/forward
			L[x] = min(L[x], Dfn[Edge[x][i]]);
		}
	}
	if (p == 0) {//root ÀÏ ¶§
		cc = 0;
		for (i = 0; i < s; i++) if (Type[x][i] == 2) cc++;
		if (cc > 1) Cut[x] = 1;
	}
	else {
		for (i = 0; i < s; i++) {
			if (Type[x][i] == 2) {
				if (L[Edge[x][i]] >= Dfn[x]) 
					Cut[x] = 1;
			}
		}
	}
	return L[x];
}
int main() {
	int i, x, y;
	scanf("%d %d", &n, &m);
	for (i = 0; i < m; i++) {
		scanf("%d %d", &x, &y);
		Edge[x].push_back(y);
		Type[x].push_back(0);
		Edge[y].push_back(x);
		Type[y].push_back(0);
	}
	
	dfn = 0;
	dfs(1, 0);
	for (i = 1; i <= n; i++)
		if (Dfn[i] == 0) break;
	if (i <= n) {printf("Disconnected Graph!\n");exit(1);}
	dfs2(1, 0);
	printf("Cut Vertices : ");
	for (i = 1; i <= n; i++) 
		if (Cut[i] == 1) 
			printf(" %d", i);
		
	printf("\n");
	return 0;
}

/*
5 3
3 2
2 1
1 4

5 4
3 2
2 1
1 4
4 5

5 5
3 2
2 1
1 4
4 5
1 3

16 20
1 2
1 3
2 4
3 4
4 5
5 6
4 6
5 7
7 8
4 12
12 13
4 11
11 13
11 10
10 9
9 11
13 14
14 15
15 16
14 16

*/